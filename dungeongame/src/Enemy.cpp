/*  File: Enemy.cpp
    Name: CSC 222 Students
    Date: 01/28/2026
    Last Edit: 01/28/2026
    Course: CSC 222 - Programming and Algorithms II
    Desc: Implementation for Enemy class used in the Dungeon of Data Structures game.
    Usage: Include this source when building Enemy or derived classes.
  
    Other files required: Character.h, Player.h, Game.h, Game.cpp,
                              Character.cpp, Player.cpp, Enemy.h
*/

#include "Enemy.h"

namespace dungeongame {

    // Enemy::Enemy(const std::string& name, int hp, int attack)
    //     : Character(name, hp), attackPower(attack) {}

    Enemy::Enemy(const std::string& name, int hp, int attack, int def, int exp, int gold)
        : Character(name, hp), attackPower(attack), defense(def), maxHealth(hp), expReward(exp), goldReward(gold) {
        // Nothing else needed here; Character initialized health.
    }

    int Enemy::getAttackPower() const {
        return attackPower;
    }

    void Enemy::takeDamage(int d) {
        health -= d;
        if (health < 0) health = 0;
    }

    void Enemy::moveTowards(int playerX, int playerY) {
        // Very small example implementation: move one step towards player
        if (pos.x < playerX) pos.x += 1;
        else if (pos.x > playerX) pos.x -= 1;

        if (pos.y < playerY) pos.y += 1;
        else if (pos.y > playerY) pos.y -= 1;
    }
    int Enemy::getExpReward() const { return expReward; }
    int Enemy::getGoldReward() const { return goldReward; }

} // namespace dungeongame
