#pragma once
#include "../interfaces/IVehicle.hpp"

class TwoWheelerVehicle : public IVehicle
{
private:
    int id;

public:
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
    int getId() const override
    {
        return id;
    }
};