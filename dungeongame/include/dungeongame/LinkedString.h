#pragma once

#include <string>

namespace dungeongame {

// Simple linked-list based string ADT for lab07.
class LinkedString {
private:
    struct Node {
        char ch;
        Node* next;
        Node(char c) : ch(c), next(nullptr) {}
    };

    Node* head;

    // helper to copy nodes from another list
    void copyFrom(const LinkedString& other) {
        head = nullptr;
        if (!other.head) return;
        head = new Node(other.head->ch);
        Node* currNew = head;
        Node* currOld = other.head->next;
        while (currOld) {
            currNew->next = new Node(currOld->ch);
            currNew = currNew->next;
            currOld = currOld->next;
        }
    }

public:
    // constructors / destructor / assignment
    LinkedString();
    LinkedString(const std::string& s);
    LinkedString(const LinkedString& other);
    LinkedString& operator=(const LinkedString& other);
    ~LinkedString();

    int length() const;
    bool equals(const LinkedString& other) const;

    char get(int index) const;    // throw if out of range
    void set(int index, char c);  // throw if out of range

    std::string toStdString() const;
};

} // namespace dungeongame
