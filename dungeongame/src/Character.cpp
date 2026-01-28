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
#include <iostream>
#include <algorithm>

namespace dungeongame {

    Character::Character(const std::string& name, int hp)
        : name(name), health(hp), maxHealth(hp), attack(1), defense(0), pos{0, 0} {}

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

    int Character::getMaxHealth() const {
        return maxHealth;
    }

    int Character::getAttack() const {
        return attack;
    }

    int Character::getDefense() const {
        return defense;
    }

    void Character::takeDamage(int damage) {
        // Simple damage application (damage already calculated by attacker)
        health -= damage;
        if (health < 0) health = 0;
    }

    int Character::calculateAttack() const {
        // Default: return base attack (override for special behaviors)
        return attack;
    }

    void Character::heal(int amount) {
        if (amount <= 0) return;
        health = std::min(maxHealth, health + amount);
    }

    void Character::displayStats() const {
        std::cout << "\n--- " << name << " Stats ---\n";
        std::cout << "Health: " << health << " / " << maxHealth << "\n";
        std::cout << "Attack: " << attack << "\n";
        std::cout << "Defense: " << defense << "\n";
        std::cout << "Position: (" << pos.x << ", " << pos.y << ")\n";
    }

    bool Character::isAlive() const {
        return health > 0;
    }

}