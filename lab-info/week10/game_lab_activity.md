# Game Lab Activity — Searching & Sorting (Week 10)

## Overview
In this lab you will connect searching and sorting algorithms to the dungeon game code. The game already has collections such as `Inventory` (a linked list of `Item`s) and `NPCGroup` (a vector of `NPC*`). You will:

- Identify Big-O for key operations in the game code
- Compare linear vs. binary search (and why binary requires sorted data)
- Implement and/or exercise sorting algorithms (bubble + selection/insertion)
- Measure the number of comparisons made by each algorithm

> **Goal:** By the end of this lab, you should be able to look at a loop in the game code and explain its Big-O, and choose the right search/sort strategy for a given situation.

---

## Step 0 — Get the code ready (5 min)
1. Open the project in your IDE.
2. Build the game to ensure everything compiles:

```bash
cd dungeongame
make
```

3. Run the game to make sure the menu works:

```bash
./bin/dungeongame
```

> The game now loads inventory data automatically from `dungeongame/data/inventory.txt` (if the file exists).

### Loading data from a file (C++ example)
In C++ you can read a text file line-by-line using `std::ifstream`, then parse each line (for example by splitting on commas). The game uses this technique to load initial inventory items on startup. A simple pattern looks like:

```cpp
std::ifstream in("data/inventory.txt");
std::string line;
while (std::getline(in, line)) {
    if (line.empty() || line[0] == '#') continue;
    std::istringstream ss(line);
    std::string name; 
    std::string valueStr;
    std::getline(ss, name, ',');
    std::getline(ss, valueStr);
    int value = std::stoi(valueStr);
    // create an Item and add it to the inventory
}
```

4. You don’t need to play the full game — just confirm it starts.

---

## Step 1 — Big-O Audit (10 min)
Open the following files and annotate the complexity (Big-O) in the code comments (or on paper):

- `dungeongame/include/dungeongame/Inventory.h`
- `dungeongame/include/dungeongame/NPCGroup.h`

For each method below, write the Big-O notation and briefly explain why.

### Inventory methods (linked list)
- `add(item)`
- `removeAt(idx)`
- `operator[](idx)` (index operator)
- `size()`
- `isEmpty()`

### NPCGroup methods (vector)
- `add(npc)`
- `operator[](idx)`
- `size()`

> **Discussion:** Why is random access (`operator[]`) O(1) on `vector` but O(n) on `LinkedList`? What trade-offs does `vector` make to achieve that?

---

## Step 2 — Search: Linear vs. Binary (25 min)
The `Inventory` class already includes two search methods:
- `findByName()` — linear search (O(n))
- `binarySearchByName()` — binary search (O(log n))

### 2a — Understand the precondition for binary search
Binary search only works if the items are sorted by the search key (name). If the inventory is not sorted, binary search can return an incorrect result.

### 2b — Verify the implementations
Open:
- `dungeongame/src/Inventory.cpp`

Locate `findByName()` and `binarySearchByName()` and read the code. Notice:
- `findByName` checks each element in order until it finds a match.
- `binarySearchByName` repeatedly halves the search range based on the middle element.

### 2c — Count comparisons (make it visible)
Create a small helper in a test file (or in `main` for demonstration):

```cpp
int linearSearchCount(const Inventory& inv, const std::string& target, int& comparisons) {
    comparisons = 0;
    for (size_t i = 0; i < inv.size(); i++) {
        comparisons++;
        if (inv[i].name == target) return static_cast<int>(i);
    }
    return -1;
}

int binarySearchCount(const Inventory& inv, const std::string& target, int& comparisons) {
    comparisons = 0;
    int lo = 0;
    int hi = static_cast<int>(inv.size()) - 1;
    while (lo <= hi) {
        comparisons++;
        int mid = lo + (hi - lo) / 2;
        if (inv[mid].name == target) return mid;
        if (inv[mid].name < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
```

Run both searches on the same inventory and compare the number of comparisons. Try:
- A small inventory (8 items)
- A larger inventory (100+ items)

Observe how the comparison counts grow for linear vs. binary.

---

## Step 3 — Sorting (30 min)
The `Inventory` class already provides two sorting methods:
- `sortByValue()` — bubble sort by item value (O(n²))
- `sortByName()` — bubble sort by item name (O(n²))

### 3a — Visualize the algorithm
Open https://visualgo.net/en, select **Sorting → Bubble Sort**, and step through a small list.

### 3b — Examine the implementation
Open `dungeongame/src/Inventory.cpp` and locate `sortByValue()` and `sortByName()`. Notice the two nested loops and how the inner loop shrinks each pass.

### 3c — Try a different O(n²) sort (optional but recommended)
Pick one of the following and implement it in `Inventory`:
- **Selection sort** (good for few swaps)
- **Insertion sort** (fast when input is nearly sorted)

Example (selection sort by name):

```cpp
void Inventory::sortByNameSelection() {
    size_t n = items.size();
    for (size_t i = 0; i < n; i++) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < n; j++) {
            if (items.get(j).name < items.get(minIdx).name)
                minIdx = j;
        }
        if (minIdx != i)
            std::swap(items.get(i), items.get(minIdx));
    }
}
```

If you add a new sort method, add a corresponding method declaration to `Inventory.h`.

---

## Step 4 — Apply sorting + searching in the game (20 min)
This step connects the algorithms to a real “game task.”

### 4a — Sort the inventory and then search
A new menu option has been added to the game for this demo ("Sort/Search Demo"). When you run the game, choose that option (menu item 25) to execute the demo.

The demo will ask you to choose between **bubble sort** and **insertion sort** (both O(n²)) so you can observe their behavior without changing code.

In `dungeongame/src/Game.cpp`, locate the code behind this menu option and verify it.

### 4b — Compare bubble vs insertion sort side-by-side
A second menu option has been added for this demo: **menu item 26: Compare bubble vs insertion sort**.

This option runs both sorts on the same starting inventory and prints:
- the sorted item order for each algorithm
- the number of comparisons each sort made
- the elapsed time (microseconds) for each sort

#### What code was added (so you can follow along)
1. **`Game.h`**: a new method declaration:

```cpp
void runSortCompareDemo();
```

2. **`Game.cpp`**:
   - Added menu option `26` in `displayMenu()`
   - Added a `case 26:` in `processChoice()` to call `runSortCompareDemo()`
   - Implemented `runSortCompareDemo()` which:
     - Copies the current inventory into a local `Inventory` object
     - Runs bubble sort and insertion sort on separate copies
     - Prints comparisons + timing for each

Run the game and choose option **26** to see the side-by-side comparison.

1. Sorts the inventory by name
2. Displays the first few items
3. Searches for a specific name using both `findByName()` and `binarySearchByName()` and prints comparison counts (as in Step 2)

This can be a temporary demonstration for the lab.

### 4b — Optional: add a new menu option
Add a new menu option to the main menu (e.g., “23) Sort Inventory (demo)”). In `Game::displayMenu()` and `Game::processChoice()`, add a case that runs the demo code from 4a.

---

## Step 5 — Verify with a test program (20 min)
Create a test file `dungeongame/tests/test_sorting.cpp` that:

1. Builds an `Inventory` with at least 8 items in unsorted order
2. Prints the inventory
3. Calls `sortByValue()` and prints the inventory again
4. Calls `sortByName()` and prints the inventory again
5. Uses the comparison-count helper functions from Step 2 to compare `findByName()` vs `binarySearchByName()` (remember to sort first)

### Example output expectations
- Unsorted list prints in original insertion order
- After `sortByValue()`, items are ordered by value
- After `sortByName()`, items are ordered alphabetically
- Binary search should require far fewer comparisons than linear search on the same sorted inventory

Run the tests:

```bash
cd dungeongame
./bin/test_sorting
```

---

## Reflection (5 min)
Answer these questions in a few sentences (in your notebook or a comment block in the test file):

1. Why does binary search require sorted data, but linear search does not?
2. What is the practical difference between an O(n) algorithm and an O(n²) algorithm when n is large?
3. In this game, when would it make sense to sort the inventory before searching? When might you prefer to just do a linear search?

---

### Extensions (extra credit)
- Implement and compare **merge sort** (O(n log n)) on the inventory.
- Add a method to sort NPCs by their `getHealth()` or `getAttackPower()` and then search for the weakest/strongest NPC.
- Add a speed benchmark using `std::chrono::steady_clock` to print elapsed time for each algorithm (not just comparison counts).
