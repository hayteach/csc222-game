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

Suggested instructor questions + answers
- Q: Why do we prefer to allocate `tmp` once at the top-level instead of reallocating in each recursive call?
  A: Allocating `tmp` once avoids repeated allocations which are expensive at runtime. Passing a single temporary buffer down the recursion reuses memory and reduces overhead (both time and memory fragmentation). It also keeps the asymptotic extra-space usage to O(n) rather than O(n log n) if each call allocated its own temporary buffer.

- Q: What happens to the copy-back step `for (x = lo..hi) arr[x] = tmp[x]` and why is it necessary?
  A: The merge writes the merged sequence into the temporary buffer (tmp) for indices lo..hi. The copy-back copies the merged segment into the original array so that subsequent recursive calls (or the caller) see the array sorted for that segment. Without the copy-back, arr would still contain the old (unsorted) values and the algorithm would not make progress.

- Q: How would comparator counting change if we compared `<` instead of `<=` during merge?
  A: Using `<` instead of `<=` changes how equal elements are handled (ties). With `<=`, equal elements from the left half are taken before the right half — merge is stable. With `<`, equal elements from the right half may be taken first in some cases, making the algorithm unstable. As for counting, the number of comparisons performed does not change in expectation — each loop iteration still performs a single comparison — but when elements are equal the branching outcome may differ, which can change which elements are moved where. The total comparison count (as implemented here) still increments once per compare, so the numeric count is the same for the same input values regardless of `<` vs `<=`.

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

Suggested instructor questions + answers
- Q: Why can choosing arr[hi] as pivot be problematic for already-sorted arrays?
  A: If the input is already sorted (increasing), choosing the last element as pivot means the pivot is the largest element every time. Partition will place the pivot at the end (no element less than pivot), so one recursive call is of size n-1 and the other is size 0. This yields T(n) = T(n-1) + O(n) which solves to O(n²) — the worst case.

- Q: How would the partition change if we used Hoare's partition scheme? (brief comparison)
  A: Hoare's partition picks a pivot (often arr[(lo+hi)/2]) and uses two indices that move toward each other, swapping out-of-place elements. It tends to do fewer swaps and can be more efficient in practice. Importantly, Hoare's partition returns a split point where both halves are non-empty when elements are distinct, and it can avoid some pathological behavior of Lomuto. However, Hoare's partition is slightly more complex to reason about and its return index semantics differ (so recursion boundaries change).

- Q: What does "in-place" mean in this context and why is it useful?
  A: "In-place" means the algorithm rearranges the elements inside the original array without allocating a proportional extra array (only a small number of extra variables or O(log n) stack frames). It's useful because it reduces extra memory usage, which matters when sorting large datasets or when memory is constrained.

---

Inventory (Item) versions — mapping to Item.name

- The Item-based merge/quick implementations use the same structure but compare `item.name` strings instead of integers.
- Counting comparisons: increment whenever two Item names are compared.
- Practical note: comparing strings is more expensive than comparing ints; good to mention when interpreting timings.

Suggested instructor questions + answers (Inventory context)
- Q: Why does comparing strings affect timing differently than comparing ints?
  A: String comparison may examine multiple characters until a difference is found, so its cost depends on string length and common prefixes. Comparing ints is a single CPU operation. Therefore, even with the same number of comparisons, sorts on strings can be substantially slower than sorts on ints.

- Q: If two items have equal names, how does merge's stability help in an Inventory context?
  A: Stability preserves the relative order of equal-name items. In an inventory, items may have other fields (e.g., value, acquisition time). A stable sort by name will keep earlier-acquired items before later ones, which can be important if the secondary order matters or the UI expects deterministic ordering.

---

Using these solutions in class
- Share this file on Zoom (screen share or open on the projector). Walk through the code in 5–10 line chunks.
- At each checkpoint: ask students to predict what the code will do for a small input, then run menu 29 (Student Sort Tests) to show the results.
- After the walkthrough, ask students to implement the same functions in `dungeongame/src/SortingStudent.cpp` without copying — they should type and explain each part as they go.

Reminder
- Instructor solutions are for demonstration and explanation. Make it explicit: students must implement the algorithms themselves — the learning objective is to understand and type the code under your guidance.
