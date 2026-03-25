# Game Lab Activity — Sorting & Search (Week 11)

## Overview
This week's lab adapts HW07 into the Dungeon of Data Structures game. Students will add and compare multiple sorting algorithms (bubble, insertion, merge, quick) and observe how sorting enables fast searching (binary search). All work is integrated into the existing game — no extra programs are required.

Goals
- Implement/inspect Merge and Quick sort concepts (already instrumented in the game).
- Run array-based benchmarks (default sizes) and collect CSV timing + comparison data for plotting.
- Run the same sorts on the game's Inventory and compare results (comparisons + microsecond timing).
- Connect sorting Big-O to practical timing and memory trade-offs.

Prerequisites
- Familiarity with bubble and insertion sort (O(n²)), and linear vs binary search.
- The repository with the game (we'll use the branch `week11` already prepared).

---

## Big-O summary (quick reference)
- Bubble sort: Worst/average O(n²), Best O(n) if you short-circuit for already-sorted input. Memory: O(1). Stable.
- Insertion sort: Worst/average O(n²), Best O(n) when input is nearly sorted. Memory: O(1). Stable.
- Merge sort: Worst/average/best O(n log n). Memory: O(n) extra for merging (not in-place). Stable.
- Quick sort: Average O(n log n), Worst O(n²) (depends on pivot choice). In-place (no large extra array), memory O(log n) stack on average. Not stable unless implemented specially.
- Binary search: O(log n) — requires sorted data. Linear search: O(n) — works on unsorted data.

Discussion points for students:
- When is it worth sorting data before repeated searches? (Hint: amortize cost: if you'll search many times, sorting once then binary searching is often better.)
- Memory trade-offs: merge uses extra space; quick usually sorts in-place but can degrade without good pivot choice.

---

## What I added to the game (branch: week11)
- Menu options:
  - 27) Array Sort Benchmarks (CSV output) — runs bubble, insertion, merge, and quick on randomly-generated integer arrays at the default sizes and prints CSV lines: `size,algorithm,time_us,comparisons`.
  - 28) Run all sorts on Inventory (compare) — copies the player's inventory and runs bubble, insertion, merge, and quick (name-based comparisons). Prints sorted results, comparison counts, and timing (microseconds).
- Implemented instrumented versions of the four sorting algorithms for arrays and for Inventory (vector<Item>) with comparison counters and microsecond timing. The CSV output is suitable for pasting into Excel/Google Sheets and plotting (log-log or semilog as appropriate).

Note: these demos are designed to run from inside the game menu — no separate test programs are required.

---

## Step-by-step in-class activity (detailed)
These instructions are written so an instructor can follow them live and students can follow step-by-step during class. They work for both 75- and 50-minute sessions; pick the parts that fit your time.

Prerequisites: students should have pulled branch `week11` and have a C++ toolchain (make) available.

A. Preparation (5 minutes)
1. Ask students to pull the latest `week11` branch:
   - git fetch origin
   - git checkout week11
   - git pull
2. Build the game (in front of the class):
   - cd dungeongame
   - make
3. Start the game:
   - ./bin/dungeongame

B. Instructor demo: Inventory sorts & search (10 minutes)
1. From the main menu choose option 28 (Run all sorts on Inventory).
2. Walk through the printed output:
   - For each algorithm (bubble, insertion, merge, quick) point out the sorted order, the comparison count, and the elapsed microseconds.
   - Ask: do the comparison counts match your expectation for O(n²) vs O(n log n)?
3. Show the students how to invoke the simpler Sort/Search demo (menu 25) and demonstrate linear vs binary search counts for a chosen target (e.g., "Potion").

C. Student hands-on: Array benchmark collection (25 minutes)
1. Ask students to run the game themselves (or run it on a projector and have them follow along). If they run locally, tell them to redirect output into a file to capture CSV data:
   - ./bin/dungeongame > sort_results.txt
   - In the game menu, choose option 27 (Array Sort Benchmarks).
   - Let it run until it finishes (it will print CSV header and rows). Press Enter/back to main menu when done.
2. Open the CSV (sort_results.txt) in Excel or Google Sheets. If students ran the game without redirection, they can copy/paste the CSV lines from their terminal into a new sheet.
3. In the sheet produce a log-log plot (time_us vs size) with one series per algorithm. If CSV contains "skipped" entries for bubble/insertion on large sizes, skip those rows or treat as N/A.
4. Ask students to annotate the chart and write one sentence: which algorithms match O(n²) and which match O(n log n) in the plotted range?

D. Coding exercise — Implement Merge Sort and Quick Sort (35 minutes)
This is the central in-class coding task: students will implement Merge Sort and Quick Sort themselves (array-based) inside the game code so they understand the recursion, merging, partitioning, and comparison counting.

Instructor notes before you begin:
- The repository already contains working implementations for benchmarks; **do not** let students copy those during the exercise. Instead either ask students to work from a provided starter skeleton (recommended) or ask them to remove/ignore the working implementations and implement their own versions in a new helper file (e.g., `dungeongame/src/SortingStudent.cpp`).
- I'll add starter skeletons and a short checklist below to make the exercise smooth.

Step-by-step student checklist
1. Create a new source file for your implementation (recommended so you don't overwrite instructor reference):
   - dungeongame/src/SortingStudent.cpp
   - dungeongame/include/dungeongame/SortingStudent.h
2. Add function signatures (matching Game.cpp's expectations) in the header. Suggested signatures:

```cpp
// Return number of string/int comparisons performed while sorting
size_t mergeSortArray(std::vector<int>& arr);
size_t quickSortArray(std::vector<int>& arr);

// (Optional) instrumented item-based versions for Inventory
std::pair<std::vector<Item>, size_t> mergeItems(std::vector<Item> v);
std::pair<std::vector<Item>, size_t> quickItems(std::vector<Item> v);
```

3. Implement Merge Sort (array of ints) using this plan:
   - Write a recursive helper mergeSortRec(arr, tmp, lo, hi) that returns comparison count.
   - Base case: if lo >= hi return 0.
   - Recursively sort left and right halves and accumulate their comparison counts.
   - Merge the two halves into the tmp array while counting comparisons between elements.
   - Copy merged results back to arr for indices [lo..hi].

Pseudocode (high level):
- mergeSortRec(arr, tmp, lo, hi):
  - if lo >= hi return 0
  - mid = (lo+hi)/2
  - comps = mergeSortRec(arr, tmp, lo, mid)
  - comps += mergeSortRec(arr, tmp, mid+1, hi)
  - i = lo; j = mid+1; k=lo
  - while i<=mid and j<=hi:
      comps++
      if arr[i] <= arr[j]: tmp[k++] = arr[i++]
      else: tmp[k++] = arr[j++]
  - copy remaining
  - copy tmp[lo..hi] back to arr[lo..hi]
  - return comps

4. Implement Quick Sort (array of ints) using this plan:
   - Implement partition(arr, lo, hi, compsRef) that picks a pivot (initially arr[hi]), partitions array in place, increments compsRef when comparing elements to pivot, and returns pivot index.
   - Implement quickSortRec(arr, lo, hi) that uses partition and recurses; return accumulated comparisons.

Pseudocode (high level):
- partition(arr, lo, hi, compsRef):
  - pivot = arr[hi]
  - i = lo - 1
  - for j in [lo..hi-1]:
      compsRef++
      if arr[j] < pivot: ++i; swap arr[i], arr[j]
  - swap arr[i+1], arr[hi]
  - return i+1

- quickSortRec(arr, lo, hi):
  - if lo < hi:
      p = partition(arr, lo, hi, comps)
      comps += quickSortRec(arr, lo, p-1)
      comps += quickSortRec(arr, p+1, hi)
  - return comps

Hints and gotchas:
- Use a temporary vector `tmp(arr.size())` for merge and pass it down into recursive calls to avoid re-allocating each time.
- For quick sort, be careful with indices and when the partition returns; ensure recursion base cases avoid infinite recursion.
- Count comparisons consistently: for merge count each comparison of arr[i] and arr[j]; for quick count each comparison of arr[j] with pivot.
- Test early on small arrays (n=8, n=20) and print both input and sorted output to confirm correctness before running large benchmarks.

5. Integrate & test inside the game
   - #include "dungeongame/SortingStudent.h" from Game.cpp near the other includes.
   - Temporarily modify runArraySortBenchmarks() to call your mergeSortArray and quickSortArray instead of the built-in versions, or add a short menu option that calls your student implementations on small sizes for quick testing.
   - Rebuild: cd dungeongame && make
   - Run the game and use the small test sizes to validate correctness.

6. Commit and push your work
   - git checkout -b week11/yourname-sorts
   - git add dungeongame/src/SortingStudent.* dungeongame/include/dungeongame/SortingStudent.h
   - git commit -m "student: implement merge and quick sort (starter exercise)"
   - git push -u origin week11/yourname-sorts

E. Quick paired coding extension (20 minutes)
Choose one of these small tasks for pairs to work on. Each pair should commit and push their changes to a personal branch (e.g., `week11/quickpivot-{initials}`) and show results to the instructor.

Option A — Median-of-three pivot for QuickSort
- Modify partitionQS / quickSortArray to use median-of-three pivot selection (lo, mid, hi) instead of always using arr[hi]. Re-run menu 27 and observe any changes in timings for quick sort.

Option B — Add menu toggle to limit algorithms
- Add a simple menu prompt before benchmarks that asks which algorithms to run (e.g., Y/N for bubble, insertion, merge, quick) and only run selected algorithms. Commit the change and re-run.

Option C — Deterministic inputs
- Change the benchmark generator to populate arrays with deterministic patterns: sorted, reverse-sorted, nearly-sorted, random. Run the benchmark for each pattern and compare the outcomes.

F. Wrap-up and submission (5 minutes)
1. Students should export their plots and include a 1-page write-up answering the worksheet questions (lab-info/week11/worksheet.md).
2. If they modified code, each pair should push a branch and submit a short PR or show the instructor locally.
3. Collect any questions and summarize key takeaways: when to choose O(n log n) sorts, memory trade-offs, and when linear search is acceptable.

---

## How to capture results reliably (tips)
- Redirect game output to a file to ensure CSV rows are saved: `./bin/dungeongame > lab-info/week11/last_run_results.csv` and then choose menu 27. The file will contain CSV lines you can paste into Sheets.
- If students' machines are slow, recommend they run only merge/quick for large sizes or use the provided sample CSV (lab-info/week11/sample_sort_results.csv).
- For reproducible benchmarks, edit Game.cpp and call `srand(42);` at the top of `runArraySortBenchmarks()` so arrays are deterministic across runs.

---

## Deliverables
- A CSV of benchmark results (or the shared sample CSV) and the plotted charts (log-log or semilog) in a PDF or image.
- A short write-up answering the worksheet questions and explaining any changes you made.
- Optional: code changes pushed to a branch with a brief PR description.

---

If you want I can also:
- Add an in-game prompt to choose which algorithms to run (makes the student workflow simpler),
- Automatically write the CSV to `lab-info/week11/last_run_results.csv` each time menu 27 runs,
- Or produce a one-page printable handout / slide PDF from this step-by-step.

Which of those would you like me to add next?