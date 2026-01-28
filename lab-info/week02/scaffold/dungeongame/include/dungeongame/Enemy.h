#pragma once

#include "Character.h"

namespace dungeongame {

class Enemy : public Character {
private:
    int attackPower;
public:
    Enemy(const std::string& name = "Enemy", int hp = 10, int attack = 1);

    int getAttackPower() const;
    void takeDamage(int d);

    // Simple AI: move towards the player's coordinates (to be implemented by students)
    void moveTowards(int playerX, int playerY);
};

} // namespace dungeongame
