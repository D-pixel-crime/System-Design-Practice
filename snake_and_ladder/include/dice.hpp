#pragma once
#include <random>

class Dice
{
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> distr;

public:
    Dice() : gen(rd()), distr(1, 6) {};

    int rollDice()
    {
        return distr(gen);
    }
};