Week 02 scaffold — Enemy class and tests

This scaffold contains minimal files and instructions to add an `Enemy` entity to the `dungeongame` project.

Files provided:
- `dungeongame/include/dungeongame/Enemy.h` — header skeleton
- `dungeongame/src/Enemy.cpp` — implementation skeleton

How to use:
1. Copy the files into the project (or merge their contents):
   - `cp -r dungeongame/include/dungeongame/Enemy.h ../../dungeongame/include/dungeongame/Enemy.h`
   - `cp dungeongame/src/Enemy.cpp ../../dungeongame/src/Enemy.cpp`
2. Add `Enemy.cpp` to compilation (Make/CMake already globs all `src/*.cpp` so it should be picked up).
3. Include and test: add tests in `dungeongame/tests/` to verify enemy behavior.

Suggested tasks for students:
- Implement enemy health and simple `takeDamage(int)` method.
- Implement `moveTowardsPlayer()` stub and test map placement.
- Add a combat unit test that exercises damage exchange.

Notes for instructors: These scaffold files are intentionally minimal — they are templates for students to modify and extend.
