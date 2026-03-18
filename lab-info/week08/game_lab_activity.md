# Game Lab Activity — Algorithm Efficiency in the Dungeon Game

## Overview

This week you'll connect Big-O analysis to code you've already written. The dungeon game has several data structures — `Inventory` (backed by `LinkedList<Item>`), `NPCGroup` (backed by `std::vector<NPC*>`), and `Grimoire` (backed by `LinkedBag<Spell>`) — and each one already performs operations whose complexity we can classify and improve.

By the end of this lab you will have:
- Annotated existing game code with Big-O labels
- Implemented bubble sort on `Inventory`
- Compared linear search vs. binary search on a sorted inventory
- Added sorting to `NPCGroup` by NPC health
- Written a test program that counts and prints comparison counts
- (Optional) Benchmarked your sorts with different input sizes using `<chrono>`

---

## What You Already Have

| Class | Backing Container | Current Search | Current Sort |
|:---|:---|:---|:---|
| `Inventory` | `LinkedList<Item>` | O(n) linear | None |
| `NPCGroup` | `std::vector<NPC*>` | O(n) linear | None |
| `Grimoire` | `LinkedBag<Spell>` | O(n) via `contains()` | None |

---

## Step 1 — Big-O Audit of Existing Code (No Coding Required)

Open `dungeongame/include/dungeongame/Inventory.h` and `NPCGroup.h`. For each method listed below, write its Big-O complexity in the blanks and be prepared to explain your reasoning in class.

**`Inventory` methods:**

| Method | Big-O | Why? |
|:---|:---:|:---|
| `add(item)` | _____ | `LinkedList::append` traverses to the tail |
| `removeAt(idx)` | _____ | `LinkedList::removeAt` traverses to index |
| `operator[](idx)` | _____ | `LinkedList::get` traverses to index |
| `size()` | _____ | returns a stored counter |
| `isEmpty()` | _____ | checks if counter is zero |

> **Expected answers:** append = O(n), removeAt = O(n), operator[] = O(n), size = O(1), isEmpty = O(1).

**`NPCGroup` methods:**

| Method | Big-O | Why? |
|:---|:---:|:---|
| `add(npc)` | _____ | `vector::push_back` amortized |
| `operator[](idx)` | _____ | `vector` direct index |
| `size()` | _____ | `vector::size()` returns stored value |

> **Expected answers:** add = O(1) amortized, operator[] = O(1), size = O(1).

**Discussion:** Why does `vector` beat `LinkedList` on random access? What would you have to give up if you replaced the vector with a linked list in `NPCGroup`?

---

## Step 2 — Add `sortByValue()` to `Inventory` (Bubble Sort)

Bubble sort is the simplest O(n²) sort to implement. It repeatedly steps through the list comparing adjacent elements and swapping them if they're in the wrong order.

### 2a — Understand the algorithm visually first

Open https://visualgo.net/en, choose **Sorting → Bubble Sort**, and step through a small example. Notice that after each full pass the *largest unsorted element* has "bubbled" to its final position.

### 2b — Add the method declaration to `Inventory.h`

Open `dungeongame/include/dungeongame/Inventory.h` and add the following public method declaration after `isEmpty()`:

```cpp
// Sort items in ascending order by value — O(n²) bubble sort
void sortByValue();

// Linear search by name — returns index or -1 if not found — O(n)
int findByName(const std::string& name) const;

// Binary search by name on an already-sorted inventory — O(log n)
// Requires the inventory to be sorted by name first (sortByName)
int binarySearchByName(const std::string& name) const;

// Sort items in ascending order by name — O(n²) bubble sort
void sortByName();
```

### 2c — Implement `sortByValue()` and `sortByName()` in `Inventory.cpp`

Open `dungeongame/src/Inventory.cpp`. Add the following implementations:

```cpp
#include "Inventory.h"
#include <algorithm>  // for std::swap

namespace dungeongame {

void Inventory::sortByValue() {
    size_t n = items.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (items.get(j).value > items.get(j + 1).value) {
                // swap the two items
                Item tmp = items.get(j);
                items.get(j) = items.get(j + 1);
                items.get(j + 1) = tmp;
            }
        }
    }
}

void Inventory::sortByName() {
    size_t n = items.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (items.get(j).name > items.get(j + 1).name) {
                Item tmp = items.get(j);
                items.get(j) = items.get(j + 1);
                items.get(j + 1) = tmp;
            }
        }
    }
}

int Inventory::findByName(const std::string& name) const {
    for (size_t i = 0; i < items.size(); i++) {
        if (items.get(i).name == name) return static_cast<int>(i);
    }
    return -1;
}

int Inventory::binarySearchByName(const std::string& name) const {
    int low = 0;
    int high = static_cast<int>(items.size()) - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        const std::string& midName = items.get(mid).name;
        if (midName == name)  return mid;
        else if (midName < name) low  = mid + 1;
        else                     high = mid - 1;
    }
    return -1;
}

} // namespace dungeongame
```

> **Why `get(j)` returns a reference:** `LinkedList::get()` returns `ItemType&`, so writing `items.get(j) = items.get(j+1)` actually modifies the node's stored value directly. Verify this in `LinkedList.h`.

### 2d — Build and confirm it compiles

```bash
cd dungeongame && make
```

No test output yet — that comes in Step 4.

---

## Step 3 — Linear Search vs. Binary Search Comparison

### 3a — Why binary search requires sorted data

Binary search eliminates half the search space each step by comparing the target to the middle element. This only works when elements are in order — if the list is unsorted, you can't know which half to discard.

```
Sorted inventory (by name): [Axe, Bow, Dagger, Elixir, Potion, Shield, Sword, Torch]

Binary search for "Potion":
  mid = index 3 ("Elixir") → "Potion" > "Elixir" → search right half
  mid = index 5 ("Shield") → "Potion" < "Shield" → search left half
  mid = index 4 ("Potion") → FOUND in 3 comparisons (vs. 5 for linear)
```

### 3b — Operation count demo

Write the following short snippet (you will put it in the test program in Step 4):

```cpp
// Count comparisons for linear search
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
        if (inv[mid].name == target)    return mid;
        else if (inv[mid].name < target) low  = mid + 1;
        else                             high = mid - 1;
    }
    return -1;
}
```

Run both on the same sorted inventory and print the comparison counts. For n=8 you should see linear≤8, binary≤4. For n=1,000 you'd expect linear≤1,000, binary≤10.

---

## Step 4 — Write `test_sorting.cpp`

Create a new test file at `dungeongame/tests/test_sorting.cpp`:

```cpp
// test_sorting.cpp — Week 08: Sorting & Searching in the Dungeon Game
// Big-O summary:
//   sortByValue()     — O(n²)  bubble sort, two nested loops
//   sortByName()      — O(n²)  bubble sort, two nested loops
//   findByName()      — O(n)   single linear scan
//   binarySearchByName() — O(log n) binary search (requires sorted input)

#include <iostream>
#include <cassert>
#include "Inventory.h"

using namespace dungeongame;

// Helper: print all items in the inventory
void printInventory(const Inventory& inv, const std::string& label) {
    std::cout << label << " (size=" << inv.size() << "):\n";
    for (size_t i = 0; i < inv.size(); i++) {
        std::cout << "  [" << i << "] " << inv[i].name
                  << " (value=" << inv[i].value << ")\n";
    }
}

// Linear search with comparison counter
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
        if (inv[mid].name == target)    return mid;
        else if (inv[mid].name < target) low  = mid + 1;
        else                             high = mid - 1;
    }
    return -1;
}

int main() {
    std::cout << "=== Week 08: Sorting & Searching Tests ===\n\n";

    // --- Test 1: sortByValue() ---
    std::cout << "--- Test 1: sortByValue (bubble sort) ---\n";
    Inventory inv;
    inv.add(Item("Torch",   10));
    inv.add(Item("Potion",  25));
    inv.add(Item("Shield",  40));
    inv.add(Item("Elixir",  60));
    inv.add(Item("Sword",   50));
    inv.add(Item("Axe",     45));
    inv.add(Item("Bow",     35));
    inv.add(Item("Dagger",  20));

    printInventory(inv, "Before sort");
    inv.sortByValue();
    printInventory(inv, "After sortByValue");

    // Verify ascending order by value
    for (size_t i = 0; i + 1 < inv.size(); i++) {
        assert(inv[i].value <= inv[i+1].value &&
               "sortByValue: items are not in ascending order!");
    }
    std::cout << "sortByValue: PASSED\n\n";

    // --- Test 2: sortByName() ---
    std::cout << "--- Test 2: sortByName (bubble sort) ---\n";
    inv.sortByName();
    printInventory(inv, "After sortByName");

    for (size_t i = 0; i + 1 < inv.size(); i++) {
        assert(inv[i].name <= inv[i+1].name &&
               "sortByName: items are not in alphabetical order!");
    }
    std::cout << "sortByName: PASSED\n\n";

    // --- Test 3: linear vs. binary search ---
    std::cout << "--- Test 3: Linear Search vs Binary Search ---\n";
    // Inventory is already sorted by name from Test 2
    int linCmp = 0, binCmp = 0;
    int linIdx = linearSearch(inv, "Potion", linCmp);
    int binIdx = binarySearch(inv, "Potion", binCmp);

    std::cout << "Searching for 'Potion' in " << inv.size() << " items:\n";
    std::cout << "  Linear search: found at index " << linIdx
              << ", comparisons = " << linCmp << "\n";
    std::cout << "  Binary search: found at index " << binIdx
              << ", comparisons = " << binCmp << "\n";

    assert(linIdx == binIdx && "Linear and binary search disagree on result!");
    assert(binCmp <= linCmp && "Binary search should use <= comparisons than linear!");
    std::cout << "Search comparison test: PASSED\n\n";

    // --- Test 4: search for missing item ---
    std::cout << "--- Test 4: Search for item not in inventory ---\n";
    int notFoundLinear = linearSearch(inv, "Wand", linCmp);
    int notFoundBinary = binarySearch(inv, "Wand", binCmp);
    std::cout << "  Linear: index=" << notFoundLinear << ", comparisons=" << linCmp << "\n";
    std::cout << "  Binary: index=" << notFoundBinary << ", comparisons=" << binCmp << "\n";
    assert(notFoundLinear == -1 && notFoundBinary == -1);
    std::cout << "Missing item test: PASSED\n\n";

    std::cout << "=== All sorting/searching tests passed! ===\n";
    return 0;
}
```

### 4a — Add to the build

Open `dungeongame/tests/run_tests.sh` and add the new test:

```bash
# Compile and run test_sorting
g++ -std=c++17 -I../include ../src/Inventory.cpp ../src/LinkedList.cpp \
    test_sorting.cpp -o test_sorting && ./test_sorting
```

> If your project uses a `Makefile` or `CMakeLists.txt`, add `test_sorting.cpp` the same way `combat_test.cpp` is included.

---

## Step 5 — Add Sorting to `NPCGroup`

Now apply the same process to enemies. Sorting enemies by health lets your combat code always fight the weakest enemy first, or allows you to quickly identify the most dangerous threat.

### 5a — Add sort methods to `NPCGroup.h`

Open `dungeongame/include/dungeongame/NPCGroup.h` and add the following public methods inside the class body:

```cpp
// Sort NPCs in ascending order by current health — O(n²) selection sort
void sortByHealth() {
    size_t n = npcs.size();
    for (size_t i = 0; i < n; i++) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < n; j++) {
            if (npcs[j]->getHealth() < npcs[minIdx]->getHealth())
                minIdx = j;
        }
        if (minIdx != i)
            std::swap(npcs[i], npcs[minIdx]);
    }
}

// Sort NPCs in descending order by attack power — O(n²) selection sort
void sortByAttack() {
    size_t n = npcs.size();
    for (size_t i = 0; i < n; i++) {
        size_t maxIdx = i;
        for (size_t j = i + 1; j < n; j++) {
            if (npcs[j]->getAttackPower() > npcs[maxIdx]->getAttackPower())
                maxIdx = j;
        }
        if (maxIdx != i)
            std::swap(npcs[i], npcs[maxIdx]);
    }
}
```

> **Algorithm used:** Selection sort — find the min/max of the unsorted portion and swap it into place. Same O(n²) as bubble sort but makes fewer *swaps* (useful when swapping is expensive).

### 5b — Use it in combat

In `Game.cpp` (or wherever enemies are spawned and the player fights), add a call before combat begins:

```cpp
// Always fight the weakest enemy first
enemyGroup.sortByHealth();
NPC* target = enemyGroup[0];
```

This transforms an O(n) "find weakest enemy" search on every turn into a O(1) lookup — but you pay the O(n²) sorting cost once up front. Discuss: is that trade-off worth it?

---

## Step 6 — Reflection: What Did You Improve?

Fill in this table after completing the steps above. Keep it in a comment block at the top of `test_sorting.cpp`.

| Operation | Before (this lab) | After (this lab) | Change in Big-O? |
|:---|:---:|:---:|:---:|
| Find item by name (Inventory) | O(n) | O(log n) (after sort) | Yes — if sorted |
| Sort inventory by value | N/A | O(n²) | New feature |
| Find weakest enemy (NPCGroup) | O(n) each turn | O(1) (after sort) | Yes — after O(n²) one-time cost |
| Sort enemies by health | N/A | O(n²) | New feature |
| `inventory[idx]` random access | O(n) (LinkedList) | O(n) (LinkedList) | No change |
| `enemyGroup[idx]` random access | O(1) (vector) | O(1) (vector) | No change |

**Discussion question:** The last row shows that `Inventory` is still O(n) for random access because it's backed by a `LinkedList`. If you switched the backing container to `std::vector<Item>`, access would be O(1) and the sorting algorithms would also run faster (fewer cache misses). What would you lose by making that switch?

---

## Step 7 (Optional Stretch) — Benchmark with `<chrono>`

Add timing to `test_sorting.cpp` to measure real elapsed time for sorting different sizes of inventory:

```cpp
#include <chrono>

void benchmarkSort(int n) {
    Inventory inv;
    // Fill with n items in reverse order (worst case for bubble sort)
    for (int i = n; i > 0; i--) {
        inv.add(Item("Item" + std::to_string(i), i));
    }

    auto start = std::chrono::high_resolution_clock::now();
    inv.sortByValue();
    auto end   = std::chrono::high_resolution_clock::now();

    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "n=" << n << "  sortByValue time: " << us << " µs\n";
}

// Call from main:
// benchmarkSort(100);
// benchmarkSort(500);
// benchmarkSort(1000);
// benchmarkSort(5000);
```

Record your results in a table. Does the time roughly quadruple when you double n? (It should — that's the signature of O(n²).)

| n | Time (µs) | Ratio vs previous n |
|:---:|:---:|:---:|
| 100 | | — |
| 200 | | |
| 400 | | |
| 800 | | |

---

## Connecting to the Game (Summary)

| Where | What you added | Complexity gained |
|:---|:---|:---|
| `Inventory` | `sortByValue()`, `sortByName()` — bubble sort | O(n²) sort enables O(log n) binary search |
| `Inventory` | `findByName()` — linear search | O(n) |
| `Inventory` | `binarySearchByName()` — requires sorted order | O(log n) |
| `NPCGroup` | `sortByHealth()`, `sortByAttack()` — selection sort | O(n²) one-time sort → O(1) weakest-enemy lookup |

---

## Submission Checklist

- [ ] Big-O audit table from Step 1 filled in (in your own words in a comment).
- [ ] `sortByValue()` and `sortByName()` implemented in `Inventory.cpp`.
- [ ] `findByName()` and `binarySearchByName()` implemented in `Inventory.cpp`.
- [ ] `sortByHealth()` and `sortByAttack()` added to `NPCGroup.h`.
- [ ] `test_sorting.cpp` created in `dungeongame/tests/`, all assertions pass.
- [ ] Project still builds and existing tests still pass (`make test` or `run_tests.sh`).
- [ ] (Stretch) Benchmark results table recorded.

> **Tip:** Run the sorting visualizer (https://visualgo.net/en) side-by-side while reading your own code. Watching the animated swap steps while tracing through your C++ code is one of the fastest ways to build intuition for why these algorithms have the complexity they do.
