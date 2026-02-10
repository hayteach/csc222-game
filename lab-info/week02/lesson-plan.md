# Week 02 — Abstract Data Types & Arrays in C++

## Learning Objectives
- Explain Abstract Data Types (ADTs) and why we design interfaces separate from implementations.
- Implement contiguous (array-based) and non-contiguous (linked-list) ADTs in C++.
- Practice dynamic memory and pointer arithmetic (raw arrays vs `std::vector`).
- Apply ADT implementations to the game: an `Inventory` ADT and an `EnemyGroup` that stores multiple `Enemy` objects.
- Write unit tests that exercise ADT behavior and pointer-based traversal.

## In-class Activities (90 min)
1. Warm-up (10 min): Quick review of last week: `Game`, `Player`, `Character` — focus on how those classes define behavior.
2. Lecture (20 min): ADT concepts — interface vs implementation, contiguous vs non-contiguous storage, big-O tradeoffs, and C++ memory model (stack vs heap, `new/delete`, smart pointers).
3. Guided lab (45 min): Students implement an **array-based `Inventory` ADT** (dynamic resizing, add/remove, access) and an **`EnemyGroup`** that stores multiple `Enemy` objects (contiguous storage exposing raw pointer access). Tests will verify behavior and require iterating using both index and pointer arithmetic.
   - Implement `Inventory.h` / `Inventory.cpp` (array-backed, expose `rawData()` to practice pointer arithmetic).
   - Implement `EnemyGroup.h` / `EnemyGroup.cpp` (uses `std::vector<Enemy>` and exposes `data()` for pointer traversal).
   - **Play the in-game pointers exercise**: the main menu includes **"8) Prepare Potions (Pointers demo)"** which reads an integer, demonstrates pointer inspection/modification, allocates a dynamic array, uses pointer arithmetic to modify values, transfers results into the player's `Inventory`, and frees the dynamic memory. After running the demo, use **9) Show Inventory** and **10) Use Potion** to confirm gameplay effects and to compare manual `new[]/delete[]` with RAII-based cleanup.
   - Add tests `test_inventory.cpp` and `test_enemygroup.cpp` to `dungeongame/tests/` and run `make test`.
4. Demo & clean-up (15 min): Run tests and demo a short game snippet showing inventory usage and managing multiple enemies.

## Homework
- Extend `Inventory` to provide an iterator (or implement a linked-list backed `Inventory` as an alternate implementation).
- Modify `Player` to include an `Inventory` member and write tests that verify picking up/dropping items.
- Add a second `EnemyGroup` implementation backed by a linked list to contrast contiguous vs non-contiguous behavior.

## Resources & Scaffold
- Project scaffold files in `week02/scaffold/` include templates for `Inventory`, `EnemyGroup`, and tests.
- Build instructions: `make` (project root) or `dungeongame/tests/run_tests.sh` to run tests and game.

---

> Instructor notes:
> - **Changes to existing files:** No mandatory edits to `Character`, `Game`, `main`, or `Player` are required to complete the lab. The scaffold provides independent ADT files and tests that compile alongside the project. 
> - **Optional changes:** To integrate inventory into gameplay, add a member to `Player` (e.g., `Inventory inventory;`) and update `Player` constructors and tests. Minimal code snippet:
>
> ```cpp
> // in Player.h
> #include "Inventory.h"
> class Player : public Character {
>  public:
>    Inventory inventory; // default-constructed
> };
> ```
>
> - Encourage students to keep changes small and submit on a branch named `week02/<username>`.
