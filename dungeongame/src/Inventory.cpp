#include "Inventory.h"

// Implementation notes (for Week 03 - Templates & Linked Lists):
// - Inventory is now implemented as a thin wrapper around LinkedList<Item>
// - Core inline methods live in the header; sorting/searching live here.

// Week 08 — Sorting & Searching implementations
// Big-O summary:
//   sortByValue()        — O(n²)  bubble sort, two nested loops
//   sortByName()         — O(n²)  bubble sort, two nested loops
//   findByName()         — O(n)   single linear scan
//   binarySearchByName() — O(log n) halves the search space each step
//                          (requires inventory to be sorted by name first)

namespace dungeongame {

// ---------------------------------------------------------------------------
// sortByValue — bubble sort ascending by Item::value
// After each outer pass the largest remaining item has "bubbled" to its
// final position, so the inner loop shrinks by one each time.
// Time complexity: O(n²)  Space complexity: O(1)
// ---------------------------------------------------------------------------
void Inventory::sortByValue() {
    size_t n = items.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (items.get(j).value > items.get(j + 1).value) {
                // LinkedList::get() returns T& so we can swap in-place
                Item tmp       = items.get(j);
                items.get(j)   = items.get(j + 1);
                items.get(j + 1) = tmp;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// sortByName — bubble sort ascending by Item::name (lexicographic)
// Identical structure to sortByValue; only the comparison key differs.
// Time complexity: O(n²)  Space complexity: O(1)
// ---------------------------------------------------------------------------
void Inventory::sortByName() {
    size_t n = items.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (items.get(j).name > items.get(j + 1).name) {
                Item tmp         = items.get(j);
                items.get(j)     = items.get(j + 1);
                items.get(j + 1) = tmp;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// insertionSortByName — insertion sort ascending by Item::name
// Builds a sorted prefix by inserting each element into its correct position.
// Time complexity: O(n²) worst-case, O(n) best-case (already sorted)
// Space complexity: O(1)
// ---------------------------------------------------------------------------
void Inventory::insertionSortByName() {
    int n = static_cast<int>(items.size());
    for (int i = 1; i < n; i++) {
        Item key = items.get(static_cast<size_t>(i));
        int j = i - 1;
        while (j >= 0 && items.get(static_cast<size_t>(j)).name > key.name) {
            items.get(static_cast<size_t>(j + 1)) = items.get(static_cast<size_t>(j));
            j--;
        }
        items.get(static_cast<size_t>(j + 1)) = key;
    }
}

// ---------------------------------------------------------------------------
// findByName — linear search
// Visits every element in order until a match is found.
// Returns the index of the first match, or -1 if not found.
// Time complexity: O(n)
// ---------------------------------------------------------------------------
int Inventory::findByName(const std::string& name) const {
    for (size_t i = 0; i < items.size(); i++) {
        if (items.get(i).name == name)
            return static_cast<int>(i);
    }
    return -1;
}

// ---------------------------------------------------------------------------
// binarySearchByName — binary search
// Requires the inventory to be sorted by name (call sortByName() first).
// Each iteration eliminates half the remaining candidates.
// Returns the index of the matching item, or -1 if not found.
// Time complexity: O(log n)
// ---------------------------------------------------------------------------
int Inventory::binarySearchByName(const std::string& name) const {
    int low  = 0;
    int high = static_cast<int>(items.size()) - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;   // avoids overflow vs. (low+high)/2
        const std::string& midName = items.get(static_cast<size_t>(mid)).name;
        if (midName == name)   return mid;
        if (midName < name)    low  = mid + 1;
        else                   high = mid - 1;
    }
    return -1;
}

} // namespace dungeongame
