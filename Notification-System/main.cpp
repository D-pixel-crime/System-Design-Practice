#include "include/database.hpp"
#include "include/dispatcher.hpp"
#include "include/notificationMethod.hpp"
#include "include/notifier.hpp"
#include "include/product.hpp"
#include "include/queueAllocator.hpp"
#include "include/user.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <thread>
#include <vector>

namespace
{
  // Complex Setup Configuration
  constexpr int kMessageQueuePoolSize = 3;
  constexpr int kMessageQueueCapacity = 500;
  constexpr int kNotificationPoolSize = 1000;
  constexpr auto kDispatchWindow = std::chrono::seconds(5);
  constexpr int kNumUsers = 10;
  constexpr int kNumProducts = 15;
  constexpr int kNumDispatchersPerQueue = 2;
} // namespace

struct SubInfo
{
  int userId;
  std::string productName;
  std::vector<std::string> methods;
};

int main()
{
  std::cout
      << "=== Notification System Simulation : Fully Concurrent Test ===\n\n";

  // --- 1. Bootstrap singletons ---
  Database *db = Database::getConn();
  Queue_Allocator::createQueuePool(kMessageQueuePoolSize,
                                   kMessageQueueCapacity);
  Notifier *notifier = Notifier::getNotifier(kNotificationPoolSize);

  // --- 2. Setup Notification Methods ---
  Email_Notification_Method email;
  Message_Notification_Method message;
  Whatsapp_Notification_Method whatsapp;

  // --- 3. Setup Users ---
  std::vector<std::unique_ptr<NonVipUser>> users;
  for (int i = 0; i < kNumUsers; i++)
  {
    users.push_back(std::make_unique<NonVipUser>());
    db->registerUser(users.back().get());
  }

  // --- 4. Setup Products ---
  std::vector<std::unique_ptr<Product>> products;
  for (int i = 0; i < kNumProducts; i++)
  {
    products.push_back(
        std::make_unique<Product>("Product_" + std::to_string(i + 1)));
    db->registerProduct(products.back().get());
  }

  // --- 5. Generate Subscriptions ---
  std::vector<SubInfo> setup_info;

  auto subscribe = [&](NonVipUser *u, Product *p,
                       std::vector<I_Notification_Method *> m,
                       std::vector<std::string> m_names)
  {
    SubInfo info;
    info.userId = u->getId();
    info.productName = p->getName();
    info.methods = m_names;
    setup_info.push_back(info);

    for (auto method : m)
    {
      db->subscribeUser(p, u, method);
    }
  };

  for (int p = 0; p < kNumProducts; p++)
  {
    for (int u = 0; u < kNumUsers; u++)
    {
      std::vector<I_Notification_Method *> m;
      std::vector<std::string> m_names;

      if ((p + u) % 2 == 0)
      {
        m.push_back(&email);
        m_names.push_back("Email");
      }
      if ((p * u) % 3 == 0)
      {
        m.push_back(&message);
        m_names.push_back("Message");
      }
      if ((p - u) % 4 == 0)
      {
        m.push_back(&whatsapp);
        m_names.push_back("Whatsapp");
      }

      if (!m.empty())
      {
        subscribe(users[u].get(), products[p].get(), m, m_names);
      }
    }
  }

  // --- 6. Print Setup ---
  std::cout << "[Initialization Setup]\n";
  std::cout << "Users: " << kNumUsers << " | Products: " << kNumProducts
            << " | Message Queues: " << kMessageQueuePoolSize
            << " | Dispatchers per Queue: " << kNumDispatchersPerQueue << "\n\n";

  std::string separator(93, '=');
  std::cout << separator << "\n";
  std::cout << "| " << std::setw(7) << std::left << "User ID"
            << " | " << std::setw(20) << std::left << "Product Subscribed"
            << " | " << std::setw(55) << std::left << "Notification Methods"
            << " |\n";
  std::cout << separator << "\n";

  for (const auto &info : setup_info)
  {
    std::string methods_str;
    for (size_t i = 0; i < info.methods.size(); i++)
    {
      methods_str += info.methods[i];
      if (i < info.methods.size() - 1)
        methods_str += ", ";
    }

    std::cout << "| User " << std::setw(2) << std::left << info.userId << " | "
              << std::setw(20) << std::left << info.productName << " | "
              << std::setw(55) << std::left << methods_str << " |\n";
  }
  std::cout << separator << "\n\n";

  // --- 7. Start Dispatcher Workers ---
  std::cout << "[Setup] Extracting Message_Queues from Queue_Allocator to "
               "attach Dispatchers...\n";
  std::set<Message_Queue *> unique_queues;
  std::vector<Message_Queue *> queues_to_clean;

  while (unique_queues.size() < kMessageQueuePoolSize)
  {
    Message_Queue *q = Queue_Allocator::allocate_queue();
    if (unique_queues.find(q) == unique_queues.end())
    {
      unique_queues.insert(q);
    }
    else
    {
      // Dummy push to increase size so the Min-Heap yields the next queue
      Notification *dummy = new Notification();
      q->pushNotification(dummy);
      queues_to_clean.push_back(q);
    }
  }

  // Clean up dummies before starting threads
  for (Message_Queue *q : queues_to_clean)
  {
    if (q->hasReadyItem())
    {
      RetryItem item = q->popReadyItem();
      delete item.notification; // Free the local dummy
    }
  }

  std::vector<std::thread> workers;
  for (Message_Queue *q : unique_queues)
  {
    for (int i = 0; i < kNumDispatchersPerQueue; i++)
    {
      workers.emplace_back([q]()
                           {
        Dispatcher dispatcher(q);
        dispatcher.pullNotification(); });
    }
  }
  for (auto &w : workers)
  {
    w.detach();
  }
  std::cout << "[System] " << unique_queues.size()
            << " Message_Queues active with "
            << (unique_queues.size() * kNumDispatchersPerQueue)
            << " total Dispatcher workers listening.\n\n";

  // --- 8. Trigger processing (simulate restocks) CONCURRENTLY ---
  std::cout << "[Action] Triggering restock events for all products "
               "concurrently...\n";
  for (int p = 0; p < kNumProducts; p++)
  {
    products[p]->updateCount((p + 1) * 10);
  }

  std::this_thread::sleep_for(kDispatchWindow);

  // --- 9. Users query states ---
  std::cout
      << "\n[Action] Users query final product availability (Pull Mechanism)\n";
  I_Product *p0 = products[0].get();
  I_Product *pLast = products.back().get();

  std::cout << "User " << users[0]->getId() << " queries " << p0->getName()
            << ": ";
  users[0]->getStatus(p0);

  std::cout << "User " << users.back()->getId() << " queries "
            << pLast->getName() << ": ";
  users.back()->getStatus(pLast);

  std::cout << "\n=== Simulation Complete ===\n";
  return 0;
}
