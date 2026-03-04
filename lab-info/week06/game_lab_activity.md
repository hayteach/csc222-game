# Lab 06 Activity — Pointer & Reference Concepts in the Dungeon Game

This lab brings together the abstract `Shape` hierarchy assignment with the pointer/reference topics introduced this week.  You'll modify parts of the existing `dungeongame` codebase so that it uses pointers, arrays, and dynamic memory just like a real application would.  The goal is to learn how pointer arithmetic, memory addresses, and polymorphism work in a context you already know.

## Objectives

- Apply pointer concepts in a small game setting
- Use arrays or vectors of pointers to manage collections of objects
- Practice taking and using memory addresses of variables and objects
- Demonstrate polymorphism through pointers to base class
- Observe contiguous vs. non-contiguous memory with arrays

## Tasks

1. **Character / NPC hierarchy integration**
   - The project already defines a `Character` base class from which `Player` and `Enemy` derive.  As part of the lab activity you should **rename the existing `Enemy` class to `NPC`** (non‑player character) to make it a more generic subclass.  Once `NPC` exists, you can create further derived types such as `Enemy`, `Boss`, `Merchant`, etc., each with their own behaviour.
   - Keep the `Character.h` header largely unchanged; add or rename `NPC.h` (formerly `Enemy.h`) and place any additional subclasses under `dungeongame/include/dungeongame/` with corresponding source files under `src/`.
   - Write a small test program (`character_test.cpp` or extend `combat_test.cpp`) that creates various `Character` and `NPC` objects (via pointers) to exercise constructors and virtual methods, demonstrating polymorphism.  Example: store a `Boss` pointer in a `Character*` array and call `calculateAttack()` on each entry.

2. **Pointer-based enemy list**
   - In `EnemyGroup` (or create a new class), change the container that holds `Enemy` objects to use a dynamically-allocated array or `std::vector<Enemy*>` instead of storing objects by value.  Use `new`/`delete` when creating/destroying enemies.
   - Write accessor functions that return `Enemy*` and show how pointer arithmetic can be used to traverse the collection.
   - Add a function to print the addresses of each `Enemy` instance (use `printf("%p\n", (void*)ptr);`) to illustrate contiguous allocation when using an array vs. non-contiguous when using `new` individually.

3. **Pointer math exercise**
   - Create a simple `int` array in `main.cpp` or a new file.  Fill it with values, then use a pointer to iterate through the array and manipulate values using pointer arithmetic (`*(ptr + i)`).
   - Print both the pointer value (address) and the dereferenced value for each element.

4. **Reference demonstration**
   - Add a function that takes an `Enemy&` or `Shape&` parameter and modifies the object (e.g. changes height/width or subtracts hit points).  Call it from various places in the game to show how references are aliases for the original object.

5. **Range and type sizes**
   - In one of your test programs, include `<limits>` and print `std::numeric_limits<int>::min()` and `max()` for `int`, `long`, and `long long`.  Add a comment explaining why ranges might differ between compilers.
   - Use a compound declaration, e.g. `unsigned long long bigNum = 0ULL;` and note that the suffix extends the range.

6. **Documentation & reflection**
   - In the `lab06.md` or add a new section to `lesson_pointers.md` summarizing how you applied each learning outcome within the game project.  Include code snippets where appropriate.

## Submission

- Ensure your project still builds and tests pass after your modifications.
- Include any new source/header files in the repository.
- Update `dungeongame/tests/run_tests.sh` or add new test programs for the pointer exercises.

> **Tip:** work incrementally—start with shapes before touching game pointers—and use `gdb` or `valgrind` if you run into memory issues.

---

This activity should make the theoretical concepts tangible by weaving them into the existing game code you’ve been developing throughout the semester.  Have fun exploring the memory model while strengthening the dungeon game!