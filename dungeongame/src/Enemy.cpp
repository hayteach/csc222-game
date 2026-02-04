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

using namespace std; // Standard namespace

// ADT relevance (Week 02):
// - `Enemy` is a `Character`-derived element type that can be stored in ADTs
//   such as `EnemyGroup` or other containers. When stored in contiguous
//   containers, pointers to elements (from `.data()`) can be used for
//   traversal and pointer arithmetic in exercises.
// - Pointer and lifetime safety: a pointer returned from a container (raw or
//   via `data()`) is only valid while the container isn't resized or destroyed.
//   Use tests to illustrate safe usage and to discuss ownership semantics.

namespace dungeongame {

    // Enemy::Enemy(const string& name, int hp, int attack)
    //     : Character(name, hp), attackPower(attack) {}

    Enemy::Enemy(const string& name, int hp, int attack, int def, int exp, int gold)
        : Character(name, hp), attackPower(attack), expReward(exp), goldReward(gold) {
        // keep derived/base stats in sync
        this->attack = attackPower;
        this->defense = def;
        this->maxHealth = hp;
        this->health = hp;
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
