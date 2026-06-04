#include "../include/parkingManager.hpp"
#include "../include/ticket.hpp"
#include <typeinfo>
#include <chrono>

Ticket *ParkingManager::allocateLot(IVehicle *_vehicle)
{
    if (!parkingLots.count(_vehicle) || parkingLots[_vehicle].empty())
    {
        return nullptr;
    }

    auto now = std::chrono::system_clock::now();
    std::chrono::sys_days days_point = std::chrono::time_point_cast<std::chrono::days>(now);
    unsigned day = (std::chrono::weekday{days_point}).c_encoding();

    int entryTime = 0, exitTime = 5;
    IParkingLot *availableLot = *parkingLots[_vehicle].begin();
    parkingLots[_vehicle].erase(availableLot);
    availableLot->occupyLot(_vehicle);
    ICostStrategy *costStrat = nullptr;

    if (typeid(*_vehicle) == typeid(TwoWheelerVehicle))
    {
        costStrat = new TwoWheelerNormalCostStrategy(20.0);
    }
    else if (typeid(*_vehicle) == typeid(ThreeWheelerVehicle))
    {
        costStrat = new ThreeWheelerNormalCostStrategy(30.0);
    }
    else if (typeid(*_vehicle) == typeid(FourWheelerVehicle))
    {
        if (day < 5)
        {
            costStrat = new FourWheelerNormalCostStrategy(40.0);
        }
        else
        {
            costStrat = new FourWheelerTaxCostStrategy(40.0, 25.0);
        }
    }

    Ticket *ticket = new Ticket(Ticket::currTickets, entryTime, exitTime, availableLot, _vehicle);
    if (day >= 5)
    {
        ticket->chargeCost({costStrat, new HolidayExtraCostStrategy(100.0)});
    }
    else
    {
        ticket->chargeCost({costStrat});
    }

    delete costStrat;
    return ticket;
}

void ParkingManager::releaseLot(Ticket *_ticket)
{
    IParkingLot *busyLot = _ticket->getLotID();
    busyLot->freeLot();
    parkingLots[busyLot->getVehicleType()].insert(busyLot);

    delete _ticket;
}