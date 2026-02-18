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
#include "Enemy.h"
#include "Inventory.h"
#include "LinkedList.h"

// Week 04 feature headers
#include "EnemySpawner.h"
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
    EnemySpawner spawner;
    ActionHistory history;

    void initMap();
    void placePlayerOnMap();
    void displayMap() const;
    void displayMenu() const;
    void processChoice(int choice);

    // Combat handling
    void processCombat(Enemy& enemy);

    // Pointers & dynamic memory demo (game-integrated)
    void runPointersDemo();

    // Template class & linked list demo (game-integrated)
    void runLinkedListDemo();

    // Week 04 helpers
    void handleSpawnSkip();
    void handleUndo();
    void handleCastSpell();
    void handlePickItem();
    void handleDropItem();
    void showSpawnQueue() const;
    void showActionHistory() const;

public:
    Game();
    void run();
};

}

// appended namespace close