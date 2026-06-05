#pragma once
#include "parkingLot.hpp"
#include "vehicle.hpp"
#include <unordered_map>
#include <set>
#include <typeindex>

class Ticket;

class ParkingManager
{
private:
    int profit;
    std::unordered_map<std::type_index, std::set<IParkingLot *>> parkingLots;

public:
    template <typename... Lots>
    ParkingManager(Lots... parkingLots) : profit(0)
    {
        addParkingLot(parkingLots...);
    }

    void addParkingLot() {}

    template <typename... Lots>
    void addParkingLot(IParkingLot *p1, Lots... lots)
    {
        std::type_index vehicleType = p1->getVehicleType();
        parkingLots[vehicleType].insert(p1);
        addParkingLot(lots...);
    }

    Ticket *allocateLot(IVehicle *_vehicle);
    void releaseLot(Ticket *_ticket);
};