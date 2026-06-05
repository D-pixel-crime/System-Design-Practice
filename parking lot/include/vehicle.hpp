#pragma once
#include "../interfaces/IVehicle.hpp"

class TwoWheelerVehicle : public IVehicle
{
private:
    int id;

public:
    inline static int currId = 0;

    TwoWheelerVehicle(int _id) : id{_id}
    {
        currId++;
    };

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
    inline static int currId = 0;

    ThreeWheelerVehicle(int _id) : id{_id}
    {
        currId++;
    };

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
    inline static int currId = 0;

    FourWheelerVehicle(int _id) : id{_id}
    {
        currId++;
    };

    int getId() const override
    {
        return id;
    }
};