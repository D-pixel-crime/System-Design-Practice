#pragma once
#include "player.hpp"
#include <vector>
#include <unordered_map>
#include <random>
#include <iostream>

class Board
{
private:
    int lim;
    bool ongoing;
    std::vector<Player> players;
    std::unordered_map<int, int> ladders, snakes;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dice;

    bool move(Player &p);

    void endGame();

public:
    Board(int _end, std::vector<std::vector<int>> &_snakes, std::vector<std::vector<int>> &_ladders);

    template <typename... AllPlayers>
    Board(int _lim, std::vector<std::vector<int>> &_snakes, std::vector<std::vector<int>> &_ladders, AllPlayers... allPlayers) : lim(_lim), ongoing(false), gen(rd()), dice(1, 6)
    {
        addPlayers(allPlayers...);
        addSnakes(_snakes);
        addLadders(_ladders);
    }

    void addPlayers() {};

    template <typename... Rest>
    void addPlayers(const Player &p1, Rest... rest)
    {
        if (ongoing)
        {
            std::cout << "\nA Game is still ongoing! Come Later.\n\n";
            return;
        }

        players.push_back(p1);
        addPlayers(rest...);
    }

    void addSnakes(std::vector<std::vector<int>> &_snakes);

    void addLadders(std::vector<std::vector<int>> &_ladders);

    void playGame();
};