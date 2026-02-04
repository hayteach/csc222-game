#pragma once

#include <string>
#include <cstddef>

// Inventory ADT notes (for Week 02 - ADTs & Pointers):
// - ADT perspective: this header declares the *interface* for an Inventory ADT
//   (operations such as add/remove/size) while the implementation details
//   (memory layout, growth policy) live in the .cpp file. This separation
//   is a core part of data abstraction: users of `Inventory` program to the
//   interface and should not rely on the implementation details.
// - Pointer practice: `rawData()` returns a pointer to the owned element
//   storage allowing students to practice pointer arithmetic and traversal.
//   When using raw pointers, discuss safety (bounds checking, lifetime, and
//   ownership) and prefer encapsulation for higher-level code.
// - Implementation trade-offs: this ADT exposes a simple interface so that
//   different implementations (library-provided containers or student-built
//   alternatives) can be swapped to explore contiguous vs non-contiguous
//   storage strategies (conceptually discussed in lecture).

namespace dungeongame {

    /*
    Simple Item struct for inventory contents.
     A struct is a class with different default access
    In C++, struct and class are almost the same. The main differences are:

    Default member access
        struct: members are public by default
        class: members are private by default
    Default inheritance access

        struct: inheritance is public by default
        class: inheritance is private by default

    When should you use struct vs class?
    A common C++ convention:
        ✅ Use struct when…

        It’s mainly a simple data container
        You want members to be public by default
        Example: “plain old data” types like Point, Color, Settings

        ✅ Use class when…

        You want encapsulation and invariants
        You want members private by default
        Example: BankAccount that must prevent invalid balances
    */ 
struct Item {
    std::string name;
    int value;
    Item(const std::string& n = "", int v = 0) : name(n), value(v) {}
};

class Inventory {
private:
    // defines a variable as a pointer and is used to dereference a pointer to access
    // or modify the value stored at that address.
    Item* data;
    size_t sz;
    size_t cap;
    void resize(size_t newCap);
public:
    Inventory(size_t initial = 4);
    // destructor
    ~Inventory();
    Inventory(const Inventory&) = delete;
    //
    Inventory& operator=(const Inventory&) = delete;

    void add(const Item& item);
    Item removeAt(size_t idx);
    size_t size() const { return sz; }
    size_t capacity() const { return cap; }

    // Expose raw data pointer for pointer arithmetic practice
    Item* rawData() { return data; }
    const Item* rawData() const { return data; }
    // Indexing operators for convenience
    // provides access to elements in the inventory by index
    Item& operator[](size_t idx);
    const Item& operator[](size_t idx) const;
};

} // namespace dungeongame
