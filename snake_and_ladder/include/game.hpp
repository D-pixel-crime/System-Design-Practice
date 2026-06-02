#pragma once
#include "dice.hpp"
#include "player.hpp"
#include "board.hpp"
#include <vector>

class Game
{
private:
    bool ongoing;
    std::vector<Player *> players;
    Board *board;
    Dice *dice;

    bool move(Player *&p);

    void endGame();

public:
    Game(Board *_board, Dice *_dice);

    template <typename... AllPlayers>
    Game(Board *_board, Dice *_dice, AllPlayers... allPlayers) : board{_board}, dice{_dice}
    {
        addPlayers(allPlayers...);
        board->currGame = this;
    }

    void addPlayers() {}

    template <typename... Rest>
    void addPlayers(Player *&p1, Rest... rest)
    {
        players.push_back(p1);
        addPlayers(rest...);
    }

    void playGame();

    bool isOngoing()
    {
        return ongoing;
    }
};