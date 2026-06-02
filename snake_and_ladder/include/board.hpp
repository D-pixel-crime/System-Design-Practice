#pragma once
#include <unordered_map>
#include <vector>

class Game;

class Board
{
private:
    int lim;
    std::unordered_map<int, int> ladders, snakes;

public:
    Game *currGame = nullptr;

    Board(int _end, std::vector<std::vector<int>> &_snakes, std::vector<std::vector<int>> &_ladders);

    void addSnakes(std::vector<std::vector<int>> &_snakes);

    void addLadders(std::vector<std::vector<int>> &_ladders);

    bool isLadderThere(int &pos)
    {
        return ladders.count(pos);
    }

    bool isSnakeThere(int &pos)
    {
        return snakes.count(pos);
    }

    int getSnakeTail(int &pos)
    {
        return snakes[pos];
    }

    int getLadderTop(int &pos)
    {
        return ladders[pos];
    }

    int &getLim()
    {
        return lim;
    }
};