#include "../include/costStrategy.hpp"

double TwoWheelerNormalCostStrategy::calculateCost(Ticket *_ticket)
{
    auto [s, e] = _ticket->getEntryAndExitTime();
    return hourlyCost * (e - s);
}

double ThreeWheelerNormalCostStrategy::calculateCost(Ticket *_ticket)
{
    auto [s, e] = _ticket->getEntryAndExitTime();
    return hourlyCost * (e - s);
}

double FourWheelerNormalCostStrategy::calculateCost(Ticket *_ticket)
{
    auto [s, e] = _ticket->getEntryAndExitTime();
    return hourlyCost * (e - s);
}

double FourWheelerTaxCostStrategy::calculateCost(Ticket *_ticket)
{
    auto [s, e] = _ticket->getEntryAndExitTime();
    auto normalCost = hourlyCost * (e - s);
    return normalCost + (hourlyCost * (taxPercent / 100.0));
}

double HolidayExtraCostStrategy::calculateCost(Ticket *_ticket)
{
    return extraCost;
}