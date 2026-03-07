#include "LinkedString.h"
#include <stdexcept>

namespace dungeongame {

LinkedString::LinkedString() : head(nullptr) {}

LinkedString::LinkedString(const std::string& s) : head(nullptr) {
    for (char c : s) {
        // append each character (we'll insert at end)
        if (!head) {
            head = new Node(c);
        } else {
            Node* curr = head;
            while (curr->next) curr = curr->next;
            curr->next = new Node(c);
        }
    }
}

LinkedString::LinkedString(const LinkedString& other) : head(nullptr) {
    copyFrom(other);
}

LinkedString& LinkedString::operator=(const LinkedString& other) {
    if (this != &other) {
        // free existing
        Node* curr = head;
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        copyFrom(other);
    }
    return *this;
}

LinkedString::~LinkedString() {
    Node* curr = head;
    while (curr) {
        Node* tmp = curr;
        curr = curr->next;
        delete tmp;
    }
}

int LinkedString::length() const {
    int count = 0;
    Node* curr = head;
    while (curr) {
        ++count;
        curr = curr->next;
    }
    return count;
}

bool LinkedString::equals(const LinkedString& other) const {
    Node* a = head;
    Node* b = other.head;
    while (a && b) {
        if (a->ch != b->ch) return false;
        a = a->next;
        b = b->next;
    }
    return a == nullptr && b == nullptr;
}

char LinkedString::get(int index) const {
    if (index < 0) throw std::out_of_range("Index negative");
    Node* curr = head;
    int i = 0;
    while (curr && i < index) {
        curr = curr->next;
        ++i;
    }
    if (!curr) throw std::out_of_range("Index out of range");
    return curr->ch;
}

void LinkedString::set(int index, char c) {
    if (index < 0) throw std::out_of_range("Index negative");
    Node* curr = head;
    int i = 0;
    while (curr && i < index) {
        curr = curr->next;
        ++i;
    }
    if (!curr) throw std::out_of_range("Index out of range");
    curr->ch = c;
}

std::string LinkedString::toStdString() const {
    std::string s;
    Node* curr = head;
    while (curr) {
        s.push_back(curr->ch);
        curr = curr->next;
    }
    return s;
}

} // namespace dungeongame
