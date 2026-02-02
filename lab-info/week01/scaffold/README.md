Week 01 scaffold — Minimal starter files

Purpose: Provide students with a minimal, copyable scaffold to start the Week 01 lab without touching the main project until ready to integrate.

Included files (relative to scaffold root):
- `dungeongame/include/dungeongame/Character.h` — minimal Character header
- `dungeongame/src/Character.cpp` — minimal implementation
- `dungeongame/include/dungeongame/Player.h` — minimal Player header
- `dungeongame/src/Player.cpp` — minimal implementation
- `dungeongame/include/dungeongame/Game.h` — minimal Game header
- `dungeongame/src/Game.cpp` — minimal game loop implementation
- `dungeongame/src/main.cpp` — main that constructs and runs Game

How to use:
1. Copy files into the project tree, e.g.:
   cp -r dungeongame/include/dungeongame ../dungeongame/include/dungeongame
   cp dungeongame/src/*.cpp ../dungeongame/src/
2. Build with the project Makefile or CMake (see lab instructions).
3. Edit and extend the scaffold to implement lab tasks.

Notes for instructors:
- These files are intentionally small and focused on the learning goals for Week 01.
- If you prefer, students can fork the repo and work in their own `week01/<username>` branches.
