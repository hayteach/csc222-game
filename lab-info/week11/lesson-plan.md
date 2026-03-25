# Week 11 — Sorting, Search, and Benchmarks (Lesson Plan — Zoom interactive model)

## Context
This lesson adapts HW07 material (Merge & Quick sort + timing comparisons) into the Dungeon of Data Structures game. You will teach live on Zoom and have students type and test code while you guide and ask questions. The repo branch `week11` contains starter files (including SortingStudent skeletons) so students build their implementations during class.

Course: CSC222 — Programming & Algorithms II
Week: 11
Topic: Merge sort, Quick sort, Binary search, Benchmarks and Big-O in practice

---

## Learning objectives
By the end of class students will be able to:
- Explain the difference between O(n), O(n log n), and O(n²) in practical terms.
- Implement recursive Merge sort and Quick sort for arrays and count their element comparisons.
- Run and collect empirical timing + comparison data for multiple sorting algorithms and plot the results.
- Apply sorting to the game's Inventory and reason when to sort vs. linear scan for search tasks.

---

## Zoom teaching model — high level
- Instructor-led, hands-on: you (instructor) share your screen to demo, then prompt students to type the same code in their environment while you narrate and ask guided questions.
- Frequent checkpoints: after each small chunk of code (5–10 minutes), pause, ask 1–2 diagnostic questions, and request a short chat/raise-hand response.
- Active checks: use Zoom reactions or the chat for quick polls (e.g., "what is the time complexity of the merge step?"), and use breakout rooms for the paired extension work.

---

## Quick Big-O reference (for the Zoom slides / board)
- Bubble sort: O(n²) average/worst, O(n) best if short-circuited; memory O(1); stable.
- Insertion sort: O(n²) average/worst, O(n) best for nearly-sorted input; memory O(1); stable.
- Merge sort: O(n log n) always; extra memory O(n) for merging; stable.
- Quick sort: average O(n log n), worst O(n²) with poor pivots; in-place (small extra stack), typically faster than merge for in-memory sorts; not stable by default.
- Binary search: O(log n) — requires sorted input. Linear search: O(n) — works on unsorted data.

---

## Class logistics
- Time: 75-minute plan below (50-minute condensed variant afterwards).
- Zoom: share screen (your IDE/terminal), encourage camera on for short checks, use chat/reactions for answers, and create breakout rooms for pair work.
- Repo/branch: ~/Projects/Mendocino College/CSC222/game → branch `week11` (includes SortingStudent skeletons in dungeongame/include & src).
- In-game helpers: menu 27/28 run benchmarks and inventory demos. Students will implement SortingStudent and run small tests in-game by temporarily calling their functions from a test spot (instructions provided below).

---

## Lesson plan (75-minute Zoom-friendly version)
Timing and instructor prompts are included so you can read them during class.

0. (5 min) Setup & housekeeping — instructor script
- Prompt (chat): "Please pull branch 'week11' now: git fetch origin && git checkout week11 && git pull". Wait for confirmation or a thumbs-up reaction.
- Instructor: build on screen: `cd dungeongame && make`. Ask: "Any build errors?" Troubleshoot 1–2 fastest students.
- Start the game once to show menu (briefly): `./bin/dungeongame` (then exit).

1. (8 min) Mini-lecture + concept checks (divide & conquer)
- Share slide/board: show merge vs quick high-level diagrams (2–3 slides).
- Ask via chat: "Which sort needs extra O(n) memory?" Wait for 5–10 replies; read one or two.
- Quick demo: show the existing Inventory run-all-sorts output (menu 28) to illustrate comparison counts.

2. (35 min) Guided live coding — students type Merge Sort then Quick Sort
This is the core Zoom activity. Work in small chunks and use frequent checks.

Instructor script & checkpoints (recommended pacing):
A) Prepare files (2 min)
- Ask students to open `dungeongame/src/SortingStudent.cpp` and `dungeongame/include/dungeongame/SortingStudent.h`.
- Instructor: share these files on your screen so everyone sees the TODO stubs.

B) Implement mergeSortArray helper + base case (8–10 min)
- Ask students to type with you: create a helper `mergeSortRec(std::vector<int>& arr, std::vector<int>& tmp, int lo, int hi)` that returns size_t comparisons.
- Pause and ask: "What should be the base case?" (expect answer: lo >= hi)
- After writing the base, ask students to run a quick compilation (`make`) to catch trivial typos.

C) Implement merge step with comparison counting (8–10 min)
- Instructor shows pseudocode and types the merge loop. Emphasize: "Increment comparisons each time you compare arr[i] and arr[j]."
- Pause for 1-minute think: ask students in chat: "How many comparisons do we expect when merging two halves of size n/2?" (expect O(n)).
- Compile and run a small test: temporarily change `runArraySortBenchmarks()` to call student `mergeSortArray` only for size 8 or 20 (instructions below). Rebuild and run to test correctness.

D) Implement quickSortArray and partition (8–10 min)
- Instructor: guide partition implementation (Lomuto favored for simplicity). For partitions, emphasize counting comparisons when comparing arr[j] to pivot.
- Checkpoint: ask students to explain (in chat or aloud) why worst-case quick sort is O(n²).
- Compile and test on small arrays as above.

E) Finalize and run small in-game test (4–5 min)
- Instructor: show how to temporarily call student functions from a safe small test area:
  1. In Game.cpp locate `runArraySortBenchmarks()` (or add a short `case 29` in `processChoice`) and replace the call for sizes <= 100 with calls to `mergeSortArray` and `quickSortArray` from `SortingStudent`.
  2. Rebuild and run the game, choose the test menu option and show printed comparisons and small sorted outputs.
- Ask: "Do the outputs match expectations for small n?" (students reply).

Notes during coding
- Keep commits small: after finishing Merge, encourage `git add` + `git commit -m "student: merge sort implementation"` then push to a personal branch.
- If students get stuck, use breakout rooms and ask the TA/instructor to drop in.

3. (15 min) Hands-on benchmarking + plotting (paired)
- With merge/quick implemented, students run menu 27 locally (or instructor runs and shares CSV). Ask pairs to produce a log-log plot (time_us vs size) and annotate which algorithms follow O(n²) vs O(n log n).
- Instructor script: "Upload one screenshot of your plot to the chat and paste your interpretation in two sentences." Give 8 minutes and then review 2–3 examples.

4. (7 min) Wrap-up & homework
- Collect plots and one-sentence interpretations. Reiterate: "Merge is stable and uses extra memory; quick is in-place but pivot choice matters."
- Homework: finish plotting and submit the worksheet + code branch.

---

## 50-minute condensed variant (Zoom)
- 5 min: Setup & pull branch
- 10 min: Mini-lecture + show menu 28 output
- 25 min: Guided coding (focus on merge only or quick only; shorten tests)
- 5 min: Run small benchmark, close with assignment

---

## Testing student code during class (practical instructions)
If you don't want to add new menu options during class, use this quick workflow to test on small arrays:
- Open `dungeongame/src/Game.cpp`.
- Find `runArraySortBenchmarks()` and temporarily add calls to `dungeongame::mergeSortArray` / `dungeongame::quickSortArray` (from SortingStudent) for very small sizes (8, 20). Example snippet:

```cpp
// inside runArraySortBenchmarks() for testing only
std::vector<int> small = {5,2,9,1,6,3,8,4};
auto compsM = dungeongame::mergeSortArray(small);
// print result and comps
```

- Rebuild: `cd dungeongame && make` and run `./bin/dungeongame` and choose the test path.
- After class revert changes to Game.cpp (or commit them to your personal branch) so the main `week11` benchmark code remains unchanged.

---

## Instructor notes & suggestions
- Use chat and reactions for micro-checks (do not over-use polls). Stop every 5–8 minutes and ask one comprehension check.
- Encourage students to `git commit` early even if code is incomplete — small commits help rollback.
- If many students hit build problems, show a short checklist for troubleshooting (missing include, typo, forgetting std::vector, etc.).

---

## Files to mention during class
- dungeongame/include/dungeongame/SortingStudent.h (skeleton declarations)
- dungeongame/src/SortingStudent.cpp (student TODOs)
- dungeongame/src/Game.cpp (where to add small test calls or temporary menu hook)
- lab-info/week11/game_lab_activity.md (detailed student instructions)


If you want, I can now:
- Produce a short slide deck with instructor prompts and Zoom timing, or
- Add an in-game menu option (29) that explicitly runs the student implementations on small sizes for quick testing (I can add this and wire it so students don't have to edit Game.cpp).
