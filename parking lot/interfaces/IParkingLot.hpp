#pragma once

class Vehicle;

// Parking Lot Interface
class IParkingLot
{
public:
    virtual ~IParkingLot() = default;

    virtual bool isOccupied() const = 0;
    virtual void occupyLot(Vehicle *_vehicle) = 0;
    virtual void freeLot() = 0;
    virtual int getId() const = 0;
};