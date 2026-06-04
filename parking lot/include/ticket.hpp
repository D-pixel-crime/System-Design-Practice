#pragma once
#include "../include/parkingLot.hpp"
#include "../include/vehicle.hpp"
#include "../include/costStrategy.hpp"
#include <utility>
#include <vector>

class Ticket
{
private:
    int id;
    int entryTime;
    int exitTime;
    IParkingLot *lotID;
    IVehicle *vehicleID;

public:
    inline static int currTickets = 0;

    Ticket(int _id, int _entryTime, int _exitTIme, IParkingLot *_lotID, IVehicle *_vehicleID);

    std::pair<int, int> getEntryAndExitTime();
    void chargeCost(const std::vector<ICostStrategy *> &costStrats);
    IParkingLot *getLotID();
};