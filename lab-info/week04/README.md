---
# Week 04 — Stack ADT (Array-based)

> **Please review all tabs before proceeding on.** ✅

## Overview

A **stack** is an abstract data type (ADT) that models a Last-In—First-Out (LIFO) collection. Think of a stack of plates or a stack of papers: the last item added is the first item you remove.

## Learning objectives

- Understand the **Stack ADT** and its common operations
- Implement a stack interface (`stackADT`) and an **array-based** stack
- Write and run tester programs to validate stack behavior

---

## Definition of a Stack

- A stack stores elements in LIFO order: Last In — First Out.
- Real-world analogy: the top plate is always the first one used.

## Stack operations

All stacks should provide a common interface so user code can work with any implementation (array or linked list).

Common operations:

- `initializeStack()` — reset to empty
- `isEmptyStack()` — true if empty
- `isFullStack()` — true if full (array implementation)
- `push(ItemType)` — add an item to the top
- `top()` — read the top item without removing it
- `pop()` — remove the top item

---

## Array-based implementation (concept)

Attributes required for an array-based stack:

- `maxStackSize` — maximum capacity of the underlying array
- `stackTop` — index/position of the current top element
- `*list` — pointer to the dynamically allocated array of `ItemType`

Extra methods / special members you should implement:

- `arrayStack(int maxSize = 100)` — constructor (default size)
- `arrayStack(const arrayStack& other)` — copy constructor
- `copyStack(const arrayStack& other)` — helper to copy contents
- `~arrayStack()` — destructor to free memory
- `arrayStack& operator=(const arrayStack& other)` — assignment operator

> Note: `stackADT` should be an abstract class (pure virtual methods). Concrete implementations (like `arrayStack`) provide the definitions.

---

## Layout Table

| Component | Purpose |
|---|---|
| `stackADT` | Abstract interface declaring stack operations |
| `arrayStack` | Array-based implementation of `stackADT` |
| `maxStackSize`, `stackTop`, `list` | Internal storage & state for `arrayStack` |
| Special members | ctor, copy ctor, `copyStack`, dtor, `operator=` |
| `arrayStackTester.cpp` | Program to exercise and verify stack behavior |

---

## Files to review / expected filenames

- `stackADT.h`
- `arrayStack.h`
- `arrayStack.cpp`
- `arrayStackTester.cpp`

---

## Testing the array stack

Typical tester actions:

1. Construct a stack
2. `push()` several items
3. Observe `top()` and `isEmptyStack()`/`isFullStack()`
4. `pop()` items and confirm LIFO order
5. Test edge cases: popping from empty stack, pushing to a full stack, copy/assignment correctness

Suggested compile command (example):

```
# g++ example (adjust filenames & flags as needed)
g++ -std=c++17 arrayStack.cpp arrayStackTester.cpp -o arrayStackTester
./arrayStackTester
```

---

## Lab tasks (step-by-step) 🔧

1. Review the provided header `stackADT.h` and the array-based UML.  
2. Implement `arrayStack` in `arrayStack.h` / `arrayStack.cpp`.  
3. Implement and thoroughly test: copy constructor, assignment operator, destructor.  
4. Write/complete `arrayStackTester.cpp` to exercise normal and boundary behavior.  
5. Run tests and fix bugs until all operations behave as specified.

---

## Exercises / suggested test cases 💡

- Push 10 items, then pop them — verify order is reversed
- Copy a non-empty stack and verify independent storage (mutating one doesn't change the other)
- Assign one stack to another (use `operator=`) and verify correctness
- Attempt to push when full and ensure `isFullStack()` reports true
- Attempt to pop when empty and ensure method handles it safely (document expected behavior)

---

## Reference

Malik, D. (2018). _C++ Programming: Program Design Including Data Structures_ (5th ed.), Chapter 17. ISBN-13: 978-1-337-11756-2

---

## Next steps

- Review the listed files and tell me if you want starter code added to the repository or automated testers created. ✨
