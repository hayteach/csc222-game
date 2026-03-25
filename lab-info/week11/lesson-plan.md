# Week 10 — Searching & Sorting

## Learning Objectives
- Illustrate the basic components of search algorithms and their various implementations (linear, binary, tree search)
- Explain the differences between list and tree search-and-sort approaches
- Describe the key ideas behind common sorting algorithms and when to use them
- Explain basic complexity analysis and Big-O notation for searching and sorting
- Apply search and sort techniques in the dungeon game codebase and reason about their performance

---

## 1. Warm-up (10 min)
### Why searching and sorting matter
Ask students:
- How do you find a phone number in a list of contacts? How would you do it if the list is **unsorted** vs. **sorted**?
- Why do real-world systems (search engines, online stores, databases) care so much about sorting and searching?

Have them brainstorm answers, then show:
- Linear scan is easy but can be slow (O(n))
- Sorting lets us use faster searches (e.g., binary search O(log n))

---

## 2. Lecture — Search Algorithms (25 min)

### 2.1 List Search: Linear vs. Binary
- **Linear search** (sequential scan): works on any list (sorted or not)
- **Binary search**: requires a **sorted** list, then repeatedly halves the search range

#### Code sketch (C++):
```cpp
// Linear search: O(n)
int linearSearch(const std::vector<Item>& items, const std::string& name) {
    for (int i = 0; i < (int)items.size(); i++) {
        if (items[i].name == name) return i;
    }
    return -1;
}

// Binary search: O(log n) (sorted input required)
int binarySearch(const std::vector<Item>& items, const std::string& name) {
    int lo = 0, hi = (int)items.size() - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (items[mid].name == name) return mid;
        if (items[mid].name < name) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
```

### 2.2 Tree Search (optional / conceptual)
- Explain the idea of a **binary search tree** (BST): left < node < right
- Show how search is a recursive descent down the tree
- Mention that balanced trees (AVL, red-black) provide O(log n) search reliably

---

## 3. Lecture — Sorting Algorithms (25 min)

### 3.1 Why sort?
- Sorting is a common precondition for faster searching (binary search, merge, etc.)
- Many problems are easier on sorted data (e.g., deduplication, range queries)

### 3.2 Sorting algorithm overview
Briefly discuss:
- **Bubble sort** (O(n²)): simple, swap adjacent out-of-order elements
- **Selection sort** (O(n²)): repeatedly pick the min and place it at the front
- **Insertion sort** (O(n²) worst; O(n) best): builds sorted prefix; good for nearly sorted input
- **Merge sort** (O(n log n) stable; divide & conquer)
- **Quick sort** (average O(n log n), worst O(n²); pivot partitioning)
- **Radix sort** (non-comparative; O(n·k) with k = number of digit positions)

### 3.3 Complexity review (Big-O)
- Grew from week 8: compare O(n), O(n log n), O(n²)
- Emphasize: constants and lower-order terms don’t matter for big input sizes

---

## 4. Guided lab activity (35 min)

### 4.1 Visualize algorithms (10 min)
- Open **Visualgo**: https://visualgo.net/en
- Walk through **Searching** (linear vs binary) and **Sorting** algorithms (bubble, selection, insertion, merge, quick)
- Ask: “Which algorithms do you see doing work on already-sorted input?”

### 4.2 Apply to the dungeon game code (25 min)
- Open `game_lab_activity.md` (existing lab instructions) and locate the sections for searching and sorting.
- In class, do the following together:
  1. **Inventory search:** Implement `linearSearchByName()` for `Inventory` and count comparisons.
  2. **Sorting:** Add `bubbleSortByValue()` to `Inventory` (or use existing bubble sort helper) and show before/after.
  3. **Binary search experiment:** After sorting, implement `binarySearchByName()` and compare the count of comparisons vs. linear search.

---

## 5. Homework / follow-up (take-home / next class)
- Complete the remaining steps in `game_lab_activity.md` if not finished during class.
- Add a second sort algorithm:
  - Option A: **Selection sort** for `Inventory::sortByName()`
  - Option B: **Insertion sort** for `NPCGroup::sortByHealth()`
- Write a small test program (e.g., in `tests/test_sorting.cpp`) that:
  1. Creates an `Inventory` with at least 8 unsorted items
  2. Runs bubble sort and selection/insertion sort, printing the list before and after
  3. Prints the number of comparisons each sort made
- In a comment at the top of the test, record the Big-O class of each implemented sort and why it matches that class.

---

## Resources
- **Visualgo** (interactive algorithm visualizations): https://visualgo.net/en
- **Sorting Algorithm Visualizer**: https://www.toptal.com/developers/sorting-algorithms
- **Radix sort explanation**: (no link provided; use existing course resource or search for “radix sort”)

> **Instructor notes:**
> - Emphasize the trade-off between simplicity and performance: O(n²) sorts are fine for small lists (e.g., inventory sizes), but become impractical on large data.
> - Tie back to the dungeon game: searching an unsorted inventory is easy to implement but gets slow as the item count grows. Sorting once and then searching can make sense when you search multiple times.
> - Keep the focus on **understanding** rather than memorizing formulas. If students can explain why binary search is faster than linear search in one sentence, you’ve succeeded.
