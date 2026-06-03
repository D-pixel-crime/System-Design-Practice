#pragma once
#include "../include/ticket.hpp"

class ICostStrategy
{
public:
    ~ICostStrategy() = default;

    virtual double calculateCost(Ticket *_ticket) = 0;
};