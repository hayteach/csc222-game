// test_sorting.cpp — Week 08: Sorting & Searching in the Dungeon Game
//
// Big-O summary for methods exercised here:
//   Inventory::sortByValue()        — O(n²)    bubble sort, two nested loops
//   Inventory::sortByName()         — O(n²)    bubble sort, two nested loops
//   Inventory::findByName()         — O(n)     single linear scan
//   Inventory::binarySearchByName() — O(log n) binary search (requires sorted input)
//   NPCGroup::sortByHealth()        — O(n²)    selection sort
//   NPCGroup::sortByAttack()        — O(n²)    selection sort

#include <iostream>
#include <cassert>
#include <chrono>
#include "Inventory.h"
#include "NPCGroup.h"

using namespace dungeongame;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

void printInventory(const Inventory& inv, const std::string& label) {
    std::cout << label << " (size=" << inv.size() << "):\n";
    for (size_t i = 0; i < inv.size(); i++) {
        std::cout << "  [" << i << "] " << inv[i].name
                  << "  (value=" << inv[i].value << ")\n";
    }
}

// Linear search with comparison counter (works on unsorted inventory)
int linearSearch(const Inventory& inv, const std::string& target, int& comparisons) {
    comparisons = 0;
    for (size_t i = 0; i < inv.size(); i++) {
        comparisons++;
        if (inv[i].name == target) return static_cast<int>(i);
    }
    return -1;
}

// Binary search with comparison counter (inventory must be sorted by name)
int binarySearch(const Inventory& inv, const std::string& target, int& comparisons) {
    comparisons = 0;
    int low = 0, high = static_cast<int>(inv.size()) - 1;
    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;
        if (inv[static_cast<size_t>(mid)].name == target)    return mid;
        if (inv[static_cast<size_t>(mid)].name <  target)    low  = mid + 1;
        else                                                  high = mid - 1;
    }
    return -1;
}

// Build a standard 8-item inventory in unsorted order
Inventory buildInventory() {
    Inventory inv;
    inv.add(Item("Torch",   10));
    inv.add(Item("Potion",  25));
    inv.add(Item("Shield",  40));
    inv.add(Item("Elixir",  60));
    inv.add(Item("Sword",   50));
    inv.add(Item("Axe",     45));
    inv.add(Item("Bow",     35));
    inv.add(Item("Dagger",  20));
    return inv;
}

// ---------------------------------------------------------------------------
// Test 1 — sortByValue (bubble sort, ascending)
// ---------------------------------------------------------------------------
void test_sortByValue() {
    std::cout << "--- Test 1: sortByValue (bubble sort) ---\n";
    Inventory inv = buildInventory();
    printInventory(inv, "Before");

    inv.sortByValue();
    printInventory(inv, "After sortByValue");

    for (size_t i = 0; i + 1 < inv.size(); i++) {
        assert(inv[i].value <= inv[i + 1].value &&
               "sortByValue: items are not in ascending order!");
    }
    std::cout << "sortByValue: PASSED\n\n";
}

// ---------------------------------------------------------------------------
// Test 2 — sortByName (bubble sort, lexicographic ascending)
// ---------------------------------------------------------------------------
void test_sortByName() {
    std::cout << "--- Test 2: sortByName (bubble sort) ---\n";
    Inventory inv = buildInventory();
    inv.sortByName();
    printInventory(inv, "After sortByName");

    for (size_t i = 0; i + 1 < inv.size(); i++) {
        assert(inv[i].name <= inv[i + 1].name &&
               "sortByName: items are not in alphabetical order!");
    }
    std::cout << "sortByName: PASSED\n\n";
}

// ---------------------------------------------------------------------------
// Test 3 — linear search vs. binary search: comparison count
// ---------------------------------------------------------------------------
void test_searchComparisons() {
    std::cout << "--- Test 3: Linear vs Binary search comparison counts ---\n";
    Inventory inv = buildInventory();
    inv.sortByName(); // binary search requires sorted input

    int linCmp = 0, binCmp = 0;
    int linIdx = linearSearch(inv, "Potion", linCmp);
    int binIdx = binarySearch(inv, "Potion", binCmp);

    std::cout << "Searching for 'Potion' in " << inv.size() << " items:\n";
    std::cout << "  Linear search: found at index " << linIdx
              << ", comparisons = " << linCmp << "\n";
    std::cout << "  Binary search: found at index " << binIdx
              << ", comparisons = " << binCmp << "\n";

    assert(linIdx == binIdx &&
           "Linear and binary search must agree on the result index!");
    assert(linIdx != -1 && "Potion should be found in inventory!");
    assert(binCmp <= linCmp &&
           "Binary search should use no more comparisons than linear!");
    std::cout << "Search comparison test: PASSED\n\n";
}

// ---------------------------------------------------------------------------
// Test 4 — findByName & binarySearchByName for missing item
// ---------------------------------------------------------------------------
void test_searchMissing() {
    std::cout << "--- Test 4: Search for item not in inventory ---\n";
    Inventory inv = buildInventory();
    inv.sortByName();

    int linCmp = 0, binCmp = 0;
    int linIdx = linearSearch(inv, "Wand", linCmp);
    int binIdx = binarySearch(inv, "Wand", binCmp);

    std::cout << "  Linear: index=" << linIdx << ", comparisons=" << linCmp << "\n";
    std::cout << "  Binary: index=" << binIdx << ", comparisons=" << binCmp << "\n";

    assert(linIdx == -1 && "Linear: missing item should return -1!");
    assert(binIdx == -1 && "Binary: missing item should return -1!");
    std::cout << "Missing item test: PASSED\n\n";
}

// ---------------------------------------------------------------------------
// Test 5 — NPCGroup::sortByHealth (selection sort)
// ---------------------------------------------------------------------------
void test_sortNPCsByHealth() {
    std::cout << "--- Test 5: NPCGroup::sortByHealth (selection sort) ---\n";

    NPC goblin("Goblin",  15, 3, 0, 10, 2);
    NPC troll ("Troll",   40, 7, 2, 30, 8);
    NPC rat   ("Rat",      5, 1, 0,  5, 1);
    NPC orc   ("Orc",     25, 5, 1, 20, 5);

    NPCGroup group;
    group.add(&troll);
    group.add(&rat);
    group.add(&orc);
    group.add(&goblin);

    std::cout << "Before sortByHealth:\n";
    for (size_t i = 0; i < group.size(); i++) {
        std::cout << "  [" << i << "] " << group[i]->getName()
                  << "  hp=" << group[i]->getHealth() << "\n";
    }

    group.sortByHealth();

    std::cout << "After sortByHealth (ascending):\n";
    for (size_t i = 0; i < group.size(); i++) {
        std::cout << "  [" << i << "] " << group[i]->getName()
                  << "  hp=" << group[i]->getHealth() << "\n";
    }

    for (size_t i = 0; i + 1 < group.size(); i++) {
        assert(group[i]->getHealth() <= group[i + 1]->getHealth() &&
               "sortByHealth: NPCs are not in ascending health order!");
    }
    // Weakest enemy is now always at index 0 — O(1) lookup
    assert(group[0]->getName() == "Rat" &&
           "sortByHealth: weakest NPC (Rat) should be at index 0!");
    std::cout << "sortByHealth: PASSED  (weakest enemy is now at index 0 in O(1))\n\n";
}

// ---------------------------------------------------------------------------
// Test 6 — NPCGroup::sortByAttack (selection sort, descending)
// ---------------------------------------------------------------------------
void test_sortNPCsByAttack() {
    std::cout << "--- Test 6: NPCGroup::sortByAttack (selection sort, descending) ---\n";

    NPC goblin("Goblin",  15, 3, 0, 10, 2);
    NPC troll ("Troll",   40, 7, 2, 30, 8);
    NPC rat   ("Rat",      5, 1, 0,  5, 1);
    NPC orc   ("Orc",     25, 5, 1, 20, 5);

    NPCGroup group;
    group.add(&goblin);
    group.add(&rat);
    group.add(&troll);
    group.add(&orc);

    group.sortByAttack();

    std::cout << "After sortByAttack (descending):\n";
    for (size_t i = 0; i < group.size(); i++) {
        std::cout << "  [" << i << "] " << group[i]->getName()
                  << "  atk=" << group[i]->getAttackPower() << "\n";
    }

    for (size_t i = 0; i + 1 < group.size(); i++) {
        assert(group[i]->getAttackPower() >= group[i + 1]->getAttackPower() &&
               "sortByAttack: NPCs are not in descending attack order!");
    }
    assert(group[0]->getName() == "Troll" &&
           "sortByAttack: strongest NPC (Troll) should be at index 0!");
    std::cout << "sortByAttack: PASSED\n\n";
}

// ---------------------------------------------------------------------------
// Stretch — benchmark sortByValue on increasingly large inputs
// Shows the O(n²) signature: doubling n roughly quadruples elapsed time
// ---------------------------------------------------------------------------
void benchmark_sortByValue() {
    std::cout << "--- Stretch: O(n²) benchmark for sortByValue ---\n";
    std::cout << "  (Worst case: items added in reverse order)\n";

    for (int n : {50, 100, 200, 400}) {
        Inventory inv;
        for (int i = n; i > 0; i--)
            inv.add(Item("Item" + std::to_string(i), i));

        auto t0 = std::chrono::high_resolution_clock::now();
        inv.sortByValue();
        auto t1 = std::chrono::high_resolution_clock::now();

        auto us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        std::cout << "  n=" << n << "  time: " << us << " µs\n";
    }
    std::cout << "  If time roughly quadruples as n doubles, that confirms O(n²).\n\n";
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------
int main() {
    std::cout << "=== Week 08: Sorting & Searching Tests ===\n\n";

    test_sortByValue();
    test_sortByName();
    test_searchComparisons();
    test_searchMissing();
    test_sortNPCsByHealth();
    test_sortNPCsByAttack();
    benchmark_sortByValue();

    std::cout << "=== All sorting/searching tests passed! ===\n";
    return 0;
}
