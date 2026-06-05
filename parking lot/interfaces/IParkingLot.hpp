#pragma once
#include <typeindex>

class IVehicle;
class IParkingLot;

// Parking Lot Interface
class IParkingLot
{
public:
    virtual ~IParkingLot() = default;

    virtual bool isOccupied() const = 0;
    virtual void occupyLot(IVehicle *_vehicle) = 0;
    virtual void freeLot() = 0;
    virtual int getId() const = 0;
    virtual std::type_index getVehicleType() const = 0;
};