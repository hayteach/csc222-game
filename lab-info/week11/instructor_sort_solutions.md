Instructor reference — Merge Sort & Quick Sort (annotated)

Purpose
- These are instructor-only annotated reference implementations for Merge Sort and Quick Sort as used in the game benchmarks. Use this file during live walkthroughs on Zoom to explain the code line-by-line. Students should not copy these files into their implementations; instead they should implement the algorithms themselves in dungeongame/src/SortingStudent.cpp while you walk through this code.

Location in repo: lab-info/week11/instructor_sort_solutions.md

---

Merge sort (array of int) — annotated

Code (student-walkthrough friendly):

```cpp
// Top-level entry: allocate temporary workspace and call recursive helper
size_t mergeSortArray(std::vector<int>& arr) {
    std::vector<int> tmp(arr.size());            // allocate once and pass down
    return mergeSortArrayRec(arr, tmp, 0, (int)arr.size() - 1);
}

// Recursive helper: sorts arr[lo..hi], returns number of comparisons
size_t mergeSortArrayRec(std::vector<int>& arr, std::vector<int>& tmp, int lo, int hi) {
    if (lo >= hi) return 0;                      // base case: zero or one element
    int mid = lo + (hi - lo) / 2;                // mid-point (avoids overflow)
    size_t comps = 0;

    // Sort left half and right half recursively
    comps += mergeSortArrayRec(arr, tmp, lo, mid);
    comps += mergeSortArrayRec(arr, tmp, mid + 1, hi);

    // Merge the two sorted halves into tmp
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        comps++;                                 // counting a comparison between arr[i] and arr[j]
        if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }

    // Copy any remaining elements from the left or right half
    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= hi) tmp[k++] = arr[j++];

    // Copy merged data back into arr[lo..hi]
    for (int x = lo; x <= hi; ++x) arr[x] = tmp[x];

    return comps;
}
```

Walkthrough points for instructor
- Base case: lo >= hi — explain that recursion bottoms out when range has 0 or 1 element.
- Workspace: tmp is allocated once and passed down; this avoids repeated reallocation and is more efficient.
- Comparison counting: we increment comps only when we compare two elements from left and right halves. This gives a reasonable count for merge comparisons.
- Stability: merge copy uses `<=` so items that are equal keep the left-side order, making merge stable.
- Complexity: T(n) = 2 T(n/2) + O(n) → O(n log n).
- Memory: merge requires extra O(n) workspace (tmp).

Suggested instructor questions
- Why do we prefer to allocate `tmp` once at the top-level instead of reallocating in each recursive call?
- What happens to the copy-back step `for (x = lo..hi) arr[x] = tmp[x]` and why is it necessary?
- How would comparator counting change if we compared < instead of <= during merge?

---

Quick sort (array of int) — annotated (Lomuto partition)

Code:

```cpp
// Partition using Lomuto scheme, pivot = arr[hi]. `comps` is incremented for
// each comparison of arr[j] to pivot.
static int partitionQS(std::vector<int>& arr, int lo, int hi, size_t& comps) {
    int pivot = arr[hi];              // choose last element as pivot
    int i = lo - 1;                   // boundary for smaller elements
    for (int j = lo; j < hi; ++j) {
        comps++;                      // one comparison of arr[j] with pivot
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[hi]);  // place pivot in its final position
    return i + 1;                    // return pivot index
}

// Recursive quicksort that accumulates comparisons
size_t quickSortArrayRec(std::vector<int>& arr, int lo, int hi) {
    size_t comps = 0;
    if (lo < hi) {
        int p = partitionQS(arr, lo, hi, comps);
        comps += quickSortArrayRec(arr, lo, p - 1);
        comps += quickSortArrayRec(arr, p + 1, hi);
    }
    return comps;
}

size_t quickSortArray(std::vector<int>& arr) {
    if (arr.empty()) return 0;
    return quickSortArrayRec(arr, 0, (int)arr.size() - 1);
}
```

Walkthrough points for instructor
- Pivot choice: last element (Lomuto). Discuss trade-offs (simplicity vs worst-case behavior on sorted input).
- Partition loop: `i` tracks boundary; when arr[j] < pivot, we extend the smaller-than-pivot region and swap.
- Comparison counting: increment for each arr[j] vs pivot comparison; note that partition itself may do fewer comparisons than a merge but recursive structure affects total.
- Worst-case: if pivot is always minimal or maximal (e.g., already sorted input), quicksort degrades to O(n²). Talk about median-of-three as an improvement.
- In-place: quicksort rearranges elements inside `arr` and uses only O(log n) stack space on average.

Suggested instructor questions
- Why can choosing arr[hi] as pivot be problematic for already-sorted arrays?
- How would the partition change if we used Hoare's partition scheme? (brief comparison)
- What does "in-place" mean in this context and why is it useful?

---

Inventory (Item) versions — mapping to Item.name

- The Item-based merge/quick implementations use the same structure but compare `item.name` strings instead of integers.
- Counting comparisons: increment whenever two Item names are compared.
- Practical note: comparing strings is more expensive than comparing ints; good to mention when interpreting timings.

---

Using these solutions in class
- Share this file on Zoom (screen share or open on the projector). Walk through the code in 5–10 line chunks.
- At each checkpoint: ask students to predict what the code will do for a small input, then run menu 29 (Student Sort Tests) to show the results.
- After the walkthrough, ask students to implement the same functions in `dungeongame/src/SortingStudent.cpp` without copying — they should type and explain each part as they go.

Reminder
- Instructor solutions are for demonstration and explanation. Make it explicit: students must implement the algorithms themselves — the learning objective is to understand and type the code under your guidance.
