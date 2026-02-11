# Dungeon of Data Structures — Week 1

Purpose: Starter scaffold for the semester-long Dungeon game project. This week focuses on C++ review, project setup and the basic game loop so students can compile and run a multi-file project.

✅ What's included
- Minimal, commented source files: `dungeongame/src/main.cpp`, `dungeongame/src/Game.h/.cpp`, `dungeongame/src/Character.h/.cpp`, `dungeongame/src/Player.h/.cpp`
- `Makefile` to build the project
- `tests/run_tests.sh` simple compile-and-run helper
- `docs/lesson-plan-week01.md` teacher notes and in-class schedule

Build & run (cross-platform) ✅

macOS / Linux (Makefile)

1) Build:
   ```bash
   make        # builds into ./bin/dungeongame
   ```
2) Run:
   ```bash
   ./bin/dungeongame
   ```

Cross-platform (single command)

- Run the cross-platform launcher (Python). It will call the correct build backend for the platform:
  ```bash
  python3 build.py
  ```
  If `python3` is not available the VS Code build task and `scripts/run_build.sh` will try `python` as a fallback. On Windows you can also use `python build.py` from PowerShell or CMD if Python is on PATH.

- Alternatively, the helper script `scripts/run_build.sh` will also prefer `python3` and fall back to `python` and can be called from POSIX shells:
  ```bash
  ./scripts/run_build.sh
  ```

Windows (no CMake required)

- Command Prompt (if you have g++ on PATH):
   ```bat
   build.bat
   ```

- PowerShell (native script):
   ```powershell
   ./build.ps1
   ```

Preferred build methods (cross-platform)

We recommend students use the Makefile (macOS / Linux / WSL) or the provided Windows scripts (`build.bat` / `build.ps1`). These scripts are intentionally simple and do not require CMake. CMake remains in the repo as an optional path for users who prefer IDE integration (Visual Studio) or need the `compile_commands.json` for advanced tooling.

macOS / Linux (Makefile)

1) Build:
   ```bash
   make        # builds into ./bin/dungeongame
   ```
2) Run:
   ```bash
   ./bin/dungeongame
   ```

Windows

- Command Prompt (if you have g++ on PATH):
   ```bat
   build.bat
   ```

- PowerShell (native script):
   ```powershell
   ./build.ps1
   ```

Notes
- The Makefile and the Windows scripts are provided so students can compile without installing CMake. Use the Makefile or the Windows scripts as the default build flow for the course.
- The pointers demo has been integrated into the main game; select **option 8: Prepare Potions (Pointers demo)** from the in-game menu to run the demo. The standalone `dungeongame/src/pointers_demo.cpp` is deprecated and no longer built as a separate program to avoid confusion and duplicate `main()` errors.

VS Code: Build & Debug (F5)
- Open the Run view and select the appropriate debug configuration:
  - **Debug dungeongame (POSIX)** on macOS / Linux
  - **Debug dungeongame (Windows)** on Windows
- The selected configuration uses **Build: cross-platform** as its `preLaunchTask`, so pressing F5 will automatically build the project before launching the debugger. If you prefer to build manually, run `make` (POSIX) or `python build.py` (cross-platform launcher) first.

Teacher notes: See `docs/lesson-plan-week01.md` for in-class agenda, demo steps, and student exercises.

---

If you'd like, I can also add starter test cases or a sample Valgrind check for memory leaks.