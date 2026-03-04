/* File: NPC.h (renamed from Enemy.h)
   Name: CSC 222 Students
   Date: 01/28/2026
   Last Edit: 01/28/2026
   Course: CSC 222 - Programming and Algorithms II
   Desc: Declaration for NPC class derived from Character used in the Dungeon game.
    Usage: Include this header when using NPC or derived classes.
  
        Other files required: Character.h, Player.h, Game.h, Game.cpp,
                              Character.cpp, Player.cpp
*/
#pragma once

#include <string>

#include "Character.h"

namespace dungeongame {

class NPC : public Character {
private:
    int attackPower;
    int expReward;
    int goldReward;
public:
    // signature: name, hp, attack, defense, exp reward, gold reward
    NPC(const std::string& name = "NPC", int hp = 10, int attack = 1, int def = 0,
          int exp = 20, int gold = 5);

    int getAttackPower() const;
   
    int getExpReward() const;
    int getGoldReward() const;

    // Simple AI: move towards the player's coordinates (to be implemented by students)
    void takeDamage(int d);
    void moveTowards(int playerX, int playerY);
    
};

} // namespace dungeongame
