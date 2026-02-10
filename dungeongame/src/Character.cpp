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

using namespace std; // Standard namespace

// Notes (Week 02 - ADTs & Pointers):
// - `Character` is a concrete type that defines state and behavior for game
//   entities (e.g., Player, Enemy). In the context of ADTs, `Character` is
//   the element type that ADTs will store and manage.
// - Contiguous storage: when many `Character`-derived objects are stored in a
//   contiguous container (an array or `std::vector`), the objects are laid out
//   consecutively in memory. This lets students practice pointer arithmetic
//   and raw pointer traversal (e.g., `T* p = container.data(); p + 1` points
//   to the next object). Emphasize that pointer arithmetic relies on
//   contiguous layout; it is not meaningful on non-contiguous structures.
// - Data abstraction point: `Character` provides the *interface* (methods and
//   invariants), while ADTs manage *how* many Characters are stored and how
//   they are accessed. Keep these concerns separated in design and tests.

namespace dungeongame {

    Character::Character(const string& name, int hp)
        : name(name), health(hp), maxHealth(hp), attack(1), defense(0), pos{0, 0} {}

    const Position& Character::getPosition() const {
        return pos;
    }

    void Character::setPosition(int x, int y) {
        pos.x = x;
        pos.y = y;
    }

    const string& Character::getName() const {
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
        health = min(maxHealth, health + amount);
    }

    void Character::displayStats() const {
        cout << "\n--- " << name << " Stats ---\n";
        cout << "Health: " << health << " / " << maxHealth << "\n";
        cout << "Attack: " << attack << "\n";
        cout << "Defense: " << defense << "\n";
        cout << "Position: (" << pos.x << ", " << pos.y << ")\n";
    }

    bool Character::isAlive() const {
        return health > 0;
    }

}