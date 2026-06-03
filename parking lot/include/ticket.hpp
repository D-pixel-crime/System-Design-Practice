#pragma once
#include "../include/parkingLot.hpp"
#include "../include/vehicle.hpp"
#include "../include/costStrategy.hpp"
#include <utility>

class Ticket
{
private:
    int id;
    int entryTime;
    int exitTime;
    IParkingLot *lotID;
    IVehicle *vehicleID;
    ICostStrategy *costStrat;

public:
    Ticket(int _id, int _entryTime, int _exitTIme, IParkingLot *_lotID, IVehicle *_vehicleID, ICostStrategy *_costStrat);

    std::pair<int, int> getEntryAndExitTime();
    void chargeCost();
};