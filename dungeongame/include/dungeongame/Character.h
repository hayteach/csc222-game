/* File: Character.h
   Name: CSC 222 Students
   Date: 01/28/2026
   Last Edit: 01/28/2026
   Course: CSC 222 - Programming and Algorithms II
   Desc: Declaration for Character base class used in the Dungeon of Data Structures game.
    Usage: Include this header when using Character or derived classes.
  
        Other files required: Character.h, Player.h, Game.h, Game.cpp,
                              Character.cpp, Player.cpp
*/
#pragma once

#include <string>

namespace dungeongame {

    struct Position {
        int x{0};
        int y{0};
    };

    class Character {
    protected:
        std::string name;
        int health;
        int maxHealth{10};
        int attack{1};
        int defense{0};
        Position pos;

    public:
        Character(const std::string& name = "Nameless", int hp = 10);
        virtual ~Character() = default;

        // Position & identity
        const Position& getPosition() const;
        void setPosition(int x, int y);
        const std::string& getName() const;

        // Basic stats
        int getHealth() const;
        int getMaxHealth() const;
        int getAttack() const;
        int getDefense() const;

        // Actions
        virtual void takeDamage(int damage);
        virtual int calculateAttack() const;
        void heal(int amount);

        // Utility
        virtual void displayStats() const;
        bool isAlive() const;
    };
}