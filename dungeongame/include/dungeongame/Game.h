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
#include "Menu.h"

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
    void displayMenu();
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

    // Week 12 hashing lab activities
    void runHashingLab();           // Week 12 hashing activity
    void runGuessHashDemo();        // hash-based number guessing game
    void runColorHashTableDemo();   // color table hashing demo
    void runGameElementHashDemo();  // game element hashing demo
    int computeGuessHash(int k) const;                     // Week 12 hash function helper
    int computeColorHash(const std::string& color) const;  // Week 12 bin hashing helper
    int computeGameElementHash(const std::string& key) const; // Week 12 game-element hash helper
    std::string normalizeString(const std::string& input) const;
    std::vector<std::string> loadColorListFromFile(const std::string& path) const;

    // Week 13 graph search lab activities
    // These methods support the BFS/DFS dungeon exploration demo added for Week 13.
    void runGraphSearchLab();
    void runBFSPathDemo();
    void runDFSExploreDemo();
    void runRandomGraphMapDemo();
    std::vector<std::string> createRandomGraphMap(int rows, int cols, Position& start, Position& goal, int openChance = 35) const;
    std::vector<Position> getNeighbors(const std::vector<std::string>& map, const Position& current) const;
    std::vector<Position> breadthFirstSearch(const std::vector<std::string>& map, const Position& start, const Position& goal) const;
    std::vector<Position> depthFirstSearch(const std::vector<std::string>& map, const Position& start, const Position& goal) const;

    // Week 14 shortest-distance / traveling salesman lab activities
    // These methods support Dijkstra's shortest path and a simple Traveling
    // Salesman route planning heuristic.
    void runShortestDistanceLab();
    void runDijkstraDistanceDemo();
    void runTravelingSalesmanDemo();
    std::vector<int> computeDijkstraDistances(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& prev) const;
    std::vector<int> reconstructPath(int goal, const std::vector<int>& prev) const;
    std::vector<int> solveTSPNearestNeighbor(const std::vector<std::vector<int>>& distances, int start) const;

    // Week 15 binary tree lab activities
    // These methods support recursive tree node counting and single-parent detection.
    struct BinaryTreeNode {
        int value;
        std::string description;
        BinaryTreeNode* left;
        BinaryTreeNode* right;
        BinaryTreeNode(int v, const std::string& desc)
            : value(v), description(desc), left(nullptr), right(nullptr) {}
    };
    void runBinaryTreeLab();
    void runBinaryTreeCountDemo();
    void runBinaryTreeSingleParentDemo();
    BinaryTreeNode* createSampleBinaryTree() const;
    void printDecisionTree(const BinaryTreeNode* root, int depth = 0) const;
    void deleteBinaryTree(BinaryTreeNode* root) const;
    int countTreeNodes(const BinaryTreeNode* root) const;
    int countTreeLeaves(const BinaryTreeNode* root) const;
    int countSingleParentNodes(const BinaryTreeNode* root) const;

    // Menu helpers (Week 12 menu refactor)
    void runInventoryMenu();
    void runDemosMenu();
    void runLabsMenu();
    void runMenuScreen(const std::function<MenuScreen(bool&)>& buildMenu);
    void movePlayer(int dx, int dy);
    MenuScreen createMainMenu();
    MenuScreen createInventoryMenu(bool& done);
    MenuScreen createDemosMenu(bool& done);
    MenuScreen createLabsMenu(bool& done);
    MenuScreen buildSubMenu(const std::string& title, bool& done, std::vector<MenuOption> options);

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

    // Week 11: Array-based sorting benchmarks and inventory demos
    // - runArraySortBenchmarks: run bubble/insertion/merge/quick on integer
    //   arrays using default sizes and print CSV-style results suitable for plotting.
    // - runSortInventoryAllDemo: run bubble/insertion/merge/quick on copies of
    //   the player's Inventory and print comparisons + timing.
    void runArraySortBenchmarks();
    void runSortInventoryAllDemo();

    // Student testing hook: run student implementations on small arrays/inventory
    void runStudentSortTests();

    // Data loading (optional): load initial inventory items from file
    void loadInventoryFromFile(const std::string& path);

public:
    Game();
    void run();
};

}

// appended namespace close
