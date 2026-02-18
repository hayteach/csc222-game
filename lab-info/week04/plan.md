...existing code...

## Plan — integrate Week 04 ADTs into DungeonGame

Goal
- Extend DungeonGame so students apply queue.remove(n), a stack-based undo, and postfix spell evaluation in a connected feature set that continues into Lab 05.

Core ideas to add
1. Spawn queue control — EnemySpawner uses queueADT<Enemy>.
   - New API: EnemySpawner::skipEnemies(int n) → calls spawnQueue.remove(n).
   - Gameplay use: player command / power that discards the next n enemies.

2. Action history (undo) — use stackADT<Action>.
   - Push reversible Action objects on each player action.
   - Provide Game::undoLastAction() to pop and revert the most recent action.

3. Postfix spell evaluator — SpellEvaluator evaluates RPN expressions for spells.
   - Example usage: evaluatePostfix("6 3 + 2 *") → 18, used for spell damage/heal formulas.

Files to add (suggested)
- src/game/enemy_spawner.h / enemy_spawner.cpp
  - void skipEnemies(int n);
  - Uses queueADT<Enemy> (arrayQueue implementation).
- src/game/action_history.h / action_history.cpp
  - void pushAction(const Action&);
  - bool undoLastAction();
- src/game/spell_evaluator.h / spell_evaluator.cpp
  - int evaluatePostfix(const std::string&);
- src/tests/test_queue_remove.cpp
- src/tests/test_action_undo.cpp
- src/tests/test_spell_eval.cpp

Implementation steps (student-friendly)
1. Add unit tests that validate queue.remove(n) behavior (n ≤ 0, 0 < n < size, n ≥ size).
2. Implement EnemySpawner::skipEnemies using spawnQueue.remove(n); wire a player command (e.g., "spawn skip N") to call it.
3. Implement ActionHistory with push/undo and add small reversible Actions (move, pick/drop).
4. Implement a small postfix evaluator and hook it to one spell (e.g., custom damage formula).
5. Add demo scenario and README instructions showing how to trigger each feature.

Example snippets
- skipEnemies
```cpp
void EnemySpawner::skipEnemies(int n) { spawnQueue.remove(n); }
```
- postfix evaluator usage
```cpp
int dmg = SpellEvaluator::evaluatePostfix("6 3 + 2 *"); // 18
```

### Menu / in‑game commands (UI + CLI bindings)

- Main Menu → Gameplay → Spawn Control → "Skip Next N Enemies..."
  - Action: prompt for N → EnemySpawner::skipEnemies(N)
  - Shortcut: S
  - CLI: `spawn skip N`
  - HUD feedback: "Skipped N enemies — X remaining"

- Main Menu → Gameplay → Action History → "Undo Last Action" / "Undo N Actions..."
  - Action: prompt for k (default 1) → ActionHistory::undoLast(k)
  - Shortcut: U
  - CLI: `undo [k]`
  - HUD feedback: "Undid k action(s); current state restored"

- Main Menu → Magic → "Cast RPN Spell..."
  - Action: enter postfix expression → SpellEvaluator::evaluatePostfix(expr)
  - Shortcut: C
  - CLI: `cast <postfix-expression>`
  - HUD feedback: show evaluated result and effect applied (damage/heal)

- Debug / Developer Menu
  - `show queue` — displays spawn queue
  - `show history` — displays action/undo stack
  - `run spawn-skip-demo` / `run postfix-demo` — automated scenarios

UI notes
- All menu/CLI actions must log a one-line result to the HUD/console and update any queue/stack HUD panels.
- Invalid inputs (negative N, malformed RPN) should show a clear error and be a no-op.

Acceptance
- Menu/CLI entries trigger the corresponding API calls and are covered by demo/tests described in the plan.

Tests / acceptance criteria
- queue.remove(n): tests for negative, zero, partial, and full removals.
- EnemySpawner: skip command removes expected enemies (demo script verifies).
- ActionHistory: undo reverts last actions (2+ test cases).
- SpellEvaluator: correct numeric results for provided RPN expressions; malformed input handled gracefully.

Milestones (recommended)
- 30–60 min: tests for queue.remove(n)
- 60–120 min: EnemySpawner skip feature + demo command
- 60 min: ActionHistory + undo
- 60 min: SpellEvaluator + integrate single spell
- 30 min: write demo README and run tests

Grading hints (instructor)
- Primary requirement: spawnQueue.remove(n) used in game and tested.
- Secondary: stack undo + postfix evaluator integrated and tested.
- Bonus: polish UI, extra tests, variable support in RPN spells.

Demo scenario (quick verification)
1. Start demo mode.
2. Add 5 enemies to spawn queue.
3. Use "spawn skip 2" → first two enemies removed; next enemy is the old 3rd.
4. Perform 3 actions, call undo twice → verify state rollback.
5. Cast a spell using RPN expression and verify computed effect.

...existing code...