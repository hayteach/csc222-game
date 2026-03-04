# Week 06 Lesson — Pointers and References in C++

This week’s topic covers the foundations of pointers, references, and the memory model used by C++ programs.  After studying the material you should be comfortable manipulating memory addresses, accessing arrays through pointer arithmetic, and understanding the relationship between variable storage and pointer values.  The content is based on Saylor’s lesson for C++ (see https://learn.saylor.org/course/view.php?id=1307).

## Learning Outcomes

Upon successful completion of this unit, you will be able to:

1. **Distinguish data organization:**
   - articulate the difference between **scalars**, **vectors**, and **arrays**
   - show how scalars, vectors, and arrays are used to organize values according to a specific multi-dimensional arrangement

2. **Pointer fundamentals:**
   - explain how to declare a pointer variable
   - define the term **pointer variable**
   - relate the value of a pointer variable to the location of a variable's value in memory
   - explain how to get the memory location of a scalar value (using the address-of operator `&`)

3. **Memory and data ranges:**
   - demonstrate how the range of a numeric scalar type can be extended via compound declarations
   - explain why scalar types may not have the same numeric range from one compiler to another
   - contrast **contiguous** and **non-contiguous** memory

4. **Pointer arithmetic and access:**
   - show how pointer math is used to access specific elements of a vector or array existing in contiguous memory

## Key Concepts

- **Scalar:** A single value such as `int`, `double`, etc.
- **Vector:** A one-dimensional sequence of values, typically accessed via a pointer or index.
- **Array:** A contiguous block of memory containing multiple elements of the same type, with a fixed size.
- **Pointer Variable:** A variable whose value is the memory address of another variable.  Pointers have a type that indicates the type of object they point to (e.g., `int*`, `double*`).
- **Address-of Operator (`&`):** Returns the memory address of its operand.
- **Dereference Operator (`*`):** Accesses the value stored at the address held by a pointer.
- **Pointer Arithmetic:** Adding or subtracting integers from a pointer moves it by a number of elements (not bytes) depending on the pointed-to type.

## Suggested Exercises

- Write a small program that declares a few scalar variables and prints their addresses using `&`.
- Create an array, then use pointer arithmetic to iterate through the elements instead of array indexing.
- Experiment with declaring pointers to different types and observe how pointer arithmetic behaves.
- Compare the numeric limits of `int`, `long`, and `long long` on your compiler using `<limits>`.

## Additional Resources

- [Saylor C++ Course](https://learn.saylor.org/course/view.php?id=1307)
- C++ reference documentation for pointers and arrays

---

> This document serves as the lesson summary for the week focusing on pointers and references in C++. Use it alongside the lab assignment and class notes.