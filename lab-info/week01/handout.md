Week 01 Handout — Project Setup & Basic Game Loop

Overview
-------
This worksheet walks through creating a small C++ project for a text-based dungeon game. Follow the steps in the guided activity to scaffold the project, implement core classes, and get the game running.

Quick start
-----------
1. Copy scaffold files into `dungeongame/` (or clone the starter repo).
2. Build: `make` from repo root.
3. Run tests: `make test` (or `dungeongame/tests/run_tests.sh`).

Key Concepts
------------
- Header and implementation separation
- Basic class design (Character base, Player derived)
- Turn-based game loop and simple I/O
- Unit testing with small test harness

Exercises (suggested)
---------------------
- Implement a new `Enemy` subclass and test a simple combat interaction.
- Add a menu option to spawn an enemy and fight.
- Improve `Player::gainExperience()` with a more interesting level curve.

Notes
-----
Ask your instructor if you get stuck — use the test harness to verify behavior.
