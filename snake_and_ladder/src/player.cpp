#include "../include/player.hpp"

Player::Player(std::string _name) : name(_name), pos(0) {}

void Player::setPos(int _pos)
{
    pos = _pos;
}

int Player::getPos()
{
    return pos;
}

const std::string &Player::getName()
{
    return name;
}