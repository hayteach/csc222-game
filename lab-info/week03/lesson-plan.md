# Week 03 — Template Classes & Linked Lists in C++

## Learning Objectives
- Understand C++ template classes and their role in generic programming
- Implement a generic singly-linked list template class
- Apply templates to existing game components (Inventory, EnemyGroup)
- Compare different container implementations (linked list vs array-based)
- Use modern C++ iteration patterns (range-based for loops) with templates

## In-class Activities (90 min)
1. Warm-up (10 min): Review last week's ADT implementations and discuss the limitations of array-based storage
2. Lecture (20 min): Template classes in C++ — syntax, instantiation, template parameters, and generic programming concepts. Compare linked lists vs contiguous arrays (Big-O analysis, memory layout, cache performance)
3. Guided lab (45 min): Students modify existing game code to use template-based containers:
   - Replace `Inventory`'s array implementation with `LinkedList<Item>`
   - Replace `EnemyGroup`'s `std::vector` with `LinkedList<Enemy>`
   - Update tests to demonstrate template-based iteration
   - Run the game to verify inventory and enemy management still work
4. Demo & clean-up (15 min): Show the linked list demo in-game and discuss template benefits

## Homework
- Extend the `LinkedList` template with additional functionality (find, insert, sort)
- Create a template-based `Stack<T>` or `Queue<T>` and integrate it into the game
- Compare performance between linked list and array implementations for different use cases

## Resources & Scaffold
- Project scaffold includes `LinkedList.h` template class
- Modified `Inventory.h` and `EnemyGroup.h` using templates
- Updated test files demonstrating template iteration
- Build instructions: `make` (project root) or `make test` to run tests

---

> Instructor notes:
> - **Key Changes:** Inventory and EnemyGroup now use LinkedList template instead of raw arrays/vectors
> - **Template Benefits:** Students see how one template class can work with different types
> - **Performance Discussion:** Linked lists have O(1) insertion/deletion but O(n) random access
> - **Modern C++:** Range-based for loops work with template iterators
> - **Optional Extension:** Students can implement additional template containers</content>
<parameter name="filePath">/Users/heidiahders/Documents/MendocinoCollege/Class/2026/Spring/CSC222/game/lab-info/week03/lesson-plan.md