/* File: Game.h
   Name: CSC 222 Students
   Date: 01/28/2026
   Last Edit: 01/28/2026
   Course: CSC 222 - Programming and Algorithms II
   Desc: Declaration for Game class used in the Dungeon of Data Structures game.
    Usage: Include this header when using Game.
  
        Other files required: Character.h, Player.h, Game.h, Game.cpp,
                              Character.cpp, Player.cpp
*/
#pragma once

#include <string>
#include "Player.h"
#include "NPC.h"          // renamed from Enemy.h
#include "Inventory.h"
#include "LinkedList.h"
#include "LinkedString.h"   // lab07 ADT
#include "LinkedBag.h"      // hw05 bag template
#include "Spell.h"          // spell ADT for grimoire
#include "Grimoire.h"       // spell collection using LinkedBag

// Week 04 feature headers
#include "NPCSpawner.h"    // renamed from EnemySpawner.h
#include "ActionHistory.h"
#include "SpellEvaluator.h"

namespace dungeongame {

// Simple game shell for Week 1
// TODO: expand this class each week to add more features
class Game {
private:
    bool running;
    Player player;
    static const int MAP_WIDTH = 5;
    static const int MAP_HEIGHT = 5;
    char map[MAP_HEIGHT][MAP_WIDTH];

    // Week 04 additions
    NPCSpawner spawner;
    ActionHistory history;
    
    // Week 07 additions: Loot System and Spell Grimoire
    LinkedBag<Item> lootBag;        // dropped items from defeated enemies
    Grimoire grimoire;              // player's learned spells

    void initMap();
    void placePlayerOnMap();
    void displayMap() const;
    void displayMenu() const;
    void processChoice(int choice);

    // Combat handling
    void processCombat(NPC& enemy);

    // Pointers & dynamic memory demo (game-integrated)
    void runPointersDemo();

    // Template class & linked list demo (game-integrated)
    void runLinkedListDemo();

    // Lab07 / HW05 activities
    void runLinkedStringLab();      // linked-string ADT demonstration
    void runBagDemo();              // linked-bag template demonstration
    
    // Loot system (using LinkedBag<Item>)
    void handleLootBag();           // view and transfer loot
    void transferLootToInventory(); // move items from loot bag to inventory
    
    // Spell grimoire (using LinkedBag<Spell> via Grimoire)
    void viewGrimoire() const;      // display all learned spells
    void learnNewSpell(const Spell& spell); // add spell to grimoire
    void castSpellFromGrimoire();   // select and cast a spell
    void initializeGrimoire();      // populate initial spells

    // Week 04 helpers
    void handleSpawnSkip();
    void handleUndo();
    void handleCastSpell();
    void handlePickItem();
    void handleDropItem();
    void showSpawnQueue() const;
    void showActionHistory() const;

    // additional demos from earlier weeks
    void runNPCGroupDemo();
    void runNPCSpawnerDemo();

    // Week 10: Sorting & searching demos
    void runSortSearchDemo();
    void runSortCompareDemo();

    // Data loading (optional): load initial inventory items from file
    void loadInventoryFromFile(const std::string& path);

public:
    Game();
    void run();
};

}

// appended namespace close
