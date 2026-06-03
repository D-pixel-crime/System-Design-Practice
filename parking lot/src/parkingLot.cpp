#include "../include/parkingLot.hpp"
#include <iostream>

CommonParkingLot::CommonParkingLot(int _id) : id{_id}, occupied{false} {}

bool CommonParkingLot::isOccupied() const
{
    return occupied;
}

void CommonParkingLot::occupyLot(Vehicle *_vehicle)
{
    if (occupied)
    {
        std::cout << "Parking Lot Already Occupied!" << std::endl;
        return;
    }
    parkedVehicle = _vehicle;
    occupied = true;
}

void CommonParkingLot::freeLot()
{
    if (!occupied)
    {
        std::cout << "Parking Lot Already Free!" << std::endl;
        return;
    }
    parkedVehicle = nullptr;
    occupied = false;
}