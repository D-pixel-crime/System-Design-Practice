#pragma once
#include "parkingLot.hpp"
#include "vehicle.hpp"
#include <unordered_map>
#include <set>

class Ticket;

class ParkingManager
{
private:
    int profit;
    std::unordered_map<IVehicle *, std::set<IParkingLot *>> parkingLots;

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
        parkingLots[p1->getVehicleType()].insert(p1);
        addParkingLot(lots...);
    }

    Ticket *allocateLot(IVehicle *_vehicle);
    void releaseLot(Ticket *_ticket);
};