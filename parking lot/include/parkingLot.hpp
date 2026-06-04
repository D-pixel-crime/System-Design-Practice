#pragma once
#include "../interfaces/IParkingLot.hpp"
#include "../interfaces/IVehicle.hpp"

class CommonParkingLot : public IParkingLot
{
private:
    int id;
    bool occupied;
    IVehicle *vehicleType;
    IVehicle *parkedVehicle;

public:
    CommonParkingLot(int _id);

    bool isOccupied() const override;
    void occupyLot(IVehicle *_vehicle) override;
    void freeLot() override;
    int getId() const override;
    IVehicle *getVehicleType() const override;
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