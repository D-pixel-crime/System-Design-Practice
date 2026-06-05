#pragma once
#include "../interfaces/IParkingLot.hpp"
#include "../interfaces/IVehicle.hpp"
#include <typeindex>

class CommonParkingLot : public IParkingLot
{
private:
    int id;
    bool occupied;
    std::type_index vehicleType;
    IVehicle *parkedVehicle;

public:
    inline static int currLot = 0;

    CommonParkingLot(int _id, std::type_index _vehicleType);

    bool isOccupied() const override;
    void occupyLot(IVehicle *_vehicle) override;
    void freeLot() override;
    int getId() const override;
    std::type_index getVehicleType() const override;
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