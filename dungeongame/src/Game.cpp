/* File: Game.cpp
    Name: CSC 222 Students
    Date: 01/28/2026
    Last Edit: 01/28/2026
    Course: CSC 222 - Programming and Algorithms II
    Desc: Game class implementation for the Dungeon of Data Structures game.
    Usage: Compile and run the program to start the game.
  
    Other files required: Character.h, Player.h, Game.h,
                              Character.cpp, Player.cpp, Enemy.cpp, Enemy.h
*/
#include "Game.h"
#include "Enemy.h"
#include "EnemySpawner.h"
#include "ActionHistory.h"
#include "SpellEvaluator.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

namespace dungeongame {

Game::Game()
    : running(true), player("Adventurer") {
    initMap();
    placePlayerOnMap();
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
            Enemy goblin("Goblin", 10, 3, 0, 10, 5);
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

void Game::processCombat(Enemy& enemy) {
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
                    Enemy e = spawner.nextEnemy();
                    e.takeDamage(val);
                    if (e.isAlive()) {
                        cout << e.getName() << " survived the blast (hp=" << e.getHealth() << ") and is re-queued.\n";
                        spawner.addEnemy(e);
                    } else {
                        cout << e.getName() << " was destroyed by the spell!\n";
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

}

// appended namespace close