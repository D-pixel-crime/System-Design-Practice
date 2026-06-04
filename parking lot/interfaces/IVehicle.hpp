#pragma once

class IVehicle
{
public:
    virtual ~IVehicle() = default;

    virtual int getId() const = 0;
};