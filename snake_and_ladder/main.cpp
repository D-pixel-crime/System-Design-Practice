#include "include/player.hpp"
#include "include/board.hpp"
#include "include/game.hpp"
#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int lim = 100;
    std::vector<std::vector<int>> ladders{{2, 11}, {5, 45}, {20, 90}, {30, 85}, {45, 78}, {68, 95}};
    std::vector<std::vector<int>> snakes{{12, 3}, {40, 5}, {39, 15}, {50, 20}, {67, 21}, {87, 1}};

    Player p1("Mike");
    Player p2("Tike");
    Player p3("Spike");
    Player p4("Nike");
    Player p5("Rike");

    Board b(100, snakes, ladders);
    Dice d;

    Game g(&b, &d, &p1, &p2, &p3, &p4, &p5);

    g.playGame();

    return 0;
}