Week 02 scaffold — ADTs, Arrays, and Pointers

This scaffold provides templates and exercises for implementing Abstract Data Types (ADTs) and working with contiguous arrays and raw pointers in C++.

Files provided (scaffold copies included here and placed under `dungeongame/`):
- `dungeongame/include/dungeongame/Inventory.h` — array-backed Inventory ADT (header)
- `dungeongame/src/Inventory.cpp` — implementation
- `dungeongame/tests/test_inventory.cpp` — unit tests for `Inventory`
- `dungeongame/include/dungeongame/EnemyGroup.h` — contiguous storage wrapper for `Enemy` objects
- `dungeongame/src/EnemyGroup.cpp` — implementation
- `dungeongame/tests/test_enemygroup.cpp` — unit tests for `EnemyGroup`

How to use:
1. Files are already available in the scaffold and the project — students can copy or merge as needed.
2. Build and run tests: `make` and then `make test`, or run `dungeongame/tests/run_tests.sh`.
3. Inspect `Inventory::rawData()` and `EnemyGroup::rawData()` to practice pointer arithmetic and traversal.

Suggested student tasks:
- Implement `Inventory` add/remove and dynamic resize.
- Use pointer arithmetic on `Inventory::rawData()` to traverse items in a test.
- Implement a linked-list backed `Inventory` as an extension to contrast contiguous vs non-contiguous behavior.
- Modify `Player` to hold an `Inventory` (optional) and add tests for picking up/dropping items.

Notes for instructors: The scaffold is ready-to-run. Encourage small, test-driven changes and branch-based submissions `week02/<username>`.
