#pragma once

#include <string>
#include <cstddef>
#include "LinkedList.h"

// Inventory ADT notes (for Week 03 - Templates & Linked Lists):
// - This ADT now uses our custom LinkedList template class instead of a raw array
// - Demonstrates how templates enable generic data structures that can work with any type
// - LinkedList provides the same interface but with different performance characteristics
// - Students learn how to adapt existing code to use template-based containers

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
    // Now using our template LinkedList instead of raw array
    LinkedList<Item> items;
public:
    Inventory() = default;

    void add(const Item& item) { items.append(item); }
    void insertAt(size_t idx, const Item& item) { items.insertAt(idx, item); }
    Item removeAt(size_t idx) { 
        Item removed = items.get(idx);
        items.removeAt(idx);
        return removed;
    }
    size_t size() const { return items.size(); }
    bool isEmpty() const { return items.isEmpty(); }

    // Provide access to the underlying linked list for iteration
    const LinkedList<Item>& getItems() const { return items; }
    LinkedList<Item>& getItems() { return items; }

    // Indexing operators for convenience
    Item& operator[](size_t idx) { return items.get(idx); }
    const Item& operator[](size_t idx) const { return items.get(idx); }
};

} // namespace dungeongame
