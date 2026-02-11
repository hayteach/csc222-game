/* File: LinkedList.h
   Name: CSC 222 Students
   Date: 02/09/2026
   Last Edit: 02/09/2026
   Course: CSC 222 - Programming and Algorithms II
   Desc: Template class for a singly linked list demonstration.
         Shows how to create generic data structures in C++.
*/

#pragma once

#include <iostream>
#include <stdexcept>

namespace dungeongame {

// Node structure for the linked list
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(const T& d) : data(d), next(nullptr) {}
};

// Template class for a singly linked list
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    size_t listSize;

public:
    // Constructor
    LinkedList() : head(nullptr), listSize(0) {}

    // Destructor
    ~LinkedList() {
        clear();
    }

    // Copy constructor (deep copy)
    LinkedList(const LinkedList& other) : head(nullptr), listSize(0) {
        Node<T>* current = other.head;
        while (current) {
            append(current->data);
            current = current->next;
        }
    }

    // Assignment operator
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node<T>* current = other.head;
            while (current) {
                append(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Add element to the end
    void append(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        listSize++;
    }

    // Add element to the beginning
    void prepend(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head;
        head = newNode;
        listSize++;
    }

    // Remove element at index
    void removeAt(size_t index) {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        } else {
            Node<T>* current = head;
            for (size_t i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            Node<T>* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
        listSize--;
    }

    // Get element at index
    T& get(size_t index) {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    const T& get(size_t index) const {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    // Get size
    size_t size() const {
        return listSize;
    }

    // Check if empty
    bool isEmpty() const {
        return listSize == 0;
    }

    // Clear the list
    void clear() {
        Node<T>* current = head;
        while (current) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        listSize = 0;
    }

    // Print the list
    void print() const {
        Node<T>* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // Iterator class for range-based for loops
    class Iterator {
    private:
        Node<T>* current;
    public:
        Iterator(Node<T>* node) : current(node) {}
        T& operator*() { return current->data; }
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

} // namespace dungeongame