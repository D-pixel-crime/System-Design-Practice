#pragma once
#include "../interfaces/ICostStrategy.hpp"
#include "../include/ticket.hpp"

class TwoWheelerNormalCostStrategy : public ICostStrategy
{
private:
    double hourlyCost;

public:
    TwoWheelerNormalCostStrategy(double _hCost) : hourlyCost(_hCost) {}

    double calculateCost(Ticket *_ticket) override;
};

class ThreeWheelerNormalCostStrategy : public ICostStrategy
{
private:
    double hourlyCost;

public:
    ThreeWheelerNormalCostStrategy(double _hCost) : hourlyCost(_hCost) {}

    double calculateCost(Ticket *_ticket) override;
};

class FourWheelerNormalCostStrategy : public ICostStrategy
{
private:
    double hourlyCost;

public:
    FourWheelerNormalCostStrategy(double _hCost) : hourlyCost(_hCost) {}

    double calculateCost(Ticket *_ticket) override;
};

class FourWheelerTaxCostStrategy : public ICostStrategy
{
private:
    double hourlyCost;
    double taxPercent;

public:
    FourWheelerTaxCostStrategy(double _hCost, double _taxPercent) : hourlyCost(_hCost), taxPercent(_taxPercent) {}

    double calculateCost(Ticket *_ticket) override;
};

class HolidayExtraCostStrategy : public ICostStrategy
{
private:
    double extraCost;

public:
    HolidayExtraCostStrategy(double _extraCost) : extraCost(_extraCost) {}

    double calculateCost(Ticket *_ticket = nullptr) override;
};