#include "../include/board.hpp"
#include "../include/player.hpp"
#include <algorithm>
#include <iostream>
#include <format>

void Board::addSnakes(std::vector<std::vector<int>> &_snakes)
{
    if (ongoing)
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
    if (ongoing)
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

Board::Board(int _lim, std::vector<std::vector<int>> &_snakes, std::vector<std::vector<int>> &_ladders) : lim(_lim), ongoing(false), gen(rd()), dice(1, 6)
{
    addSnakes(_snakes);
    addLadders(_ladders);
}

bool Board::move(Player &p)
{
    int oldPos = p.getPos();
    int newPos = p.getPos() + dice(gen);
    if (newPos <= lim)
    {
        if (ladders.count(newPos))
        {
            std::cout << std::format("({} climbed a ladder!)", p.getName());
            newPos = ladders[newPos];
        }
        else if (snakes.count(newPos))
        {
            std::cout << std::format("({} found a snake!)", p.getName());
            newPos = snakes[newPos];
        }

        p.setPos(newPos);

        std::cout << std::format("Moved {} from {} to {}", p.getName(), oldPos, newPos) << std::endl;
    }

    return p.getPos() == lim;
}

void Board::playGame()
{
    if (ongoing)
    {
        std::cout << "\nA Game is still ongoing! Come Later.\n\n";
        return;
    }
    if (players.size() < 2)
    {
        std::cout << "\nInsufficient players to start a game!\n\n";
        return;
    }

    std::cout << "\nStarting game NOW!\n";
    ongoing = true;
    int curr = 0;
    while (!move(players[curr]))
    {
        curr = (curr + 1) % ((int)players.size());
    }
    endGame();
}

void Board::endGame()
{
    std::sort(players.begin(), players.end(), [&](Player &a, Player &b)
              { return a.getPos() > b.getPos(); });

    std::cout << "\nGame Finished!\nThe Rankings of this game are:"
              << std::endl;
    for (auto &p : players)
    {
        std::cout << p.getName() << " -> " << p.getPos() << std::endl;
    }

    std::cout << "\nAll the players are now removed! Please add new players for next game.\n ";

    players.clear();
    ongoing = false;
}
