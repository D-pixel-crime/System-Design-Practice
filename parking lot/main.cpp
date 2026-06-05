#include "include/costStrategy.hpp"
#include "include/parkingLot.hpp"
#include "include/parkingManager.hpp"
#include "include/ticket.hpp"
#include "include/vehicle.hpp"
#include <typeindex>
#include <typeinfo>
#include <iostream>
#include <queue>
#include <format>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << "--- Initializing Parking Lots ---" << std::endl;

    IParkingLot *a1 = new TwoWheelerParkingLot(TwoWheelerParkingLot::currLot, std::type_index(typeid(TwoWheelerVehicle)));
    IParkingLot *a2 = new TwoWheelerParkingLot(TwoWheelerParkingLot::currLot, std::type_index(typeid(TwoWheelerVehicle)));
    IParkingLot *a3 = new TwoWheelerParkingLot(TwoWheelerParkingLot::currLot, std::type_index(typeid(TwoWheelerVehicle)));
    IParkingLot *a4 = new TwoWheelerParkingLot(TwoWheelerParkingLot::currLot, std::type_index(typeid(TwoWheelerVehicle)));

    IParkingLot *b1 = new ThreeWheelerParkingLot(ThreeWheelerParkingLot::currLot, std::type_index(typeid(ThreeWheelerVehicle)));
    IParkingLot *b2 = new ThreeWheelerParkingLot(ThreeWheelerParkingLot::currLot, std::type_index(typeid(ThreeWheelerVehicle)));
    IParkingLot *b3 = new ThreeWheelerParkingLot(ThreeWheelerParkingLot::currLot, std::type_index(typeid(ThreeWheelerVehicle)));

    IParkingLot *c1 = new FourWheelerParkingLot(FourWheelerParkingLot::currLot, std::type_index(typeid(FourWheelerVehicle)));
    IParkingLot *c2 = new FourWheelerParkingLot(FourWheelerParkingLot::currLot, std::type_index(typeid(FourWheelerVehicle)));

    ParkingManager manager(a1, a2, a3, a4, b1, b2, b3, c1, c2);

    std::cout << "\n--- Initializing Vehicles ---" << std::endl;
    IVehicle *v1 = new TwoWheelerVehicle(TwoWheelerVehicle::currId);
    IVehicle *v2 = new TwoWheelerVehicle(TwoWheelerVehicle::currId);
    IVehicle *v3 = new TwoWheelerVehicle(TwoWheelerVehicle::currId);
    IVehicle *v4 = new TwoWheelerVehicle(TwoWheelerVehicle::currId);
    IVehicle *v5 = new TwoWheelerVehicle(TwoWheelerVehicle::currId);

    IVehicle *v6 = new ThreeWheelerVehicle(ThreeWheelerVehicle::currId);
    IVehicle *v7 = new ThreeWheelerVehicle(ThreeWheelerVehicle::currId);
    IVehicle *v8 = new ThreeWheelerVehicle(ThreeWheelerVehicle::currId);
    IVehicle *v9 = new ThreeWheelerVehicle(ThreeWheelerVehicle::currId);

    IVehicle *v10 = new FourWheelerVehicle(FourWheelerVehicle::currId);
    IVehicle *v11 = new FourWheelerVehicle(FourWheelerVehicle::currId);
    IVehicle *v12 = new FourWheelerVehicle(FourWheelerVehicle::currId);

    std::cout << "\n--- Simulating Ticket Allocations ---" << std::endl;

    std::queue<Ticket *> activeTickets;

    IVehicle *twoWheelers[] = {v1, v2, v3, v4, v5};
    for (auto v : twoWheelers)
    {
        Ticket *t = manager.allocateLot(v);
        if (t)
        {
            activeTickets.push(t);
        }
        else
        {
            std::cout << std::format("Allocation Failed: No parking lot available for Vehicle-{}", v->getId()) << std::endl;
        }
    }

    IVehicle *fourWheelers[] = {v10, v11, v12};
    for (auto v : fourWheelers)
    {
        Ticket *t = manager.allocateLot(v);
        if (t)
        {
            activeTickets.push(t);
        }
        else
        {
            std::cout << std::format("Allocation Failed: No parking lot available for Vehicle-{}", v->getId()) << std::endl;
        }
    }

    std::cout << "\n--- Simulating Vehicle Releases ---" << std::endl;

    if (!activeTickets.empty())
    {
        std::cout << "Releasing earliest parked vehicle..." << std::endl;
        manager.releaseLot(activeTickets.front());
        activeTickets.pop();
    }

    std::cout << "\n--- Retesting Allocation on Recently Freed Space ---" << std::endl;

    Ticket *retryTicket = manager.allocateLot(v5);
    if (retryTicket)
    {
        activeTickets.push(retryTicket);
    }

    std::cout << "\n--- Cleaning up Remainder Memory ---" << std::endl;

    while (!activeTickets.empty())
    {
        manager.releaseLot(activeTickets.front());
        activeTickets.pop();
    }

    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete v5;
    delete v6;
    delete v7;
    delete v8;
    delete v9;
    delete v10;
    delete v11;
    delete v12;

    delete a1;
    delete a2;
    delete a3;
    delete a4;
    delete b1;
    delete b2;
    delete b3;
    delete c1;
    delete c2;

    std::cout << "Testing completed successfully!" << std::endl;
    return 0;
}