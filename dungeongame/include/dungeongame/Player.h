/* File: Player.h
   Name: CSC 222 Students
   Date: 01/28/2026
   Last Edit: 01/28/2026
   Course: CSC 222 - Programming and Algorithms II
   Desc: Declaration for Player class used in the Dungeon of Data Structures game.
    Usage: Include this header when using Player.
  
        Other files required: Character.h, Player.h, Game.h, Game.cpp,
                              Character.cpp, Player.cpp
*/
#pragma once

#include "Character.h"

namespace dungeongame {

class Player : public Character {
private:
    int level;
    int gold;
public:
    Player(const std::string& name = "Player");

    // Movement within a bounded map (map bounds enforced by caller)
    void move(int dx, int dy);
    void displayStats() const;
};

} // namespace dungeongame