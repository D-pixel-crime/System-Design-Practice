#pragma once
#include <string>

class Player
{
private:
    std::string name;
    int pos;

public:
    Player(std::string _name);

    void setPos(int _pos);

    int getPos();

    const std::string &getName();
};