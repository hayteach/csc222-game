/* File: Player.cpp
   Name: CSC 222 Students
   Date: 01/28/2026
   Last Edit: 01/28/2026
   Course: CSC 222 - Programming and Algorithms II
   Desc: Player class implementation for the Dungeon of Data Structures game.
    Usage: Compile and run the program to start the game.
  
        Other files required: Character.h, Player.h, Game.h, Game.cpp,
                              Character.cpp, Player.cpp
*/
#include "Player.h"
#include <iostream>

namespace dungeongame {

Player::Player(const std::string& name)
    : Character(name, 20), level(1), gold(0) {
    // start near top-left corner (0,0)
    pos.x = 0;
    pos.y = 0;
}

void Player::move(int dx, int dy) {
    int newX = pos.x + dx;
    int newY = pos.y + dy;

    // Keep player inside the 0..4 range (matches Game map size)
    if (newX < 0) newX = 0;
    if (newY < 0) newY = 0;
    if (newX > 4) newX = 4;
    if (newY > 4) newY = 4;

    pos.x = newX;
    pos.y = newY;
}

void Player::displayStats() const {
    std::cout << "\n--- Player Stats ---\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Health: " << health << "\n";
    std::cout << "Level: " << level << "\n";
    std::cout << "Gold: " << gold << "\n";
    std::cout << "Position: (" << pos.x << ", " << pos.y << ")\n";
}

}

// appended namespace close