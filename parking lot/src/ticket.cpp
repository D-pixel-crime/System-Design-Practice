#include "../include/ticket.hpp"
#include <iostream>
#include <format>

Ticket::Ticket(int _id, int _entryTime, int _exitTIme, IParkingLot *_lotID, IVehicle *_vehicleID) : id{_id}, entryTime{_entryTime}, exitTime{_exitTIme}, lotID{_lotID}, vehicleID{_vehicleID}
{
    currTickets++;
}

std::pair<int, int> Ticket::getEntryAndExitTime()
{
    return std::make_pair(entryTime, exitTime);
}

void Ticket::chargeCost(const std::vector<ICostStrategy *> &costStrats)
{
    double toPay = 0.0;
    for (auto &c : costStrats)
    {
        toPay += c->calculateCost(this);
    }

    std::cout << std::format("Vehicle-{} payed {} for Parking-Lot-{}", vehicleID->getId(), toPay, lotID->getId()) << std::endl;
}

IParkingLot *Ticket::getLotID()
{
    return lotID;
}
