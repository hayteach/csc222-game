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
    cout << "Choose an action: ";
}

void Game::processChoice(int choice) {
    switch (choice) {
        case 1: player.move(0, -1); break;
        case 2: player.move(0, 1); break;
        case 3: player.move(-1, 0); break;
        case 4: player.move(1, 0); break;
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
            if (!player.usePotion()) cout << "No potions available." << endl;
            break;
        }
        default: cout << "Invalid choice." << endl; break;
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
    int myVar;
    if (!(cin >> myVar) || myVar <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input; defaulting to 5." << endl;
        myVar = 5;
    }

    int* iptr = &myVar;
    cout << "myVar value: " << myVar << '\n';
    cout << "iptr address: " << static_cast<const void*>(iptr) << '\n';
    cout << "*iptr value: " << *iptr << "\n\n";

    // Manipulate myVar through its pointer (demonstrates inspecting/modifying via pointer)
    cout << "Incrementing myVar via iptr...\n";
    (*iptr)++;
    cout << "myVar after increment: " << myVar << "\n\n";

    // Dynamic integer array allocated using the (possibly updated) myVar
    int* myArray = new int[myVar];
    for (int i = 0; i < myVar; ++i) myArray[i] = i + 1;

    cout << "Array values (direct indexing): ";
    for (int i = 0; i < myVar; ++i) cout << myArray[i] << (i + 1 == myVar ? '\n' : ' ');

    int* ptrToMyArray = myArray;
    cout << "Enhancing potions via pointer arithmetic (multiply values by 10)...\n";
    for (int i = 0; i < myVar; ++i) *(ptrToMyArray + i) *= 10;

    cout << "Array values (via pointer ptrToMyArray): ";
    for (int i = 0; i < myVar; ++i) cout << *(ptrToMyArray + i) << (i + 1 == myVar ? '\n' : ' ');

    // Transfer dynamic array items into the player's Inventory (player owns potions now)
    for (int i = 0; i < myVar; ++i) {
        player.addItem(Item("Potion #" + to_string(i + 1), myArray[i]));
    }

    // Free manually-allocated array
    delete[] myArray;
    cout << "Manual delete[] called. All dynamically allocated memory released.\n\n";

    cout << "Added " << myVar << " potions to your inventory. Use 'Show Inventory' and 'Use Potion' from the main menu.\n";

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