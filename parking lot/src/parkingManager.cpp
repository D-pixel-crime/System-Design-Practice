#include "../include/parkingManager.hpp"
#include "../include/ticket.hpp"
#include <typeinfo>
#include <typeindex>
#include <chrono>
#include <iostream>

Ticket *ParkingManager::allocateLot(IVehicle *_vehicle)
{
    std::type_index vehicleType = std::type_index(typeid(*_vehicle));

    if (!parkingLots.count(vehicleType) || parkingLots[vehicleType].empty())
    {
        return nullptr;
    }

    auto now = std::chrono::system_clock::now();
    std::chrono::sys_days days_point = std::chrono::time_point_cast<std::chrono::days>(now);
    unsigned day = (std::chrono::weekday{days_point}).c_encoding();

    int entryTime = 0, exitTime = 5;
    IParkingLot *availableLot = *parkingLots[vehicleType].begin();
    parkingLots[vehicleType].erase(availableLot);
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
        if (day > 0 && day < 6)
        {
            costStrat = new FourWheelerNormalCostStrategy(40.0);
        }
        else
        {
            costStrat = new FourWheelerTaxCostStrategy(40.0, 25.0);
        }
    }

    Ticket *ticket = new Ticket(Ticket::currTickets, entryTime, exitTime, availableLot, _vehicle);
    if (day == 0 || day == 6)
    {
        ticket->chargeCost({costStrat, new HolidayExtraCostStrategy(100.0)});
    }
    else
    {
        ticket->chargeCost({costStrat});
    }

    availableLot->occupyLot(_vehicle);
    std::cout << std::endl;

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