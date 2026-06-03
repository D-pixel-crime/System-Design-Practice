#pragma once
#include "parkingLot.hpp"
#include "vehicle.hpp"
#include <vector>

class Ticket;

class ParkingManager
{
private:
    int profit;
    std::vector<IParkingLot *> lots;

public:
    Ticket *allocateLot(IVehicle *_vehicle);
    void releaseLot(Ticket *_ticket);
};