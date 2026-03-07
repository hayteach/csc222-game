# Week 07 – Linked Lists and String ADT

This week we continue our exploration of linked data structures with an emphasis on using linked lists for simple ADTs:

- a **Bag** class template (from the homework)
- a **character string** implementation (the lab)

Both assignments require careful pointer management and dynamic memory handling.  Remember that linked‑list structures have no fixed capacity but do require explicit node creation/destruction.

## Topics Covered

* Linked-list fundamentals (nodes, head pointers, traversal)
* Dynamic memory allocation and pointer management (Unit 4 coverage)
  * `new` / `delete`, constructors/destructors, avoiding leaks
  * Rule of three: copy ctor, assignment operator, destructor for classes owning heap data
* Implementing ADT operations using chained nodes
  * length, equality, add/remove, contains, toVector
* Linked stacks, queues, and lists (Unit 6 coverage)
  * Contrast with array-based parallels; FIFO vs LIFO behavior
  * Practical motivations for choosing linked structures
* Differences between array‑based and linked‑list implementations (capacity vs. overhead)
* Testing strategies with both positive and negative cases

## Deliverables

1. **Lab 07 – Linked String ADT** (see `lab07.md`)
   - Build a `LinkedString` class where each node holds one `char`.
   - Provide constructors, accessors, mutators, `length()`, `equals()`, etc.
   - Write a test program and submit a zipped archive of source files.

2. **Homework 05 – Linked-List Bag Template** (see `hw05.md`)
   - Complete a generic `LinkedBag` class with all required methods.
   - Test using `std::string` objects and demonstrate correct behavior.
   - Package the template and tester into an archive for submission.

> **Bonus lab activity:** The `dungeongame` project already integrates both ADTs.  Launch the game and select menu option **21** to try the linked-string lab and option **22** for a linked-bag demo.  These options use the same classes you implement for Lab 07 and HW 05, so you can interactively experiment with your code.

---

> **Reminder:**  Work incrementally and run your tests often; using tools such as `valgrind` (on macOS use `leaks`) will help catch memory issues early.
