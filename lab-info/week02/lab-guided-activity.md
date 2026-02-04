# Week 2 — Guided Lab: OOP Review (Classes & Objects)

> **Note for students:** Before building or running tests, run `make clean` in the repository root to remove old build artifacts. There is a `.gitignore` in this folder (`lesson/week02/.gitignore`) that prevents compiled objects and binaries from being committed — do not commit `dungeongame/bin/` or `dungeongame/obj/`.

## Goal
Students will practice designing and implementing class methods for a basic character/combat system using the provided starter project. By the end of the lab students will:
- Understand class headers/implementation separation
- Implement/extend character behaviors (damage, attack, heal)
- Add new enemy types and test combat
- Use CMake to build and run the test harness

---

## Files you'll use
- `include/dungeongame/Character.h` — base class interface
- `src/Character.cpp` — existing implementations for core methods
- `include/dungeongame/Player.h` and `src/Player.cpp` — player specialization
- `include/dungeongame/Enemy.h` and `src/Enemy.cpp` — enemy specialization (starter provided)
- `tests/combat_test.cpp` — small harness to run basic combat
- `CMakeLists.txt` — build configuration
- `tests/run_tests.sh` — convenience script (requires cmake)

---

## Lab Plan (90 minutes)

### Part A — Warm-up (10 min)
1. Open `Character.h` and `Character.cpp`. Read the members: `health`, `maxHealth`, `attack`, `defense`, and method signatures.
2. Instructor quick quiz (5 questions on public/private, header vs cpp, constructors).

### Part B — Inspect & Run (10 min)
1. In terminal run:

```
cd dungeongame
bash tests/run_tests.sh
```

Note: This uses CMake. If `cmake` isn't installed, install it (or build with your preferred method).

2. Discuss the `combat_test` output; it simulates a simple fight and prints damage per hit.

### Part C — Modify Character Behavior (25 min)
1. Implement or inspect `takeDamage()` — ensure it clamps health at zero.
2. Modify `calculateAttack()` to add a small random variance for critical hits (optional as a challenge).
3. Add a `heal(int amount)` method to restore health but not exceed `maxHealth`.

Instructor hint: After changes, re-run `bash tests/run_tests.sh` and confirm `combat_test` still passes.

### Part D — Player Progression (20 min)
1. Inspect `Player` methods: `gainExperience`, `levelUp`, and `addGold`.
2. Implement `gainExperience` such that when the player reaches the threshold (e.g., 100 * level) they level up.
3. On `levelUp`, increase `maxHealth`, `attack`, `defense`, and fully heal the player.

Challenge: Change the threshold to use an exponential curve or design your own leveling formula.

### Part E — Add New Enemy Types (15 min)
1. Create at least 3 enemies with different stats by adding instantiations in `tests/combat_test.cpp` or by adding new tests.
2. Run the test harness and verify expected winners for each encounter.

Optional: Add an `EnemyFactory` helper to create enemies by name.

---

## Assessment Checklist (what you must show the instructor)
- [ ] Project builds (no compile errors)
- [ ] `combat_test` runs and prints combat events
- [ ] Player levels up when gaining enough experience
- [ ] Added at least 3 enemy types and tested combat
- [ ] Pushed a commit with a descriptive message

---

## Instructor Notes
- This lab is intentionally small so students can focus on class design and methods.
- Encourage pair programming and frequent commits.
- Use `combat_test` as a quick unit test — extend it to check edge cases.

### Style note: headers and `using namespace std;`
- **Do not** put `using namespace std;` in header files. This causes the entire `std` namespace to be imported into every translation unit that includes the header, which can lead to name collisions, surprising compilation errors, and harder-to-debug code. Instead, prefer:
  - Explicit `std::` qualifiers in headers (e.g., `std::string`) so the interface is clear and safe for all users.
  - If desired, add `using namespace std;` or selective `using std::cout;` inside `.cpp` files only, where the effect is limited to a single translation unit.

- **Include vs availability:** Always include the headers that declare the symbols your header uses (e.g., if `Player.h` uses `std::string` add `#include <string>` directly in `Player.h`). Relying on transitive includes (another header including `<string>` for you) is brittle — if that header changes, your header may fail to compile. Make headers self-sufficient: "include what you use."

---

Happy teaching! 🎓
