/* File: Game.cpp
    Name: CSC 222 Students
    Date: 01/28/2026
    Last Edit: 01/28/2026
    Course: CSC 222 - Programming and Algorithms II
    Desc: Game class implementation for the Dungeon of Data Structures game.
    Usage: Compile and run the program to start the game.
  
    Other files required: Character.h, Player.h, Game.h,
                              Character.cpp, Player.cpp, NPC.cpp, NPC.h
*/
#include "Game.h"
#include "NPC.h"
#include "NPCSpawner.h"
#include "ActionHistory.h"
#include "SpellEvaluator.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

namespace dungeongame {

Game::Game()
    : running(true), player("Adventurer") {
    // Optional: load inventory items from a file at startup
    loadInventoryFromFile("data/inventory.txt");

    initMap();
    placePlayerOnMap();
    initializeGrimoire();
}

void Game::loadInventoryFromFile(const std::string& path) {
    // Try both the provided path and a project-relative path so the game can be
    // run from either the repo root or the `dungeongame/` folder.
    std::ifstream in(path);
    std::string actualPath = path;
    if (!in) {
        std::string altPath = "dungeongame/" + path;
        in.open(altPath);
        if (in) {
            actualPath = altPath;
        }
    }

    if (!in) {
        cout << "(No inventory file found at '" << path << "' or 'dungeongame/" << path
             << "'. Starting with empty inventory.)\n";
        return;
    }

    cout << "Loading inventory from file: " << actualPath << "\n";
    std::string line;
    int loaded = 0;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        std::string name;
        if (!std::getline(ss, name, ',')) continue;
        std::string valueStr;
        if (!std::getline(ss, valueStr)) continue;
        int value = 0;
        try {
            value = std::stoi(valueStr);
        } catch (...) {
            // ignore malformed lines
            continue;
        }
        player.addItem(Item(name, value));
        loaded++;
    }

    cout << "  Loaded " << loaded << " item(s) into inventory.\n";
}

void Game::initMap() {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            map[y][x] = '.'; // empty floor
        }
    }
}

void Game::placePlayerOnMap() {
    // reset previous positions every time
    initMap();
    Position p = player.getPosition();
    map[p.y][p.x] = 'P';
}

void Game::displayMap() const {
    cout << "Map:\n";
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            cout << map[y][x] << ' ';
        }
        cout << '\n';
    }
}

void Game::displayMenu() const {
    cout << "\n=== Main Menu ===\n";
    cout << "1) Move Up\n";
    cout << "2) Move Down\n";
    cout << "3) Move Left\n";
    cout << "4) Move Right\n";
    cout << "5) Show Stats\n";
    cout << "6) Quit\n";
    cout << "7) Encounter Enemy (demo)\n";
    cout << "8) Prepare Potions (Pointers demo)\n";
    cout << "9) Show Inventory\n";
    cout << "10) Use Potion\n";
    cout << "11) Linked List Demo (Template class demo)\n";
    cout << "12) Spawn Control (skip N)\n";
    cout << "13) Action History (undo)\n";
    cout << "14) Cast Postfix Spell\n";
    cout << "15) Show Spawn Queue (debug)\n";
    cout << "16) Show Action History (debug)\n";
    cout << "17) Pick up item (demo)\n";
    cout << "18) Drop item (by index)\n";
    cout << "19) NPC pointer container demo\n";
    cout << "20) NPC spawner demo\n";
    cout << "21) Linked String Lab (lab07)\n";
    cout << "22) Linked Bag Demo (hw05)\n";
    cout << "23) View Grimoire\n";
    cout << "24) Loot Bag\n";
    cout << "25) Sort/Search Demo (inventory)\n";
    cout << "26) Compare bubble vs insertion sort\n";

    cout << "Choose an action: ";
}

void Game::processChoice(int choice) {
    switch (choice) {
        case 1: {
            Position prev = player.getPosition();
            player.move(0, -1);
            history.pushMove(prev);
            break;
        }
        case 2: {
            Position prev = player.getPosition();
            player.move(0, 1);
            history.pushMove(prev);
            break;
        }
        case 3: {
            Position prev = player.getPosition();
            player.move(-1, 0);
            history.pushMove(prev);
            break;
        }
        case 4: {
            Position prev = player.getPosition();
            player.move(1, 0);
            history.pushMove(prev);
            break;
        }
        case 5: player.displayStats(); break;
        case 6: running = false; break;
        case 7: {
            // Demo encounter: spawn a goblin and start combat
             NPC goblin("Goblin", 10, 3, 0, 10, 5);
            cout << "You encounter a Goblin!" << endl;
            processCombat(goblin);
            break;
        }
        case 8: {
            // Pointers & dynamic memory demo integrated into game
            runPointersDemo();
            break;
        }
        case 9: {
            player.showInventory();
            break;
        }
        case 10: {
            int prevH = player.getHealth();
            Item used;
            int healAmt = 0;
            if (!player.usePotionAndGet(used, healAmt)) {
                cout << "No potions available." << endl;
            } else {
                history.pushUsePotion(used, prevH);
            }
            break;
        }
        case 11: {
            // Template class & linked list demo integrated into game
            runLinkedListDemo();
            break;
        }
        case 17: {
            handlePickItem();
            break;
        }
        case 18: {
            handleDropItem();
            break;
        }
        case 19: {
            // NPC pointer container demonstration
            runNPCGroupDemo();
            break;
        }
        case 20: {
            // NPC spawner pointer demonstration
            runNPCSpawnerDemo();
            break;
        }
        case 21: {
            runLinkedStringLab();
            break;
        }
        case 22: {
            runBagDemo();
            break;
        }
        case 23: {
            viewGrimoire();
            break;
        }
        case 24: {
            handleLootBag();
            break;
        }
        case 25: {
            runSortSearchDemo();
            break;
        }
        case 26: {
            runSortCompareDemo();
            break;
        }
        default:
            if (choice >= 12 && choice <= 16) {
                if (choice == 12) handleSpawnSkip();
                else if (choice == 13) handleUndo();
                else if (choice == 14) handleCastSpell();
                else if (choice == 15) showSpawnQueue();
                else if (choice == 16) showActionHistory();
            } else {
                cout << "Invalid choice." << endl;
            }
            break;
    }
    placePlayerOnMap();
}

void Game::processCombat(NPC& enemy) {
    // simple turn-based loop
    while (player.isAlive() && enemy.isAlive()) {
        cout << "\n--- Combat ---" << endl;
        player.displayStats();
        enemy.displayStats();

        cout << "Choose action: 1) Attack  2) Flee\n";
        int action = 0;
        if (!(cin >> action)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number." << endl;
            continue;
        }

        if (action == 1) {
            int atk = player.calculateAttack();
            int damage = atk - enemy.getDefense();
            if (damage < 1) damage = 1;
            cout << "You hit the " << enemy.getName() << " for " << damage << " damage." << endl;
            enemy.takeDamage(damage);
            if (!enemy.isAlive()) {
                cout << "You defeated the " << enemy.getName() << "!" << endl;
                player.gainExperience(enemy.getExpReward());
                player.addGold(enemy.getGoldReward());
                
                // Create and add loot to the loot bag
                int lootValue = 10 + (rand() % 30);
                Item loot(enemy.getName() + " Loot", lootValue);
                lootBag.add(loot);
                cout << "  *** " << loot.name << " (value: " << loot.value << ") dropped into loot bag! ***" << endl;
                
                break;
            }
            // enemy retaliates
            int eatk = enemy.calculateAttack();
            int edamage = eatk - player.getDefense();
            if (edamage < 1) edamage = 1;
            cout << "The " << enemy.getName() << " hits you for " << edamage << " damage." << endl;
            player.takeDamage(edamage);
            if (!player.isAlive()) {
                cout << "You have been defeated..." << endl;
                running = false;
                break;
            }
        } else if (action == 2) {
            // 50% chance to flee
            if (rand() % 2 == 0) {
                cout << "You fled successfully." << endl;
                break;
            } else {
                cout << "Flee failed! The " << enemy.getName() << " attacks." << endl;
                int eatk = enemy.calculateAttack();
                int edamage = eatk - player.getDefense();
                if (edamage < 1) edamage = 1;
                cout << "The " << enemy.getName() << " hits you for " << edamage << " damage." << endl;
                player.takeDamage(edamage);
                if (!player.isAlive()) {
                    cout << "You have been defeated..." << endl;
                    running = false;
                    break;
                }
            }
        } else {
            cout << "Invalid action." << endl;
        }
    }
}

void Game::runPointersDemo() {
    cout << "\n--- Potions Prep (Pointers Demo) ---" << endl;
    cout << "How many potions would you like to prepare? ";
    int potionNum;
    if (!(cin >> potionNum) || potionNum <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input; defaulting to 5." << endl;
        potionNum = 5;
    }

    int* iptr = &potionNum;
    cout << "potionNum value: " << potionNum << '\n';
    cout << "iptr address: " << static_cast<const void*>(iptr) << '\n';
    cout << "*iptr value: " << *iptr << "\n\n";

    // Manipulate potionNum through its pointer (demonstrates inspecting/modifying via pointer)
    cout << "Incrementing potionNum via iptr...\n";
    (*iptr)++;
    cout << "potionNum after increment: " << potionNum << "\n\n";

    // Dynamic integer array allocated using the (possibly updated) potionNum
    int* myArray = new int[potionNum];
    for (int i = 0; i < potionNum; ++i) myArray[i] = i + 1;

    cout << "Array values (direct indexing): ";
    for (int i = 0; i < potionNum; ++i) cout << myArray[i] << (i + 1 == potionNum ? '\n' : ' ');

    int* ptrToMyArray = myArray;
    cout << "Enhancing potions via pointer arithmetic (multiply values by 10)...\n";
    for (int i = 0; i < potionNum; ++i) *(ptrToMyArray + i) *= 10;

    cout << "Array values (via pointer ptrToMyArray): ";
    for (int i = 0; i < potionNum; ++i) cout << *(ptrToMyArray + i) << (i + 1 == potionNum ? '\n' : ' ');

    // Transfer dynamic array items into the player's Inventory (player owns potions now)
    for (int i = 0; i < potionNum; ++i) {
        player.addItem(Item("Potion #" + to_string(i + 1), myArray[i]));
    }

    // Free manually-allocated array
    delete[] myArray;
    cout << "Manual delete[] called. All dynamically allocated memory released.\n\n";

    cout << "Added " << potionNum << " potions to your inventory. Use 'Show Inventory' and 'Use Potion' from the main menu.\n";

}

void Game::runLinkedListDemo() {
    cout << "\n--- Linked List Demo (Template Class) ---" << endl;
    cout << "This demo shows how to use a template class for a generic linked list." << endl;
    cout << "We'll create linked lists of different types and demonstrate operations." << endl;

    // Demo 1: Linked list of integers
    cout << "\n1. Creating a linked list of integers:" << endl;
    LinkedList<int> intList;
    intList.append(10);
    intList.append(20);
    intList.append(30);
    cout << "Added 10, 20, 30: ";
    intList.print();

    cout << "Prepending 5: ";
    intList.prepend(5);
    intList.print();

    cout << "Size: " << intList.size() << endl;
    cout << "Element at index 2: " << intList.get(2) << endl;

    // Demo 2: Linked list of strings
    cout << "\n2. Creating a linked list of strings:" << endl;
    LinkedList<std::string> stringList;
    stringList.append("Hello");
    stringList.append("Template");
    stringList.append("World");
    cout << "Added 'Hello', 'Template', 'World': ";
    stringList.print();

    // Demo 3: Linked list of custom objects (Items)
    cout << "\n3. Creating a linked list of Items (custom objects):" << endl;
    LinkedList<Item> itemList;
    itemList.append(Item("Sword", 100));
    itemList.append(Item("Shield", 80));
    itemList.append(Item("Potion", 25));
    cout << "Added Sword ($100), Shield ($80), Potion ($25):" << endl;
    cout << "Linked list contents:" << endl;
    for (size_t i = 0; i < itemList.size(); ++i) {
        const Item& item = itemList.get(i);
        cout << "  " << item.name << " (value: $" << item.value << ")" << endl;
    }

    // Demo 4: Using range-based for loop (iterator)
    cout << "\n4. Using range-based for loop to traverse the string list:" << endl;
    for (const std::string& str : stringList) {
        cout << str << " ";
    }
    cout << endl;

    // Demo 5: Removing elements
    cout << "\n5. Removing element at index 1 from integer list:" << endl;
    cout << "Before removal: ";
    intList.print();
    intList.removeAt(1);
    cout << "After removal: ";
    intList.print();

    // Demo 6: Copying linked lists
    cout << "\n6. Copying linked list (deep copy):" << endl;
    LinkedList<std::string> copiedList = stringList;
    cout << "Original: ";
    stringList.print();
    cout << "Copy: ";
    copiedList.print();

    cout << "\nTemplate classes allow us to create reusable data structures that work with any type!" << endl;
    cout << "This linked list template can store integers, strings, or any custom class." << endl;
}
// ------------------------------------------------------
// Lab 07 activity: Linked String ADT demonstration
// ------------------------------------------------------

void Game::runLinkedStringLab() {
    using namespace std;
    cout << "\n--- Linked String Lab ---" << endl;
    cout << "Enter first string: ";
    string s1;
    cin >> ws;
    getline(cin, s1);
    cout << "Enter second string: ";
    string s2;
    getline(cin, s2);

    LinkedString ls1(s1);
    LinkedString ls2(s2);

    cout << "You entered:\n";
    cout << "  1) " << ls1.toStdString() << " (length=" << ls1.length() << ")\n";
    cout << "  2) " << ls2.toStdString() << " (length=" << ls2.length() << ")\n";

    if (ls1.equals(ls2))
        cout << "The two strings are equal.\n";
    else
        cout << "The two strings are NOT equal.\n";

    cout << "Demo: change first char of first string to 'X' (if exists)" << endl;
    if (ls1.length() > 0) {
        ls1.set(0, 'X');
        cout << "Modified 1) " << ls1.toStdString() << "\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ------------------------------------------------------
// Homework 05 activity: Linked Bag demonstration
// ------------------------------------------------------

void Game::runBagDemo() {
    using namespace std;
    cout << "\n--- Linked Bag Demo ---" << endl;
    LinkedBag<string> bag;
    cout << "We'll add several strings to a linked bag, then remove and query." << endl;
    vector<string> samples = {"apple", "banana", "cherry", "date", "banana"};
    for (auto &w : samples) {
        bag.add(w);
        cout << "added '" << w << "'\n";
    }
    cout << "current bag size: " << bag.getCurrentSize() << "\n";
    cout << "Bag contains 'banana'? " << (bag.contains("banana") ? "yes" : "no") << "\n";
    cout << "Removing 'banana'...\n";
    bag.remove("banana");
    cout << "Size after removal: " << bag.getCurrentSize() << "\n";
    cout << "Contents via toVector(): ";
    auto vec = bag.toVector();
    for (auto &x : vec) cout << x << " ";
    cout << "\n";
    cout << "Clear bag.\n";
    bag.clear();
    cout << "Bag empty? " << (bag.isEmpty() ? "yes" : "no") << "\n";

    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
// ---------------- Week 04 helper implementations ----------------

void Game::handleSpawnSkip()
{
    cout << "Enter number of enemies to skip (n): ";
    int n = 0;
    if (!(cin >> n)) {
        cin.clear(); cin.ignore(10000, '\n');
        cout << "Invalid input." << endl;
        return;
    }
    spawner.skipEnemies(n);
    cout << "Skipped " << n << " enemies.\n";
}

void Game::handleUndo()
{
    cout << "Undo how many actions? (default 1): ";
    int k = 1;
    if (!(cin >> k)) {
        cin.clear(); cin.ignore(10000, '\n');
        k = 1;
    }
    int undone = history.undoLast(k, player);
    cout << "Undone " << undone << " action(s).\n";
}

void Game::handleCastSpell()
{
    cout << "Enter postfix expression (tokens separated by spaces), e.g. '6 3 + 2 *': ";
    cin.ignore(10000, '\n');
    std::string expr;
    std::getline(cin, expr);
    try {
        int val = SpellEvaluator::evaluatePostfix(expr);

        // provide multiple effects for demo: ask user which effect to apply
        cout << "Choose effect: 1) Heal player  2) Give gold  3) Damage enemy (demo)\n";
        cout << "Enter choice (1-3): ";
        int eff = 1;
        if (!(std::cin >> eff)) { std::cin.clear(); std::cin.ignore(10000, '\n'); eff = 1; }

        switch (eff) {
            case 1:
                cout << "Spell evaluated to: " << val << " (healing player)\n";
                player.heal(val);
                break;
            case 2:
                cout << "Spell evaluated to: " << val << " (granting gold)\n";
                player.addGold(val);
                break;
            case 3:
                cout << "Spell evaluated to: " << val << " (demo damage to next spawned enemy)\n";
                if (spawner.hasEnemies()) {
                    NPC* e = spawner.nextEnemy();
                    e->takeDamage(val);
                    if (e->isAlive()) {
                        cout << e->getName() << " survived the blast (hp=" << e->getHealth() << ") and is re-queued.\n";
                        spawner.addEnemy(e);
                    } else {
                        cout << e->getName() << " was destroyed by the spell!\n";
                        delete e; 

                    }
                } else {
                    cout << "No enemies to affect.\n";
                }
                break;
            default:
                cout << "Unknown effect; applying heal by default." << endl;
                player.heal(val);
                break;
        }
    } catch (const std::exception& ex) {
        cout << "Error evaluating expression: " << ex.what() << "\n";
    }
}

void Game::handlePickItem()
{
    cout << "Enter item name: ";
    std::string name;
    if (!(std::cin >> name)) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Invalid name." << std::endl; return; }
    cout << "Enter item value: ";
    int v = 0;
    if (!(std::cin >> v)) { std::cin.clear(); std::cin.ignore(10000, '\n'); v = 1; }

    Item it(name, v);
    player.addItem(it);
    history.pushPick(it, player.inventorySize() - 1);
    cout << "Picked up: " << it.name << " (" << it.value << ")\n";
}

// simple demo stubs to satisfy menu
void Game::runNPCGroupDemo() {
    cout << "\n--- NPC Group Demo ---\n";
    cout << "(This demo would show a container of NPC pointers.)\n";
}

static size_t bubbleSortCount(Inventory& inv) {
    size_t n = inv.size();
    size_t comparisons = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (inv[j].name > inv[j + 1].name) {
                Item tmp = inv[j];
                inv[j]   = inv[j + 1];
                inv[j + 1] = tmp;
            }
        }
    }
    return comparisons;
}

static size_t insertionSortCount(Inventory& inv) {
    size_t comparisons = 0;
    int n = static_cast<int>(inv.size());
    for (int i = 1; i < n; i++) {
        Item key = inv[static_cast<size_t>(i)];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (inv[static_cast<size_t>(j)].name > key.name) {
                inv[static_cast<size_t>(j + 1)] = inv[static_cast<size_t>(j)];
                j--;
            } else {
                break;
            }
        }
        inv[static_cast<size_t>(j + 1)] = key;
    }
    return comparisons;
}

void Game::runSortSearchDemo() {
    cout << "\n=== Sort/Search Demo ===\n";

    if (player.inventorySize() == 0) {
        cout << "Inventory is empty — adding demo items...\n";
        player.addItem(Item("Potion", 10));
        player.addItem(Item("Sword", 50));
        player.addItem(Item("Bow", 45));
        player.addItem(Item("Shield", 30));
        player.addItem(Item("Elixir", 20));
    }

    cout << "\nInventory (before sorting):\n";
    player.showInventory();

    cout << "\nChoose sorting algorithm:\n";
    cout << "  1) Bubble sort (O(n²))\n";
    cout << "  2) Insertion sort (O(n²))\n";
    cout << "Select (1 or 2): ";
    int sortChoice = 0;
    if (!(cin >> sortChoice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        sortChoice = 1;
    }

    if (sortChoice == 2) {
        cout << "\nSorting inventory by name (insertion sort)...\n";
        player.sortInventoryByNameInsertion();
    } else {
        cout << "\nSorting inventory by name (bubble sort)...\n";
        player.sortInventoryByName();
    }
    player.showInventory();

    const std::string target = "Potion";
    int linearComparisons = 0;
    int binaryComparisons = 0;
    int linearIndex = -1;
    int binaryIndex = -1;

    // Linear search count
    for (size_t i = 0; i < player.inventorySize(); ++i) {
        linearComparisons++;
        if (player[i].name == target) {
            linearIndex = static_cast<int>(i);
            break;
        }
    }

    // Binary search count (requires sorted inventory)
    int lo = 0;
    int hi = static_cast<int>(player.inventorySize()) - 1;
    while (lo <= hi) {
        binaryComparisons++;
        int mid = lo + (hi - lo) / 2;
        const std::string& midName = player[mid].name;
        if (midName == target) {
            binaryIndex = mid;
            break;
        }
        if (midName < target) lo = mid + 1;
        else hi = mid - 1;
    }

    cout << "\nSearch for '" << target << "':\n";
    cout << "  Linear search: index=" << linearIndex << ", comparisons=" << linearComparisons << "\n";
    cout << "  Binary search: index=" << binaryIndex << ", comparisons=" << binaryComparisons << "\n";
}

void Game::runSortCompareDemo() {
    cout << "\n=== Sort Comparison Demo (Bubble vs Insertion) ===\n";

    // Ensure there's inventory to work with
    if (player.inventorySize() == 0) {
        cout << "Inventory is empty — adding demo items...\n";
        player.addItem(Item("Potion", 10));
        player.addItem(Item("Sword", 50));
        player.addItem(Item("Bow", 45));
        player.addItem(Item("Shield", 30));
        player.addItem(Item("Elixir", 20));
    }

    // Copy the current inventory so both algorithms start from the same data
    Inventory base;
    for (size_t i = 0; i < player.inventorySize(); ++i) {
        base.add(player[i]);
    }

    auto runAndMeasure = [&](Inventory inv, const std::string& label,
                             size_t (*sortFn)(Inventory&)) {
        auto start = std::chrono::steady_clock::now();
        size_t comparisons = sortFn(inv);
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        cout << "\n" << label << ":\n";
        cout << "  Sorted result:\n";
        for (size_t i = 0; i < inv.size(); ++i) {
            cout << "    " << i << ") " << inv[i].name << " (" << inv[i].value << ")\n";
        }
        cout << "  Comparisons: " << comparisons << "\n";
        cout << "  Time: " << ms << " microseconds\n";
        return comparisons;
    };

    cout << "Starting with the same inventory for both sorts...\n";
    cout << "Base inventory:\n";
    for (size_t i = 0; i < base.size(); ++i) {
        cout << "  " << i << ") " << base[i].name << " (" << base[i].value << ")\n";
    }

    runAndMeasure(base, "Bubble sort", bubbleSortCount);
    runAndMeasure(base, "Insertion sort", insertionSortCount);

    cout << "\n(Observation: comparisons/time vary depending on sorting algorithm and input order.)\n";
}

// ---------------- Week 11: Array-based sorts & inventory-wide demos ----------------

// Instrumented array sorts (operate on vector<int>) — return comparison count
static size_t bubbleSortArray(std::vector<int>& arr) {
    size_t n = arr.size();
    size_t comparisons = 0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j + 1 < n - i; ++j) {
            comparisons++;
            if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
        }
    }
    return comparisons;
}

static size_t insertionSortArray(std::vector<int>& arr) {
    size_t comparisons = 0;
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[static_cast<size_t>(j)] > key) {
                arr[static_cast<size_t>(j + 1)] = arr[static_cast<size_t>(j)];
                --j;
            } else break;
        }
        arr[static_cast<size_t>(j + 1)] = key;
    }
    return comparisons;
}

static size_t mergeSortArrayRec(std::vector<int>& arr, std::vector<int>& tmp, int lo, int hi) {
    if (lo >= hi) return 0;
    int mid = lo + (hi - lo) / 2;
    size_t comps = 0;
    comps += mergeSortArrayRec(arr, tmp, lo, mid);
    comps += mergeSortArrayRec(arr, tmp, mid + 1, hi);
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        comps++;
        if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }
    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= hi) tmp[k++] = arr[j++];
    for (int x = lo; x <= hi; ++x) arr[x] = tmp[x];
    return comps;
}

static size_t mergeSortArray(std::vector<int>& arr) {
    std::vector<int> tmp(arr.size());
    return mergeSortArrayRec(arr, tmp, 0, static_cast<int>(arr.size()) - 1);
}

static int partitionQS(std::vector<int>& arr, int lo, int hi, size_t& comps) {
    int pivot = arr[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; ++j) {
        comps++;
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[hi]);
    return i + 1;
}

static size_t quickSortArrayRec(std::vector<int>& arr, int lo, int hi) {
    size_t comps = 0;
    if (lo < hi) {
        int p = partitionQS(arr, lo, hi, comps);
        comps += quickSortArrayRec(arr, lo, p - 1);
        comps += quickSortArrayRec(arr, p + 1, hi);
    }
    return comps;
}

static size_t quickSortArray(std::vector<int>& arr) {
    if (arr.empty()) return 0;
    // quickSortArrayRec uses partitionQS which accumulates comparisons via return values
    return quickSortArrayRec(arr, 0, static_cast<int>(arr.size()) - 1);
}

void Game::runArraySortBenchmarks() {
    using namespace std::chrono;
    cout << "\n=== Array Sort Benchmarks ===\n";
    std::vector<int> sizes = {100, 1000, 10000, 50000, 100000};
    cout << "size,algorithm,time_us,comparisons\n";
    for (int s : sizes) {
        // generate random array with values [0, s*10)
        std::vector<int> base(s);
        for (int i = 0; i < s; ++i) base[i] = rand() % (s * 10);

        // Bubble
        auto arr1 = base;
        auto t0 = steady_clock::now();
        size_t comps1 = bubbleSortArray(arr1);
        auto t1 = steady_clock::now();
        auto us1 = duration_cast<microseconds>(t1 - t0).count();
        cout << s << ",bubble," << us1 << "," << comps1 << "\n";

        // Insertion
        auto arr2 = base;
        t0 = steady_clock::now();
        size_t comps2 = insertionSortArray(arr2);
        t1 = steady_clock::now();
        auto us2 = duration_cast<microseconds>(t1 - t0).count();
        cout << s << ",insertion," << us2 << "," << comps2 << "\n";

        // Merge
        auto arr3 = base;
        t0 = steady_clock::now();
        size_t comps3 = mergeSortArray(arr3);
        t1 = steady_clock::now();
        auto us3 = duration_cast<microseconds>(t1 - t0).count();
        cout << s << ",merge," << us3 << "," << comps3 << "\n";

        // Quick
        auto arr4 = base;
        t0 = steady_clock::now();
        size_t comps4 = quickSortArray(arr4);
        t1 = steady_clock::now();
        auto us4 = duration_cast<microseconds>(t1 - t0).count();
        cout << s << ",quick," << us4 << "," << comps4 << "\n";

        // Small sanity check: print first 5 of merge-sorted array
        cout << "sample_sorted_first5:";
        for (int i = 0; i < std::min(5, s); ++i) cout << " " << arr3[i];
        cout << "\n";
    }
    cout << "(CSV output above — copy into Excel/Google Sheets and create log-log or semilog plots.)\n";
}

void Game::runSortInventoryAllDemo() {
    using namespace std::chrono;
    cout << "\n=== Inventory: Run All Sorts (compare) ===\n";
    if (player.inventorySize() == 0) {
        cout << "Inventory is empty — adding demo items...\n";
        player.addItem(Item("Potion", 10));
        player.addItem(Item("Sword", 50));
        player.addItem(Item("Bow", 45));
        player.addItem(Item("Shield", 30));
        player.addItem(Item("Elixir", 20));
    }

    // Copy inventory into a vector<Item> so array-style sorts are fair (random access)
    std::vector<Item> base;
    for (size_t i = 0; i < player.inventorySize(); ++i) base.push_back(player[i]);

    // Helper to run a name-based sort on vector<Item>
    auto runNameSort = [&](std::vector<Item> data, const std::string& label,
                           std::function<size_t(std::vector<int>&)> /*unused*/) {
        // We'll implement using integer mapping: map each name to a hash by comparing strings
        // But for comparisons counting, we will compare strings directly in adapted algorithms below.
        // For simplicity reuse std::sort for merge/quick timing comparison but count string comps via lambda.
    };

    // For clarity, implement three instrumented sorts operating on vector<Item> comparing .name
    auto bubbleItems = [&](std::vector<Item> v) {
        size_t comps = 0;
        size_t n = v.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j + 1 < n - i; ++j) {
                comps++;
                if (v[j].name > v[j + 1].name) std::swap(v[j], v[j + 1]);
            }
        }
        return std::make_pair(v, comps);
    };

    auto insertionItems = [&](std::vector<Item> v) {
        size_t comps = 0;
        for (size_t i = 1; i < v.size(); ++i) {
            Item key = v[i];
            int j = static_cast<int>(i) - 1;
            while (j >= 0) {
                comps++;
                if (v[static_cast<size_t>(j)].name > key.name) {
                    v[static_cast<size_t>(j + 1)] = v[static_cast<size_t>(j)];
                    --j;
                } else break;
            }
            v[static_cast<size_t>(j + 1)] = key;
        }
        return std::make_pair(v, comps);
    };

    // Merge sort for Items
    std::function<size_t(std::vector<Item>&, std::vector<Item>&, int, int)> mergeItemsRec;
    mergeItemsRec = [&](std::vector<Item>& arr, std::vector<Item>& tmp, int lo, int hi) -> size_t {
        if (lo >= hi) return 0;
        int mid = lo + (hi - lo) / 2;
        size_t comps = 0;
        comps += mergeItemsRec(arr, tmp, lo, mid);
        comps += mergeItemsRec(arr, tmp, mid + 1, hi);
        int i = lo, j = mid + 1, k = lo;
        while (i <= mid && j <= hi) {
            comps++;
            if (arr[i].name <= arr[j].name) tmp[k++] = arr[i++];
            else tmp[k++] = arr[j++];
        }
        while (i <= mid) tmp[k++] = arr[i++];
        while (j <= hi) tmp[k++] = arr[j++];
        for (int x = lo; x <= hi; ++x) arr[x] = tmp[x];
        return comps;
    };

    auto mergeItems = [&](std::vector<Item> v) {
        std::vector<Item> tmp(v.size());
        size_t comps = 0;
        if (!v.empty()) comps = mergeItemsRec(v, tmp, 0, static_cast<int>(v.size()) - 1);
        return std::make_pair(v, comps);
    };

    // Quick sort for Items
    std::function<size_t(std::vector<Item>&, int, int)> quickItemsRec;
    std::function<int(std::vector<Item>&, int, int, size_t&)> partitionItems;

    partitionItems = [&](std::vector<Item>& arr, int lo, int hi, size_t& comps) -> int {
        std::string pivot = arr[hi].name;
        int i = lo - 1;
        for (int j = lo; j < hi; ++j) {
            comps++;
            if (arr[j].name < pivot) {
                ++i; std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[hi]);
        return i + 1;
    };

    quickItemsRec = [&](std::vector<Item>& arr, int lo, int hi) -> size_t {
        size_t comps = 0;
        if (lo < hi) {
            int p = partitionItems(arr, lo, hi, comps);
            comps += quickItemsRec(arr, lo, p - 1);
            comps += quickItemsRec(arr, p + 1, hi);
        }
        return comps;
    };

    auto quickItems = [&](std::vector<Item> v) {
        size_t comps = 0;
        if (!v.empty()) comps = quickItemsRec(v, 0, static_cast<int>(v.size()) - 1);
        return std::make_pair(v, comps);
    };

    // Run and measure each algorithm
    auto start = steady_clock::now();
    {
        auto t0 = steady_clock::now();
        auto res = bubbleItems(base);
        auto t1 = steady_clock::now();
        auto us = duration_cast<microseconds>(t1 - t0).count();
        cout << "Bubble sort:\n";
        for (size_t i = 0; i < res.first.size(); ++i) cout << "  " << i << ") " << res.first[i].name << " (" << res.first[i].value << ")\n";
        cout << "  Comparisons: " << res.second << "  Time: " << us << " microseconds\n\n";
    }

    {
        auto t0 = steady_clock::now();
        auto res = insertionItems(base);
        auto t1 = steady_clock::now();
        auto us = duration_cast<microseconds>(t1 - t0).count();
        cout << "Insertion sort:\n";
        for (size_t i = 0; i < res.first.size(); ++i) cout << "  " << i << ") " << res.first[i].name << " (" << res.first[i].value << ")\n";
        cout << "  Comparisons: " << res.second << "  Time: " << us << " microseconds\n\n";
    }

    {
        auto t0 = steady_clock::now();
        auto res = mergeItems(base);
        auto t1 = steady_clock::now();
        auto us = duration_cast<microseconds>(t1 - t0).count();
        cout << "Merge sort:\n";
        for (size_t i = 0; i < res.first.size(); ++i) cout << "  " << i << ") " << res.first[i].name << " (" << res.first[i].value << ")\n";
        cout << "  Comparisons: " << res.second << "  Time: " << us << " microseconds\n\n";
    }

    {
        auto t0 = steady_clock::now();
        auto res = quickItems(base);
        auto t1 = steady_clock::now();
        auto us = duration_cast<microseconds>(t1 - t0).count();
        cout << "Quick sort:\n";
        for (size_t i = 0; i < res.first.size(); ++i) cout << "  " << i << ") " << res.first[i].name << " (" << res.first[i].value << ")\n";
        cout << "  Comparisons: " << res.second << "  Time: " << us << " microseconds\n\n";
    }

    cout << "(Observation: merge/quick are typically O(n log n); bubble/insertion are O(n^2). Times/comparisons depend on input order and size.)\n";
}

void Game::runNPCSpawnerDemo() {
    cout << "\n--- NPC Spawner Demo ---\n";
    cout << "(This demo shows the NPCSpawner in action.)\n";
}

void Game::handleDropItem()
{
    player.showInventory();
    cout << "Enter index of item to drop: ";
    int idx = -1;
    if (!(std::cin >> idx)) { std::cin.clear(); std::cin.ignore(10000, '\n'); cout << "Invalid input." << endl; return; }
    if (idx < 0 || static_cast<size_t>(idx) >= player.inventorySize()) { cout << "Index out of range." << endl; return; }

    Item removed = player.removeItemAt(static_cast<size_t>(idx));
    history.pushDrop(removed, static_cast<size_t>(idx));
    cout << "Dropped: " << removed.name << "\n";
}

void Game::showSpawnQueue() const
{
    spawner.showQueue();
}

void Game::showActionHistory() const
{
    history.showHistory();
}


void Game::run() {
    // seed rand for flee chance
    srand((unsigned)time(nullptr));

    while (running) {
        displayMap();
        displayMenu();
        int choice = 0;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number." << endl;
            continue;
        }
        processChoice(choice);
    }
    cout << "Thanks for playing!" << endl;
}

// ======================================================
// Spell Grimoire implementations (using LinkedBag<Spell>)
// ======================================================

void Game::initializeGrimoire() {
    // Start the player with a few spells
    grimoire.learnSpell(Spell("Fireball", 20, 30, "deals 30 fire damage"));
    grimoire.learnSpell(Spell("Ice Storm", 25, 35, "deals 35 ice damage"));
    grimoire.learnSpell(Spell("Lightning", 15, 25, "deals 25 lightning damage"));
    cout << "Your grimoire has been initialized with starter spells!" << endl;
}

void Game::viewGrimoire() const {
    cout << "\n=== Your Spell Grimoire ===" << endl;
    if (grimoire.isEmpty()) {
        cout << "Your grimoire is empty. Learn some spells!" << endl;
        return;
    }
    
    auto spells = grimoire.getAllSpells();
    cout << "You know " << spells.size() << " spell(s):\n" << endl;
    for (size_t i = 0; i < spells.size(); ++i) {
        cout << i + 1 << ") " << spells[i].getNameAsString() << endl;
        cout << "   Mana Cost: " << spells[i].getManaCost() 
             << " | Damage: " << spells[i].getDamage() 
             << " | Effect: " << spells[i].getEffect() << endl;
    }
    cout << endl;
}

void Game::learnNewSpell(const Spell& spell) {
    if (grimoire.learnSpell(spell)) {
        cout << "You learned the spell \"" << spell.getNameAsString() << "\"!" << endl;
    } else {
        cout << "Could not learn the spell." << endl;
    }
}

void Game::castSpellFromGrimoire() {
    if (grimoire.isEmpty()) {
        cout << "\nYour grimoire is empty! Learn some spells first." << endl;
        return;
    }
    
    cout << "\n=== Cast Spell from Grimoire ===" << endl;
    viewGrimoire();
    
    auto spells = grimoire.getAllSpells();
    cout << "Choose a spell to cast (1-" << spells.size() << "), or 0 to cancel: ";
    int choice = 0;
    if (!(cin >> choice) || choice < 0 || choice > static_cast<int>(spells.size())) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid choice." << endl;
        return;
    }
    
    if (choice == 0) {
        cout << "Spell casting cancelled." << endl;
        return;
    }
    
    Spell spell = spells[choice - 1];
    cout << "You cast " << spell.getNameAsString() << "!" << endl;
    cout << "  Effect: " << spell.getEffect() << endl;
    cout << "  (Mana cost: " << spell.getManaCost() << ")" << endl;
}

// ======================================================
// Loot Bag implementations (using LinkedBag<Item>)
// ======================================================

void Game::handleLootBag() {
    cout << "\n=== Loot Bag ===" << endl;
    if (lootBag.isEmpty()) {
        cout << "Your loot bag is empty." << endl;
        return;
    }
    
    auto lootItems = lootBag.toVector();
    cout << "You have " << lootItems.size() << " item(s) in your loot bag:\n" << endl;
    for (size_t i = 0; i < lootItems.size(); ++i) {
        cout << i + 1 << ") " << lootItems[i].name 
             << " (value: $" << lootItems[i].value << ")" << endl;
    }
    
    cout << "\nOptions: 1) Transfer all to inventory  2) Cancel\n";
    cout << "Choose: ";
    int choice = 0;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    
    if (choice == 1) {
        transferLootToInventory();
    }
}

void Game::transferLootToInventory() {
    auto lootItems = lootBag.toVector();
    int transferred = 0;
    
    for (auto& item : lootItems) {
        player.addItem(item);
        transferred++;
    }
    
    lootBag.clear();
    cout << "Transferred " << transferred << " item(s) to inventory." << endl;
}
}

