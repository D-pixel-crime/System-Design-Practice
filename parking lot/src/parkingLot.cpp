#include "../include/parkingLot.hpp"
#include <iostream>
#include <format>

CommonParkingLot::CommonParkingLot(int _id) : id{_id}, occupied{false} {}

bool CommonParkingLot::isOccupied() const
{
    return occupied;
}

void CommonParkingLot::occupyLot(IVehicle *_vehicle)
{
    if (occupied)
    {
        std::cout << "Parking Lot Already Occupied!" << std::endl;
        return;
    }

    std::cout << std::format("Parking-Lot-{} is now OCCUPIED by Vehicle-{}", id, _vehicle->getId()) << std::endl;

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

    std::cout << std::format("Parking-Lot-{} is not FREE!", id) << std::endl;

    parkedVehicle = nullptr;
    occupied = false;
}

int CommonParkingLot::getId() const
{
    return id;
}

IVehicle *CommonParkingLot::getVehicleType() const
{
    return vehicleType;
}