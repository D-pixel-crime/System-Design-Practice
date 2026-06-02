#include "../include/board.hpp"
#include "../include/game.hpp"
#include <algorithm>
#include <iostream>

void Board::addSnakes(std::vector<std::vector<int>> &_snakes)
{
    if (currGame && currGame->isOngoing())
    {
        std::cout << "\nA Game is still ongoing! Come Later.\n\n";
        return;
    }

    for (auto &i : _snakes)
    {
        if (!snakes.count(i[0]) && i[1] && !snakes.count(i[1]) && !ladders.count(i[1]) && i[0] > i[1])
        {
            snakes[i[0]] = i[1];
        }
    }
}

void Board::addLadders(std::vector<std::vector<int>> &_ladders)
{
    if (currGame && currGame->isOngoing())
    {
        std::cout << "\nA Game is still ongoing! Come Later.\n\n";
        return;
    }

    for (auto &i : _ladders)
    {
        if (!ladders.count(i[0]) && i[0] && !ladders.count(i[1]) && !snakes.count(i[1]) && i[0] < i[1])
        {
            ladders[i[0]] = i[1];
        }
    }
}

Board::Board(int _lim, std::vector<std::vector<int>> &_snakes, std::vector<std::vector<int>> &_ladders) : lim(_lim)
{
    addSnakes(_snakes);
    addLadders(_ladders);
}
