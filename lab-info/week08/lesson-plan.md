# Week 08 — Algorithm Efficiency, Big-O Notation & Sorting Algorithms

## Learning Objectives
- Explain what Big-O notation measures and why it matters for practical software
- Classify common algorithms by their growth rate: O(1), O(log n), O(n), O(n log n), O(n²)
- Analyze best, worst, and average-case complexity for loops and simple programs
- Implement and compare at least three sorting algorithms (bubble, selection, insertion) in C++
- Identify which sorting algorithm is appropriate for a given data size and access pattern
- Use visualization tools to build mental models of how sorting algorithms actually behave
- Connect Big-O analysis back to concrete code in the dungeon game project

---

## In-class Activities (90 min)

### 1. Warm-up — How Slow Is Slow? (10 min)
Open the Big-O complexity cheat sheet:  
🔗 https://www.freecodecamp.org/news/big-o-cheat-sheet-time-complexity-chart/

Ask students:
- If the dungeon game has 1,000 items in the inventory, how many comparisons does a **linear search** make in the worst case?
- What if the inventory had 1,000,000 items?  
- What if you could sort it first and use **binary search**?

Write the three answers on the board: `1,000`, `1,000,000`, `20`. Let that sink in.

---

### 2. Lecture — Big-O Notation (25 min)

#### 2.1 What Big-O Measures
Big-O describes how the **number of operations** grows relative to input size **n**. It ignores hardware, constants, and small inputs — all that matters is the *shape* of the growth curve.

| Class | Name | Example |
|:---|:---|:---|
| O(1) | Constant | Accessing `inventory[0]` by index |
| O(log n) | Logarithmic | Binary search on a sorted array |
| O(n) | Linear | Linear scan/search through a list |
| O(n log n) | Linearithmic | Merge sort, quicksort (average) |
| O(n²) | Quadratic | Bubble sort, nested loops |
| O(2ⁿ) | Exponential | Brute-force recursive subsets |

#### 2.2 Identifying Complexity in Code
Walk through three patterns students will see constantly:

```cpp
// O(1) — constant time, no loop, direct access
Item& get(size_t i) { return items[i]; }

// O(n) — single loop over all elements
int findByName(const std::string& name) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].name == name) return i;
    }
    return -1;
}

// O(n²) — loop inside a loop (both scale with n)
void bubbleSort() {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (items[j].value > items[j+1].value)
                swap(items[j], items[j+1]);
        }
    }
}
```

#### 2.3 Best, Worst, and Average Case
- **Worst case** (most useful): guarantees an upper bound — what we promise the user.
- **Best case**: useful for understanding lucky scenarios (already-sorted input).
- **Average case**: realistic expectation over random inputs.

Example: linear search  
- Best: element is first → O(1)  
- Worst: element is last (or missing) → O(n)  
- Average: element is in the middle → O(n/2) = O(n)

---

### 3. Guided Activity — Visualizing Sorting Algorithms (20 min)
Open the visualization site:  
🔗 https://visualgo.net/en

Select **Sorting** and walk through each algorithm together as a class:

1. **Bubble Sort** — watch adjacent swaps bubble the largest element to the end each pass. Count the swaps for n=8.
2. **Selection Sort** — watch it find the minimum each pass and swap it to the front.
3. **Insertion Sort** — watch it build a sorted subarray from left to right (behaves well on nearly-sorted data).
4. **Merge Sort** — watch the divide-and-conquer split and merge phases. Note that it's always O(n log n).
5. **Quick Sort** — watch the pivot partitioning. Fast in practice, but worst case O(n²) on bad pivot choices.

Optional live sorting race:  
🔗 https://www.toptal.com/developers/sorting-algorithms  
Set array to "Random" and hit **Start All** — students can observe the differences in step count and time.

Discussion questions:
- Which algorithm looks most "chaotic"? Which looks most "efficient"?
- When would you choose insertion sort over merge sort?
- Why does quicksort beat merge sort in practice even though they share O(n log n) average?

---

### 4. Application — Sorting in the Dungeon Game (25 min)
Bridge the abstract to the code students already have. See `game_lab_activity.md` for the full step-by-step instructions. In class, walk through **Steps 1–3** together:

- Step 1: Annotate existing game methods (Inventory, NPCGroup) with their Big-O complexity.
- Step 2: Add `sortByValue()` (bubble sort) to `Inventory`.
- Step 3: Add `searchByName()` comparing linear vs. binary search — run both and count operations.

---

### 5. Wrap-up & Preview (10 min)
- Recap the growth rate table. Ask: "Why can O(n log n) sort millions of items but O(n²) can't?"
- Preview the lab: students finish Steps 4–6 of `game_lab_activity.md` on their own, adding sorting to `NPCGroup` and benchmarking their implementations.
- Point to homework: implement a second sort (selection or insertion) and compare operation counts empirically.

---

## Homework
- Complete all steps in `game_lab_activity.md` if not finished in class.
- Add a `sortByName()` method to `Inventory` using **selection sort** (different from the bubble sort done in lab).
- Add a `sortByHealth()` method to `NPCGroup` using **insertion sort**.
- Write a `test_sorting.cpp` test program that:
  1. Creates an `Inventory` with at least 8 items in unsorted order.
  2. Calls `sortByValue()` and prints before/after.
  3. Calls `sortByName()` and prints before/after.
  4. Counts the number of comparisons each sort makes and records them in a comment.
- In a comment block at the top of `test_sorting.cpp`, state the Big-O class of each sorting method you implemented and explain why it falls in that class.

---

## Resources
| Resource | URL |
|:---|:---|
| Big-O Cheat Sheet | https://www.freecodecamp.org/news/big-o-cheat-sheet-time-complexity-chart/ |
| Sorting Algorithm Visualizer | https://www.toptal.com/developers/sorting-algorithms |
| VisuAlgo (interactive visualizations) | https://visualgo.net/en |
| Saylor: Algorithm Efficiency (readings in week08/) | `lab-info/week08/introduction.md` |

---

> **Instructor notes:**  
> - **Key connection:** Students have already seen O(n) traversal in `LinkedList` and `LinkedBag`. Sorting is the natural next step — it requires *doing* something useful with that traversal beyond just printing.  
> - **Avoid theory overload:** The goal is *recognition*, not derivation. Students should be able to look at a loop and say "that's O(n)" or "those nested loops are O(n²)".  
> - **Visualization first:** Many students struggle to picture algorithms from pseudocode alone. Running visualgo.net *before* showing code is intentional — it gives them a mental image to anchor the code to.  
> - **Game context:** The dungeon game provides a concrete motivation. "How fast can I search for a potion in a 500-item inventory?" is a question students care about.  
> - **Keep sorts simple:** For this week, focus on O(n²) sorts as implementations. O(n log n) sorts (merge, quick) are demonstrated visually and discussed conceptually — students are not expected to implement them from scratch this week.
