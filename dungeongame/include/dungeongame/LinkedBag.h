#pragma once

#include <vector>
#include <stdexcept>

namespace dungeongame {

// Template class for a simple linked-list bag (no order guaranteed)
// used in Homework 05 and as a game demo.

template<typename ItemType>
class LinkedBag {
private:
    struct Node {
        ItemType data;
        Node* next;
        Node(const ItemType& d) : data(d), next(nullptr) {}
    };

    Node* headPtr;
    int itemCount;

public:
    LinkedBag() : headPtr(nullptr), itemCount(0) {}
    LinkedBag(const LinkedBag& other) : headPtr(nullptr), itemCount(0) {
        Node* curr = other.headPtr;
        while (curr) {
            add(curr->data);
            curr = curr->next;
        }
    }
    ~LinkedBag() { clear(); }
    LinkedBag& operator=(const LinkedBag& other) {
        if (this != &other) {
            clear();
            Node* curr = other.headPtr;
            while (curr) {
                add(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    int getCurrentSize() const { return itemCount; }
    bool isEmpty() const { return itemCount == 0; }
    bool add(const ItemType& newEntry) {
        Node* newNode = new Node(newEntry);
        newNode->next = headPtr;
        headPtr = newNode;
        itemCount++;
        return true;
    }
    bool remove(const ItemType& anEntry) {
        Node* prev = nullptr;
        Node* curr = headPtr;
        while (curr) {
            if (curr->data == anEntry) {
                if (prev) prev->next = curr->next;
                else headPtr = curr->next;
                delete curr;
                itemCount--;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }
    void clear() {
        Node* curr = headPtr;
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        headPtr = nullptr;
        itemCount = 0;
    }
    bool contains(const ItemType& anEntry) const {
        Node* curr = headPtr;
        while (curr) {
            if (curr->data == anEntry) return true;
            curr = curr->next;
        }
        return false;
    }
    std::vector<ItemType> toVector() const {
        std::vector<ItemType> result;
        Node* curr = headPtr;
        while (curr) {
            result.push_back(curr->data);
            curr = curr->next;
        }
        return result;
    }
};

} // namespace dungeongame
