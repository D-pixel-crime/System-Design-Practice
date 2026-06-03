#pragma once

class IVehicle
{
public:
    ~IVehicle() = default;

    virtual int getId() const = 0;
};