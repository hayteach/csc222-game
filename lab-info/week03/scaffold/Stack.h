#pragma once

#include "../dungeongame/include/dungeongame/LinkedList.h"
#include <stdexcept>

// Week 03 Scaffold: Template-based Stack
// Demonstrates how to build higher-level data structures using templates

namespace scaffold {

template <typename T>
class Stack {
private:
    dungeongame::LinkedList<T> items;
public:
    // Constructor
    Stack() = default;

    // Push element onto stack
    void push(const T& item) {
        items.prepend(item); // Add to front for O(1) push/pop
    }

    // Pop element from stack
    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        T item = items.get(0);
        items.removeAt(0);
        return item;
    }

    // Peek at top element
    T& top() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return items.get(0);
    }

    const T& top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return items.get(0);
    }

    // Check if stack is empty
    bool isEmpty() const {
        return items.size() == 0;
    }

    // Get size
    size_t size() const {
        return items.size();
    }

    // Clear stack
    void clear() {
        items.clear();
    }
};

} // namespace scaffold</content>
<parameter name="filePath">/Users/heidiahders/Documents/MendocinoCollege/Class/2026/Spring/CSC222/game/lab-info/week03/scaffold/Stack.h