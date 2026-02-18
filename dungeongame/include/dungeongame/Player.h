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

#include <string>

#include "Character.h"
#include "Inventory.h"

// Instructor/student note (Week 02 - ADTs & Composition):
// - To integrate ADTs into the gameplay, `Player` can *contain* an ADT such
//   as `Inventory` (composition). This demonstrates how compound ADTs are
//   used in larger systems (Player has-an Inventory).
// - To keep the lab minimal, adding an Inventory member is optional for
//   students; if you add it, include `#include "Inventory.h"` and add a
//   member like `Inventory inventory;` to the `Player` class.

namespace dungeongame {

class Player : public Character {
    private:
        int level;
        int gold;
        int experience;
        // Composition: player has an Inventory (Week 02 - ADTs & Pointers)
        Inventory inventory;
    public:
        Player(const std::string& name = "Player");

        // Movement within a bounded map (map bounds enforced by caller)
        void move(int dx, int dy);
        void displayStats() const override;

        // Progression
        void gainExperience(int exp);
        void levelUp();
        void addGold(int amount);

        // Inventory helpers (simple wrappers)
        void addItem(const Item& item);
        void addItemAt(size_t idx, const Item& item);
        Item removeItemAt(size_t idx);
        void showInventory() const;
        size_t inventorySize() const;
        Item& operator[](size_t idx);
        const Item& operator[](size_t idx) const;
        bool usePotion(); // returns true if a potion was used
        bool usePotionAndGet(Item& outItem, int& healAmount); // returns potion used and heal amount

        // Health helpers (used by undo)
        void setHealth(int newHealth);

        // Accessors
        int getLevel() const;
        int getGold() const;
        int getExperience() const;
    };

} // namespace dungeongame