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

## How to run (step-by-step)
1. Build the game:

```bash
cd dungeongame
make
```

2. Run the game executable:

```bash
./bin/dungeongame
```

3. From the main menu choose one of the new options:
- 27 → Array Sort Benchmarks (CSV): This will print a header line and then many CSV lines for default sizes: 100, 1000, 10000, 50000, 100000. Example CSV header:

```
size,algorithm,time_us,comparisons
```

Copy the CSV output into a file (or pipe into a file if you run the game in a terminal that supports redirection). Example (from a shell):

```bash
./bin/dungeongame > sort_results.txt
# then in the game choose 27 and let it run; all CSV lines will be captured in sort_results.txt
```

- 28 → Run all sorts on Inventory (compare): This prints a human-readable report showing the sorted inventory for each algorithm, comparisons, and microsecond timings.

4. Plotting the results:
- Paste the CSV data into Excel / Google Sheets. Recommended sizes are already used by the benchmark; use log-log plots to visualize growth across orders of magnitude.
- For each algorithm plot `time_us` vs `size`. You can also plot `comparisons` vs `size`.

---

## Lab tasks (student-facing)
1. Run the game and choose menu option 27 to collect CSV timing/comparison data for array sorts.
2. Paste the CSV into a sheet and produce plots (suggested: log-log chart of time vs size). Include a short caption describing which algorithms match O(n²) vs O(n log n) behavior.
3. Choose menu option 28 to run all sorts on the Inventory. Observe differences in comparisons/time and note any ordering differences.
4. Answer the reflection questions below and submit your plots + source file modifications (if you made changes).

Reflection questions (short answers):
- Why does binary search require sorted data, but linear search does not?
- For a single search on a small list, which is faster: sort+binary-search or linear search? Explain.
- How do merge sort and quick sort differ in memory usage and stability?
- When would you avoid using bubble or insertion sort in real assignments or production code?

---

## Instructor notes
- The game runs bubble and insertion for all sizes by default. Bubble/insertion on 100k can be very slow; it's intentional for demonstration but consider warning students or skipping bubble/insertion at the largest size during live demos.
- If you want to skip expensive sorts for the largest sizes, run the game and choose option 27, then press Ctrl+C and re-run with the game redirected into a capture file and stop after the sizes you want. (Alternatively I can modify the code to skip O(n²) sorts for sizes > X — tell me if you want that change.)

---

## Deliverables
- A single document (PDF or notebook) including:
  - Plots for each sorting algorithm (time vs size)
  - Short answers to the reflection questions
  - Any code changes you made (if students extend or optimize algorithms)

---

If you'd like, I will:
- Add the Big-O summary into the Player/Inventory header comments as inline notes.
- Add a small worksheet file (lab-info/week11/worksheet.md) and example CSV sample (lab-info/week11/sample_sort_results.csv).

Shall I add the worksheet and sample CSV now? If yes, I will create them and commit to branch `week11`.