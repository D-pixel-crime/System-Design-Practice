#include "../include/game.hpp"
#include <format>
#include <algorithm>
#include <iostream>

Game::Game(Board *_board, Dice *_dice) : board{_board}, dice{_dice}
{
    board->currGame = this;
}

bool Game::move(Player *&p)
{
    int m = dice->rollDice();
    int oldPos = p->getPos();
    int newPos = p->getPos() + m;
    if (newPos <= board->getLim())
    {
        if (board->isLadderThere(newPos))
        {
            std::cout << std::format("({} climbed a ladder!)", p->getName());
            newPos = board->getLadderTop(newPos);
        }
        else if (board->isSnakeThere(newPos))
        {
            std::cout << std::format("({} found a snake!)", p->getName());
            newPos = board->getSnakeTail(newPos);
        }

        p->setPos(newPos);

        std::cout << std::format("Moved {} from {} to {}", p->getName(), oldPos, newPos) << std::endl;
    }

    return p->getPos() == board->getLim();
}

void Game::playGame()
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

void Game::endGame()
{
    std::sort(players.begin(), players.end(), [&](Player *&a, Player *&b)
              { return a->getPos() > b->getPos(); });

    std::cout << "\nGame Finished!\nThe Rankings of this game are:"
              << std::endl;
    for (auto &p : players)
    {
        std::cout << p->getName() << " -> " << p->getPos() << std::endl;
    }

    std::cout << "\nAll the players are now removed! Please add new players for next game.\n ";

    players.clear();
    ongoing = false;
    board->currGame = nullptr;
}