# Lab 07 – Linked String ADT

**Objective:**
Implement an Abstract Data Type (ADT) for a character string using a linked chain of characters.  Each character is stored in a node of a linked list rather than using a contiguous array.

---

## Requirements

1. **Data structure** – a singly linked list where every node contains one `char` and a pointer to the next node.
2. **Constructors / Destructor / Assignment**
   - Default constructor (empty string)
   - Copy constructor
   - Destructor to free all nodes
   - Overloaded assignment operator
3. **Accessors & Mutators**
   - `char get(int index) const` (or similar) to read a character
   - `void set(int index, char c)` to modify a character
   - (other helpers as needed)
4. **Additional operations**
   - `int length() const` – compute and return the number of characters in the list.
   - `bool equals(const LinkedString &other) const` – return `true` if this string contains the same sequence of characters as `other`.
5. **Testing**
   - Write a test program that builds several `LinkedString` objects and exercises every member function.  Check both positive and negative cases (e.g. comparing equal and unequal strings, empty strings, etc.).
   - Make sure your program compiles and runs without memory leaks.
6. **Submission**
   - Package all necessary source files and the test program into a single `.zip`, `.7z` or `.rar` archive.
   - Submit the archive for grading.

---

> **Note:**  This lab reinforces your understanding of linked lists by applying them to a simple string ADT.  Pay attention to memory management and edge cases such as empty strings or out‑of‑bounds indices.
