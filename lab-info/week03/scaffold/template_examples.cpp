#include <iostream>
#include <string>
#include "../dungeongame/include/dungeongame/LinkedList.h"

// Week 03 Scaffold: Template Examples
// This file demonstrates basic template syntax and usage

using namespace std;
using namespace dungeongame;

// Example 1: Simple template function
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Example 2: Template class with multiple types
template <typename T, typename U>
class Pair {
private:
    T first;
    U second;
public:
    Pair(T f, U s) : first(f), second(s) {}
    T getFirst() const { return first; }
    U getSecond() const { return second; }
    void print() const {
        cout << "(" << first << ", " << second << ")" << endl;
    }
};

// Example 3: Template specialization
template <typename T>
class Container {
public:
    void printType() { cout << "Generic type" << endl; }
};

// Specialization for int
template <>
class Container<int> {
public:
    void printType() { cout << "Integer type" << endl; }
};

// Example 4: Using templates with LinkedList
void demonstrateLinkedListTemplates() {
    cout << "\n=== LinkedList Template Usage ===" << endl;

    // LinkedList with different types
    LinkedList<int> numbers;
    numbers.append(1);
    numbers.append(2);
    numbers.append(3);

    cout << "Integer list: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    LinkedList<string> words;
    words.append("Hello");
    words.append("Template");
    words.append("World");

    cout << "String list: ";
    for (const string& word : words) {
        cout << word << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Template Examples ===" << endl;

    // Template function
    cout << "max(5, 10) = " << maximum(5, 10) << endl;
    cout << "max(3.14, 2.71) = " << maximum(3.14, 2.71) << endl;
    cout << "max('a', 'z') = " << maximum('a', 'z') << endl;

    // Template class
    Pair<int, double> p1(42, 3.14159);
    Pair<string, int> p2("Answer", 42);

    cout << "\nPairs:" << endl;
    p1.print();
    p2.print();

    // Template specialization
    Container<double> c1;
    Container<int> c2;
    c1.printType(); // Generic type
    c2.printType(); // Integer type

    // LinkedList templates
    demonstrateLinkedListTemplates();

    cout << "\nTemplates enable generic programming!" << endl;
    return 0;
}</content>
<parameter name="filePath">/Users/heidiahders/Documents/MendocinoCollege/Class/2026/Spring/CSC222/game/lab-info/week03/scaffold/template_examples.cpp