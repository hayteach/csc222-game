/* File: main.cpp
   Name: CSC 222 Students
   Date: 01/28/2026
   Last Edit: 01/28/2026
   Course: CSC 222 - Programming and Algorithms II
   Desc: Main entry point for the Dungeon of Data Structures game.
         Initializes and starts the game loop.
    Usage: Compile and run the program to start the game.
  
        Other files required: Character.h, Player.h, Game.h, Game.cpp,
                              Character.cpp, Player.cpp
*/

#include <iostream>
#include "Game.h"

using namespace std;   // Use standard namespace

int main() {
    std::cout << "Dungeon Game\n";
    dungeongame::Game game;
    game.run();
    return 0;
}