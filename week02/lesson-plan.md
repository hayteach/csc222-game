# Week 02 — Dungeon Game: Enemies & Combat

## Learning Objectives
- Introduce new game entities (Enemies) and extend the game model.
- Practice adding headers and source files to a multi-file C++ project.
- Write and run unit tests for new behavior.
- Use the project's build system (Make/CMake) and debug in VS Code.

## In-class Activities (90 min)
1. Warm-up (10 min): Review last week's code (Game, Player, Character).
2. Lecture (20 min): Design an `Enemy` class (inherit from `Character`). Discuss attributes (HP, damage), constructors, and simple AI (`moveTowardsPlayer()` stub).
3. Guided lab (45 min): Students implement `Enemy.h`/`Enemy.cpp`, add to build, and write a test that spawns an enemy and verifies basic behavior.
4. Demo & clean-up (15 min): Run tests, demo gameplay with an enemy present, discuss improvements.

## Homework
- Extend enemy AI to chase the player when within N tiles.
- Add a `combat` interaction where Player and Enemy exchange damage.
- Write tests covering combat outcomes and edge cases.

## Resources
- Project scaffold files in `week02/scaffold/`
- Build instructions: `make` (project root) or `dungeongame/scripts/run_game.sh`

---

> Instructor note: Encourage students to keep changes minimal and to submit via a new branch named `week02/<username>`.
