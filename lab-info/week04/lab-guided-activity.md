# Week 04 — Lab guided activity (Instructor notes)

Duration: 90–120 minutes

Learning objectives
- Reinforce the Queue ADT by adding and testing `remove(n)` semantics.
- Apply queues and stacks in a small game: spawn‑queue control and undo history.
- Build and test a postfix (RPN) expression evaluator and use it for spell effects.
- Practice writing unit tests and integrating new features into an existing codebase.

Preparation (before class)
- Ensure students have the `week04` branch checked out.
- Ask them to build the project locally before class:
  - cmake -S dungeongame -B dungeongame/build
  - cmake --build dungeongame/build --target dungeongame_exe
- Familiarize yourself with these files (open them in the editor):
  - `lab-info/week04/src/queueADT.h`, `lab-info/week04/src/arrayQueue.h`, `lab-info/week04/src/arrayQueueTester.cpp`
  - `dungeongame/include/dungeongame/Game.h`, `dungeongame/src/Game.cpp`
  - `dungeongame/include/dungeongame/EnemySpawner.h`, `dungeongame/src/EnemySpawner.cpp`
  - `dungeongame/include/dungeongame/ActionHistory.h`, `dungeongame/src/ActionHistory.cpp`
  - `dungeongame/include/dungeongame/SpellEvaluator.h`, `dungeongame/src/SpellEvaluator.cpp`
  - tests: `dungeongame/tests/test_action_undo.cpp`, `dungeongame/tests/test_enemy_spawner.cpp`, `dungeongame/tests/test_spell_eval.cpp`

Lesson flow (step‑by‑step)
1) Warm‑up & motivation (10 min) ✅
   - Quick review: FIFO vs LIFO and where each is useful.
   - Show one worked postfix example from `lab-info/week04/lesson.md` and evaluate by hand.
   - Run `arrayQueueTester` to demonstrate `remove(n)` behavior.
     - Command (lab files): g++ -std=c++17 lab-info/week04/arrayQueueTester.cpp -o arrayQueueTester && ./arrayQueueTester

2) Queue.remove(n) — review & edge cases (10 min) ⚠️
   - Show `queueADT::remove(int n)` contract in `queueADT.h`.
   - Walk through `arrayQueue::remove(int n)` implementation; highlight modular arithmetic and the three cases: n ≤ 0, 0 < n < size, n ≥ size.
   - Ask students: "What happens to front/rear/count?" — short quiz question.

3) Spawn‑queue in the game (15 min) 🔧
   - Explain the purpose of `EnemySpawner` (spawn queue for demo enemies).
   - Demonstrate `spawn skip N` in the running game:
     - Menu: `Spawn Control (skip N)` → enter N
     - Debug: `Show Spawn Queue`
   - Exercise: have students change the default spawn list (in `EnemySpawner` constructor) and verify `skipEnemies()`.

4) Undo system (30 min) — build & test (hands‑on) ♻️
   - Introduce `ActionHistory` and the idea that `undo` uses a stack of reversible actions.
   - Walk students through adding a `Move` action (already done) and then add exercises to implement reversible `Pick` and `Drop`.
   - Demonstrate the `UsePotion` undo: show how we save previous health + the used item.
   - Student task (paired):
     - Implement `pushPick`, `pushDrop`, `pushUsePotion` (if not already provided in scaffold).
     - Add the corresponding `undo` behavior.
     - Run `dungeongame/tests/test_action_undo.cpp` and fix failing assertions.
   - Test command: run CTest or the test binary once built:
     - cmake --build dungeongame/build --target test_action_undo
     - ./dungeongame/build/bin/test_action_undo

5) Postfix spells — evaluator + multiple effects (20 min) ✨
   - Short explanation of RPN evaluation algorithm using a stack.
   - Walk through `SpellEvaluator::evaluatePostfix()` and show error handling for malformed input and divide‑by‑zero.
   - Demonstrate hooking an RPN result to multiple spell effects (heal, gold, damage spawn) in `Game::handleCastSpell()`.
   - Exercise: have students add another effect (e.g., temporary defense buff or double‑gold) and write a test for it.
   - Run unit test for evaluator:
     - cmake --build dungeongame/build --target test_spell_eval
     - ./dungeongame/build/bin/test_spell_eval

6) Integrate + demo scenarios (15 min)
   - Students run the game and perform these scenarios:
     - Spawn‑skip demo: add several enemies, call `Spawn Control (skip N)`, verify `Show Spawn Queue`.
     - Undo demo: move several steps, pick/drop an item, use a potion → call `Action History (undo)` to revert.
     - Postfix demo: cast `6 3 + 2 *` and choose each spell effect; observe heal/gold/damage.
   - Have a couple of students present their successful runs.

7) Wrap‑up, common pitfalls & homework (10 min) 💡
   - Common mistakes to highlight:
     - Off‑by‑one in `remove(n)` (front index arithmetic).
     - Forgetting to store state needed to undo (e.g., previous health or dropped item index).
     - Not validating postfix tokens before conversion.
   - Homework / extension ideas:
     - Add undo for combat actions (damage/heal reversal).
     - Extend `SpellEvaluator` to accept variables (player level) or functions.
     - Replace `EnemySpawner`'s internal container with `arrayQueue<T>` from the lab and compare behavior.

Instructor checklist (before leaving class)
- [ ] All students can run `arrayQueueTester` and the three new unit tests.
- [ ] Each student has demonstrated spawn‑skip, undo, and casting an RPN spell.
- [ ] Push classroom changes to the `week04` branch and open PR if required.

Useful commands (quick reference)
- Build game: cmake -S dungeongame -B dungeongame/build && cmake --build dungeongame/build --target dungeongame_exe
- Run single test binary: ./dungeongame/build/bin/test_action_undo
- Run postfix example (lab file): g++ -std=c++17 lab-info/week04/infix_to_postfix.cpp lab-info/week04/postfix_eval.cpp -o expr_eval && ./expr_eval

Assessment / expected deliverables
- Short lab submission (zip or PR):
  - Small change/addition demonstrating `remove(n)` or `undo` for a new action.
  - Unit test that validates the new behavior.
- Grading pointers: verify correctness and test coverage, plus a 1‑paragraph explanation of the design choice.

Notes for remote teaching
- Use a shared screen to step through `arrayQueue::remove` and `SpellEvaluator::evaluatePostfix` line‑by‑line.
- Ask students to paste their failing test output in chat for quick triage.

---

If you want, I can also:
- generate a short student handout (steps + starter TODOs), or
- create a demo script (`run spawn-skip-demo` / `run postfix-demo`) and add it to `dungeongame/scripts`.
