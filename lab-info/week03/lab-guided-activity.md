# Week 3 — Guided Lab: Template Classes & Linked Lists

> **Note for students:** Before building or running tests, run `make clean` in the repository root. There is a `.gitignore` in this folder (`lesson/week03/.gitignore`) that prevents compiled objects and binaries from being committed — do not commit `dungeongame/bin/` or `dungeongame/obj/`.

## Goal
Students will learn about C++ template classes by implementing and using a generic linked list. By the end of the lab students will:
- Understand template syntax and generic programming
- Implement a template-based linked list class
- Replace existing game components to use templates
- Compare different container implementations

---

## Files you'll use
- `include/dungeongame/LinkedList.h` — Template class for singly-linked list
- `include/dungeongame/Inventory.h` — Now uses LinkedList<Item>
- `include/dungeongame/EnemyGroup.h` — Now uses LinkedList<Enemy>
- `tests/test_inventory.cpp` — Updated to test template iteration
- `tests/test_enemygroup.cpp` — Updated to test template iteration
- `CMakeLists.txt` — Build configuration
- `tests/run_tests.sh` — Convenience script

---

## Lab Plan (90 minutes)

### Part A — Warm-up (10 min)
1. Review last week's Inventory implementation (array-based with manual memory management)
2. Discuss limitations: fixed capacity, expensive resizing, contiguous memory requirements
3. Introduce linked lists as an alternative: dynamic size, O(1) insertion/deletion, non-contiguous

### Part B — Examine Template Class (15 min)
1. Open `LinkedList.h` and study the template implementation:
   - Template syntax: `template <typename T>`
   - Node structure with data and next pointer
   - Generic operations: append, prepend, removeAt, get
   - Iterator support for range-based for loops

2. Discuss how templates enable code reuse across different types

### Part C — Modify Game Components (30 min)
1. **Update Inventory** (15 min):
   - Examine how `Inventory.h` now uses `LinkedList<Item>`
   - Note that the interface remains the same but implementation changed
   - Update `Inventory.cpp` (now mostly empty - implementation moved to header)

2. **Update EnemyGroup** (15 min):
   - Examine how `EnemyGroup.h` now uses `LinkedList<Enemy>`
   - Compare with previous `std::vector` implementation
   - Discuss trade-offs between linked lists and vectors

### Part D — Update Tests & Verify (25 min)
1. **Update test files** (10 min):
   - `test_inventory.cpp`: Now uses range-based iteration instead of pointer arithmetic
   - `test_enemygroup.cpp`: Now uses template-based iteration
   - Discuss how templates enable modern C++ patterns

2. **Build and test** (15 min):
   ```bash
   cd /path/to/game
   make clean && make
   make test
   ```

3. **Run the game** (verify inventory still works):
   ```bash
   ./dungeongame/bin/dungeongame
   # Try options 8 (potions), 9 (show inventory), 10 (use potion)
   ```

### Part E — Template Demo (10 min)
1. Run the in-game linked list demo (option 11)
2. Discuss how one template class works with different types
3. Compare linked list vs array performance characteristics

---

## Key Concepts Covered

### Template Syntax
```cpp
template <typename T>
class LinkedList {
    // T can be any type: int, std::string, Item, Enemy, etc.
};

LinkedList<int> numbers;
LinkedList<Item> inventory;
```

### Generic Programming Benefits
- **Code Reuse**: One implementation works for many types
- **Type Safety**: Compile-time type checking
- **Performance**: No runtime type overhead

### Container Trade-offs
| Feature | Array/Vector | Linked List |
|---------|-------------|-------------|
| Random Access | O(1) | O(n) |
| Insertion/Deletion | O(n) | O(1) |
| Memory Layout | Contiguous | Scattered |
| Cache Performance | Excellent | Poor |
| Memory Overhead | Minimal | Node pointers |

---

## Common Issues & Solutions

### Compilation Errors
- **Template definitions in .cpp files**: Templates must be in headers (or use explicit instantiation)
- **Missing `#include <LinkedList.h>`**: Add to files using the template

### Runtime Issues
- **Iterator invalidation**: Don't modify list while iterating
- **Memory leaks**: LinkedList handles its own memory, but be careful with contained objects

### Template Tips
- Use `const` references for parameters to avoid copies
- Provide both const and non-const versions of accessors
- Consider iterator invalidation in your design

---

## Extension Activities (Optional)
1. **Add LinkedList features**: Implement `find()`, `insert()`, or `sort()` methods
2. **Create new templates**: Implement `Stack<T>` or `Queue<T>` using LinkedList
3. **Performance comparison**: Time operations on large datasets
4. **Template specialization**: Create special behavior for specific types

---

## Submission
- Ensure `make test` passes
- Game inventory functionality works correctly
- Submit on branch `week03/<username>`
- Include brief reflection on template benefits vs drawbacks</content>
<parameter name="filePath">/Users/heidiahders/Documents/MendocinoCollege/Class/2026/Spring/CSC222/game/lab-info/week03/lab-guided-activity.md