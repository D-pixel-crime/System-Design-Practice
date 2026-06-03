#pragma once
#include "../interfaces/IParkingLot.hpp"

class CommonParkingLot : public IParkingLot
{
private:
    int id;
    bool occupied;
    Vehicle *parkedVehicle;

public:
    CommonParkingLot(int _id);

    bool isOccupied() const override;
    void occupyLot(Vehicle *_vehicle) override;
    void freeLot() override;
    int getId() const override
    {
        return id;
    }
};

class TwoWheelerParkingLot : public CommonParkingLot
{
    using CommonParkingLot::CommonParkingLot; // Helps in inheriting constructors
};
class ThreeWheelerParkingLot : public CommonParkingLot
{
    using CommonParkingLot::CommonParkingLot;
};
class FourWheelerParkingLot : public CommonParkingLot
{
    using CommonParkingLot::CommonParkingLot;
};