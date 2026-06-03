#include "../include/ticket.hpp"
#include <iostream>
#include <format>

Ticket::Ticket(int _id, int _entryTime, int _exitTIme, IParkingLot *_lotID, IVehicle *_vehicleID, ICostStrategy *_costStrat) : id{_id}, entryTime{_entryTime}, exitTime{_exitTIme}, lotID{_lotID}, vehicleID{_vehicleID}, costStrat{_costStrat} {}

void Ticket::chargeCost()
{
    auto toPay = costStrat->calculateCost(this);
    std::cout << std::format("Vehicle-{} payed {} for Parking-Lot-{}", vehicleID->getId(), toPay, lotID->getId()) << std::endl;
}

std::pair<int, int> Ticket::getEntryAndExitTime()
{
    return std::make_pair(entryTime, exitTime);
}