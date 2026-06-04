#pragma once
#include "../interfaces/IVehicle.hpp"

class TwoWheelerVehicle : public IVehicle
{
private:
    int id;

public:
    TwoWheelerVehicle(int _id) : id{_id} {};

    int getId() const override
    {
        return id;
    }
};

class ThreeWheelerVehicle : public IVehicle
{
private:
    int id;

public:
    ThreeWheelerVehicle(int _id) : id{_id} {};

    int getId() const override
    {
        return id;
    }
};

class FourWheelerVehicle : public IVehicle
{
private:
    int id;

public:
    FourWheelerVehicle(int _id) : id{_id} {};

    int getId() const override
    {
        return id;
    }
};