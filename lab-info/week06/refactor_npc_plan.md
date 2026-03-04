# Refactor Plan: Convert `Enemy` to `NPC` and Demonstrate Lab Activity

This document outlines a step-by-step plan to modify the existing game code so that it supports the Week 06 lab activity.  You'll rename the `Enemy` class to `NPC`, add new subclasses, update containers, and include pointer exercises. A separate walkthrough will demonstrate the changes in practice.

## High-Level Plan

1. **Rename `Enemy` to `NPC`**
   - Update header (`Enemy.h` -> `NPC.h`) and source (`Enemy.cpp` -> `NPC.cpp`).
   - Change class name and references throughout the project.
   - Adjust comments and documentation accordingly.

2. **Introduce new NPC subclasses**
   - Create at least one additional subclass, e.g. `Boss` or `Merchant`, inheriting from `NPC`.
   - Provide unique attributes or override a virtual method for each new type.

3. **Update container classes**
   - Modify `EnemyGroup`/`EnemySpawner` to operate on `NPC` (rename to `NPCGroup`/`NPCSpawner` as appropriate).
   - Change internal storage to `std::vector<NPC*>` or a dynamically allocated array to practice pointers and pointer arithmetic.
   - Add helper functions that return raw pointers and print addresses.

4. **Extend tests**
   - Create a new test file (e.g. `npc_test.cpp`) that demonstrates:
     - Construction of different NPC types
     - Polymorphic calls via `NPC*` or `Character*`
     - Pointer arithmetic on an array of `NPC*`
     - A function taking `NPC&` to modify an object
     - Numeric limits and range examples
   - Update `combat_test.cpp` to include or delegate to the pointer tests if desired.

5. **Update lab activity documentation**
   - Add a comprehensive walkthrough file (`npc_walkthrough.md`) that implements each step and shows code snippets and output.
   - Ensure `game_lab_activity.md` refers to the walkthrough for guidance.

6. **Build & verify**
   - Run the build (`make` or existing scripts) and run tests to confirm everything still compiles and executes.
   - Fix any resulting compile errors or missing includes.

---

Once the plan is ready, the walkthrough file will walk through each of these steps with commands, file edits, and sample code to make the process reproducible.  This allows students to follow along and see exactly how to integrate the lab concepts into the game project.