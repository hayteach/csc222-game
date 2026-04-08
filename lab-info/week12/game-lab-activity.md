# Week 12 Game Lab Activity: Hashing Challenge

## Goal
Use the Dungeon Game to explore hashing, collisions, and hash table storage in a fun, interactive way.

## Before You Start
- Read `game/lab-info/week12/week12.md` and `game/lab-info/week12/hashing.md`.
- Confirm that the game builds successfully.
- Make sure `game/dungeongame/data/ColorList.txt` is available.

## Step 0: Add the Week 12 Hashing Functions
If the game does not already include the Week 12 hashing lab, add the following functions to the Dungeon Game source.

1. Open `game/dungeongame/include/dungeongame/Game.h`.
2. Under the existing lab/demo methods, add the Week 12 declarations:
   - `void runHashingLab();`
   - `void runGuessHashDemo();`
   - `void runColorHashTableDemo();`
   - `void runGameElementHashDemo();`
   - `int computeGuessHash(int k) const;`
   - `int computeColorHash(const std::string& color) const;`
   - `int computeGameElementHash(const std::string& key) const;`
   - `std::vector<std::string> loadColorListFromFile(const std::string& path) const;`

3. Open `game/dungeongame/src/Game.cpp`.
4. Add any missing standard includes near the top of the file:
   - `#include <algorithm>`
   - `#include <cmath>`
   - `#include <cctype>`

5. Add the Week 12 functions in `Game.cpp`:
   - `Game::runHashingLab()` creates the main hashing menu for the game.
   - `Game::computeGuessHash(int k)` computes the number hash for the guess game using a demo-friendly formula.
   - `Game::computeColorHash(const std::string& color)` maps a color name into one of 15 bins.
   - `Game::computeGameElementHash(const std::string& key)` hashes inventory item names into bins for a game-specific demo.
   - `Game::loadColorListFromFile(const std::string& path)` loads `ColorList.txt` or falls back to built-in sample colors.
   - `Game::runGuessHashDemo()` runs the number-hashing guessing game and reports collisions.
   - `Game::runColorHashTableDemo()` builds the color hash table, prints bucket statistics, and supports searches/additions.
   - `Game::runGameElementHashDemo()` shows how hashing can group in-game inventory items and speed lookup.

### Why these functions are important
- `runHashingLab()` is the entry point for all Week 12 hashing activity from the game menu.
- `computeGuessHash()` uses a different hash formula from the homework lab so the game demonstrates hashing while protecting the homework solution.
- `computeColorHash()` shows a simple ASCII-sum hash and `mod 15` binning, which is easy to inspect and test.
- `computeGameElementHash()` shows how game data like inventory item names can be hashed and grouped into buckets for faster searches.
- `loadColorListFromFile()` keeps the color demo data external and reusable.
- `runGuessHashDemo()` gives students an interactive collision experience with number hashing.
- `runColorHashTableDemo()` shows how a hash table can store strings, handle collisions in bins, and perform case-insensitive lookups.

6. Add the new menu option in `Game::displayMenu()` so students can choose:
   - `30) Hashing Challenge (Week 12 lab)`

7. Rebuild the game and verify that option `30` appears and that both hashing submenus work correctly.

## Refactoring the game menu
Use a helper file to break the long main menu into smaller screens.

1. Create these two new files:
   - `game/dungeongame/include/dungeongame/Menu.h`
   - `game/dungeongame/src/Menu.cpp`
2. In `Menu.h`, define `MenuOption`, `MenuScreen`, `displayMenu()`, `promptMenuChoice()`, and `dispatchMenuChoice()`.
3. In `Menu.cpp`, implement the helper functions using `std::function<void()>` for menu actions.
4. In `game/dungeongame/include/dungeongame/Game.h`, add private helpers for:
   - `runInventoryMenu()`
   - `runDemosMenu()`
   - `runLabsMenu()`
   - `movePlayer(int dx, int dy)`
   - static menu builder methods for the main, inventory, demos, and labs menus
5. In `game/dungeongame/src/Game.cpp`:
   - include `Menu.h`
   - replace the long `displayMenu()` implementation with a helper-driven `Main Menu`
   - replace the large `processChoice()` switch with a menu dispatch
   - create separate inventory, demos, and labs screens so each menu uses its own numbering
6. Confirm the refactor still allows the player to:
   - move around the map
   - open inventory actions
   - run demos from the Demos menu
   - open the Labs menu and launch the Hashing Challenge

## Hashing in games
- Hashing helps games find information quickly without checking every item.
- In the Dungeon Game, hashing is used for:
  - the number guessing demo, which shows how values map to hashes and how collisions can happen
  - the color hash table demo, which groups string keys into bins and searches only the appropriate bin
- Why hashing inventory is useful compared to arrays or linked lists:
  - An array or linked list must often be searched one item at a time, which takes longer as inventory grows.
  - Hashing computes a bin from the item name, so the game only checks one small bucket instead of the entire inventory.
  - This is especially helpful when inventory is large or when many lookups happen often.
  - Arrays and linked lists are still useful, but hashing adds a faster lookup layer on top of them.
- In real games, hashing is also useful for:
  - inventory lookup by item name
  - asset/resource caching by string keys
  - grouping game entities so lookups are fast
  - procedural generation using hash-based seeds

### Hashing and Java
- Java uses the same core idea in `HashMap`, `HashSet`, and other hash-based collections.
- Each Java object has a `hashCode()` method, and the collection uses the result to place items into buckets.
- When a collision happens, Java still only checks the items in that one bucket, so lookups stay much faster than scanning the whole collection.
- In this game, the hash formulas for numbers, colors, and inventory names are a simple version of what Java does internally.

## Step 1: Launch the Game
1. Build the Dungeon Game as directed by the project.
2. Run the executable from `game/dungeongame`.
3. When the menu appears, choose option `30`.

## Step 2: Number Hashing Guess Game
1. The game will hide a value between `0` and `99`.
2. Your goal is to find the hidden value by hashing your guesses and comparing hashes.
3. Enter a guess and observe the hashed result.
4. If the hash matches the hidden number’s hash, the game will tell you.
5. If the value is different but the hash matches, a collision has occurred.
6. Keep guessing until you find the exact hidden value.

### What to Record
- The hidden number when you find it.
- The hash of the hidden number.
- Your final guess and its hash.
- How many guesses it took.
- Whether you experienced a collision.

## Step 3: Color Hash Table Demo
1. Choose the color hash table activity from the Hashing Challenge menu.
2. The game will build a hash table with 15 bins.
3. The hash function adds the ASCII codes of the letters in a color name, then applies `mod 15`.
4. Review the bin statistics printed by the game:
   - average number of colors per non-empty bin
   - maximum number of colors in a bin
5. Search for colors using the game prompt.
6. If a color is not found, the game will add it to the hash table.

### What to Observe
- Which colors are in each bin.
- Whether bins have different sizes.
- How the game only searches the appropriate bin.
- How the hash function distributes names across bins.

## Step 4: Game Element Hashing Demo
1. Choose the game element hashing demo from the Hashing Challenge menu.
2. The game will hash your current inventory item names into 10 bins.
3. Review the inventory hash bins and observe how items are grouped.
4. Search for an inventory item name to see which bin it belongs to.
5. If the item is not found, the game will explain that the item is not currently in inventory.

### What to Observe
- How inventory items are grouped by their hashed name.
- How only one bin is searched when checking for an item.
- How the hash function helps avoid scanning the full inventory.
- How game elements like item names can be treated like keys for a hash table.

## Step 4: Reflection Questions
Answer these questions in your notes:
1. What is the hashing formula used for the number guessing game?
2. What does the `mod` operation do in the color hash table?
3. Describe a collision. Did you see one in the guessing game or color table?
4. How does chaining work in the color table demo?
5. Why is it useful to only search one bin when looking for a color?

## Optional Challenge
- Modify the hash function to use a different number of bins.
- Add a second hash function for the color table.
- Create a version of the game that uses open addressing instead of chaining.

## Submission
- Save your answers to the reflection questions.
- Share any interesting collision examples you found.
- If required, package your updated game and `ColorList.txt` files for review.
