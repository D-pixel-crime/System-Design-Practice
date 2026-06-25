#pragma once

class I_Product
{
private:
    int cnt;

public:
    virtual ~I_Product() = default;

    virtual void updateCount() = 0;

    virtual int getAvailability() const = 0;
};