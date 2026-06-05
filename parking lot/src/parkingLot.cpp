#include "../include/parkingLot.hpp"
#include <iostream>
#include <format>

CommonParkingLot::CommonParkingLot(int _id, std::type_index _vehicleType) : id{_id}, occupied{false}, vehicleType{_vehicleType}
{
    currLot++;
}

bool CommonParkingLot::isOccupied() const
{
    return occupied;
}

void CommonParkingLot::occupyLot(IVehicle *_vehicle)
{
    if (occupied)
    {
        std::cout << std::format("Parking-Lot-{} ALREADY OCCUPIED!", id) << std::endl;
        return;
    }

    std::cout << std::format("Parking-Lot-{} is NOW OCCUPIED by Vehicle-{}", id, _vehicle->getId()) << std::endl;

    parkedVehicle = _vehicle;
    occupied = true;
}

void CommonParkingLot::freeLot()
{
    if (!occupied)
    {
        std::cout << std::format("Parking-Lot-{} ALREADY FREE!", id) << std::endl;
        return;
    }

    std::cout << std::format("Parking-Lot-{} is NOW FREE!", id) << std::endl;

    parkedVehicle = nullptr;
    occupied = false;
}

int CommonParkingLot::getId() const
{
    return id;
}

std::type_index CommonParkingLot::getVehicleType() const
{
    return vehicleType;
}