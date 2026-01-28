/* File: Character.cpp
   Name: CSC 222 Students
   Date: 01/28/2026
   Last Edit: 01/28/2026
   Course: CSC 222 - Programming and Algorithms II
   Desc: Character class implementation for the Dungeon of Data Structures game.
    Usage: Compile and run the program to start the game.
  
    Other files required: Player.h, Game.h, Game.cpp,
                              Character.cpp, Player.cpp
*/
#include "Character.h"

namespace dungeongame {

Character::Character(const std::string& name, int hp)
    : name(name), health(hp), pos{0, 0} {}

const Position& Character::getPosition() const {
    return pos;
}

void Character::setPosition(int x, int y) {
    pos.x = x;
    pos.y = y;
}

const std::string& Character::getName() const {
    return name;
}

int Character::getHealth() const {
    return health;
}
}