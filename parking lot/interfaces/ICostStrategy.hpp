#pragma once

class Ticket;

class ICostStrategy
{
public:
    virtual ~ICostStrategy() = default;

    virtual double calculateCost(Ticket *_ticket) = 0;
};