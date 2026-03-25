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

using namespace std; // Standard namespace

namespace dungeongame {

// Inventory helper implementations
void Player::addItem(const Item& item) {
    inventory.add(item);
}

void Player::addItemAt(size_t idx, const Item& item) {
    inventory.insertAt(idx, item);
}

Item Player::removeItemAt(size_t idx) {
    return inventory.removeAt(idx);
}

void Player::setHealth(int newHealth) {
    if (newHealth < 0) newHealth = 0;
    if (newHealth > maxHealth) newHealth = maxHealth;
    health = newHealth;
}

void Player::showInventory() const {
    cout << "\n--- Inventory (" << inventory.size() << " items) ---\n";
    for (size_t i = 0; i < inventory.size(); ++i) {
        cout << i << ") " << inventory[i].name << " (value=" << inventory[i].value << ")\n";
    }
}

// Sorting/searching helpers (Week 10)
void Player::sortInventoryByValue() {
    inventory.sortByValue();
}

void Player::sortInventoryByName() {
    inventory.sortByName();
}

void Player::sortInventoryByNameInsertion() {
    inventory.insertionSortByName();
}

int Player::findInInventoryByName(const std::string& name) const {
    return inventory.findByName(name);
}

int Player::binarySearchInventoryByName(const std::string& name) const {
    return inventory.binarySearchByName(name);
}

size_t Player::inventorySize() const { return inventory.size(); }

Item& Player::operator[](size_t idx) { return inventory[idx]; }
const Item& Player::operator[](size_t idx) const { return inventory[idx]; }

bool Player::usePotion() {
    Item tmp; int heal = 0;
    return usePotionAndGet(tmp, heal);
}

bool Player::usePotionAndGet(Item& outItem, int& healAmount) {
    if (inventory.size() == 0) return false;
    // Use last item as potion: remove and apply its value as heal
    Item it = inventory.removeAt(inventory.size() - 1);
    healAmount = it.value;
    health += healAmount;
    if (health > maxHealth) health = maxHealth;
    outItem = it;
    cout << name << " used " << it.name << " and healed " << healAmount << " HP.\n";
    return true;
}


    Player::Player(const string& name)
        : Character(name, 20), level(1), gold(0), experience(0), inventory() {
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
        cout << "\n--- Player Stats ---\n";
        cout << "Name: " << name << "\n";
        cout << "Health: " << health << "\n";
        cout << "Level: " << level << "\n";
        cout << "Gold: " << gold << "\n";
        cout << "Experience: " << experience << "\n";
        cout << "Position: (" << pos.x << ", " << pos.y << ")\n";
    }
    
    void Player::gainExperience(int exp) {
        if (exp <= 0) return;
        experience += exp;
        // Simple threshold: 100 * level
        while (experience >= level * 100) {
            experience -= level * 100;
            levelUp();
        }
    }

    void Player::levelUp() {
        ++level;
        maxHealth += 10;
        health = maxHealth; // Heal on level up
        attack += 2;
        defense += 1;
        cout << name << " leveled up to " << level << "!\n";
    }

    void Player::addGold(int amount) {
        if (amount > 0) gold += amount;
    }

    int Player::getLevel() const { return level; }
    int Player::getGold() const { return gold; }
    int Player::getExperience() const { return experience; }

}

// appended namespace close