# Week 01 — Guided Activity: Project Setup & Basic Game Loop

Duration: 90 minutes

Goal: Students will learn how to create the project structure, add header/source files, wire the build system (Make/CMake) and implement a minimal playable game loop.

Prerequisites:
- Basic C++ knowledge (classes, headers, .cpp files)
- Git and basic terminal usage
- A C++ compiler (g++/clang) and make or cmake installed

Materials provided:
- Starter repository (this project)
- `dungeongame` subdirectory scaffold

Activity steps (with suggested timings):

1) Project scaffolding (10 min)
- Create the following tree under the repo root (or confirm it exists):
  - dungeongame/include/dungeongame/  (for headers)
  - dungeongame/src/                 (for .cpp files)
  - dungeongame/tests/               (for test harness)
  - dungeongame/bin/                 (ignored, for runtime binaries)
  - dungeongame/obj/                 (ignored, for objects)
- Add a top-level `Makefile` or `CMakeLists.txt` to build the project.

2) Implement base Character (20 min)
- Create `dungeongame/include/dungeongame/Character.h` with:
  - struct Position { int x, y; }
  - class Character { protected: name, health, maxHealth, attack, defense, pos; public: constructor, get/set position, getHealth(), takeDamage(), calculateAttack(), heal(), isAlive(), displayStats() }
- Implement `dungeongame/src/Character.cpp` with basic method bodies (clamp health at 0, simple calculateAttack returns attack).

3) Implement Player (15 min)
- Create `dungeongame/include/dungeongame/Player.h` deriving from Character, add level, experience, gold and public methods: move(dx,dy), displayStats(), gainExperience(), levelUp(), addGold().
- Implement `dungeongame/src/Player.cpp` with movement bounds (5x5 map), starting stats, and level-up behavior.

4) Implement Game shell & menu (20 min)
- Create `dungeongame/include/dungeongame/Game.h` with Game class that holds a Player, a 5x5 map array and methods: initMap(), placePlayerOnMap(), displayMap(), displayMenu(), processChoice(int), run().
- Implement `dungeongame/src/Game.cpp`: read numeric choices, move the player, show stats, quit. Make sure `main` constructs Game and calls run().
- Add a menu item like "7) Encounter Enemy (demo)" for later expansion.

5) Add Enemy skeleton (10 min)
- Create `dungeongame/include/dungeongame/Enemy.h` deriving from Character with additional fields like expReward and goldReward and a method `moveTowards()`.
- Implement `dungeongame/src/Enemy.cpp` with simple behavior and a constructor that syncs base stats.

6) Add tests and harness (10 min)
- Add `dungeongame/tests/combat_test.cpp` that instantiates enemies and players and verifies:
  - Enemy stats and movement
  - A simulated combat victory
  - A simulated defeat
  - Deterministic flee success/failure via seeded rand
- Add `tests/run_tests.sh` which calls `make -C .. test` or runs the test binary directly.

7) Build and run (5 min)
- From repo root: `make test` (or `cmake` flow).
- Confirm test output (e.g., `combat_test: PASS`) and that `./dungeongame/bin/dungeongame` runs interactively.

Instructor notes & extensions:
- Encourage students to keep each week's changes on a branch named `weekNN/<username>` and open a PR for review.
- Extend combat with more actions (items, use, multiple enemies) in later weeks.
- Replace the ad-hoc tests with a unit test framework (Catch2 or GoogleTest) when adding more complex behavior.

Assessment checklist (student deliverables):
- [ ] Project builds with `make` or `cmake` (no compile errors)
- [ ] `combat_test` runs and asserts key scenarios pass
- [ ] Player levels up when gaining the right experience
- [ ] Added and tested at least one Enemy type
- [ ] Commit history per small logical steps and pushed to a branch

Hints & troubleshooting:
- If headers are "file not found" in your editor, generate `compile_commands.json` (CMake: `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON`) or set your editor include paths to `dungeongame/include`.
- If `.gitignore` isn't ignoring bin/ or obj/, run: `git rm -r --cached dungeongame/bin dungeongame/obj` then commit.

---

Happy coding! If you'd like, I can also:
- Add a Makefile template or CMake template to the repo,
- Add a GitHub Actions workflow to run `make test` on PRs, or
- Create a starter commit/branch that students can fork from.

