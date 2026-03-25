# Week 11 — Sorting, Search, and Benchmarks (Lesson Plan)

## Context
This lesson takes the HW07 material (Merge & Quick sort + timing comparisons) and integrates it into the Dungeon of Data Structures game. All work is done in the repository branch `week11` and students will run demos from inside the game (menu options 27/28).

Course: CSC222 — Programming & Algorithms II
Week: 11
Topic: Merge sort, Quick sort, Binary search, Benchmarks and Big-O in practice

---

## Learning objectives
By the end of class students will be able to:
- Explain the difference between O(n), O(n log n), and O(n²) in practical terms.
- Describe Merge sort and Quick sort (divide & conquer) and their trade-offs (memory, stability, worst-case behavior).
- Run and collect empirical timing + comparison data for multiple sorting algorithms and plot the results.
- Apply sorting to the game's Inventory and reason about when to sort vs. linear scan for search tasks.

---

## Quick Big-O reference (for students)
- Bubble sort: O(n²) average/worst, O(n) best if short-circuited; memory O(1); stable.
- Insertion sort: O(n²) average/worst, O(n) best for nearly-sorted input; memory O(1); stable.
- Merge sort: O(n log n) always; extra memory O(n) for merging; stable.
- Quick sort: average O(n log n), worst O(n²) with poor pivots; in-place (small extra stack), typically faster than merge for in-memory sorts; not stable by default.
- Binary search: O(log n) — requires sorted input. Linear search: O(n) — works on unsorted data.

---

## Class logistics
- Date/time: Today — class at 2:00 PM (you mentioned this in chat).
- Recommended session length: 75 minutes. (If your section is 50 minutes, follow the 50-min variant below.)
- Repo/branch: ~/Projects/Mendocino College/CSC222/game → branch `week11` (I've pushed all changes there).
- New game menu items (use these during class):
  - 27) Array Sort Benchmarks (CSV output) — prints CSV lines for sizes up to 1,000,000 (bubble/insertion are skipped for very large sizes).
  - 28) Run all sorts on Inventory (compare) — runs bubble, insertion, merge, quick on game Inventory and prints comparisons + timings.

---

## Lesson plan (75-minute version)

0. (5 min) Setup & housekeeping
- Confirm students have pulled branch `week11` and built the game.
  - cd dungeongame && make
  - ./bin/dungeongame
- Briefly recap last week's material and learning goals for today.

1. (10 min) Concept check: divide & conquer and Big-O (lecture + questions)
- Quick conceptual slides / board work: recursion in merge/quick, comparison counts, and memory trade-offs.
- Ask two quick questions to students (think-pair-share): when would you prefer merge vs quick? when is insertion sort useful?

2. (10 min) Live demo: inventory sorting & search (in-game)
- Run the game, choose menu item 28 and demonstrate the Inventory run-all-sorts output.
- Show the sorted output, comparison counts, and microsecond timings.
- Emphasize: these timings are noisy on laptops — focus on trends and comparison counts.

3. (20 min) Guided lab: array benchmarks (hands-on)
- Ask students to run menu item 27 themselves (or run it for the class and capture CSV output).
  - Redirect output to a file if running in a terminal you control: ./bin/dungeongame > sort_results.csv
  - Choose 27 and let it run; open the CSV in Excel/Google Sheets.
- Students create a log-log plot (time_us vs size) and annotate which algorithms match O(n²) vs O(n log n).
- Walk around, help students interpret odd results (e.g., skipped entries for O(n²) on huge sizes).

4. (20 min) Small coding activity / extension (paired)
- Options (pick one):
  A) Modify pivot selection in quickSortArray to use median-of-three and re-run benchmarks. Observe differences.
  B) Add a command-line / menu toggle to limit which algorithms are run (e.g., skip bubble/insertion for large sizes).
  C) Implement an in-place merge (advanced) or instrument comparisons differently.
- Students commit small changes to the `week11` branch, push, and open a short PR (or show instructor locally).

5. (5 min) Wrap-up & homework
- Collect plots and answers to the worksheet questions (lab-info/week11/worksheet.md).
- Homework: finish plotting, turn in one-page write-up with plots, answer reflection questions, and include any code changes.

---

## 50-minute condensed version
- 5 min: Setup & quick recap
- 10 min: Mini-lecture (Big-O + trade-offs)
- 15 min: Demo + run menu 28 (Inventory) together
- 15 min: Run menu 27 (array benchmarks) and start plotting (finish as homework)
- 5 min: Wrap-up & assignments

---

## Instructor notes & suggestions
- The array benchmarks now include larger sizes up to 1,000,000 but skip bubble/insertion for sizes > 100k (to avoid extremely long runs). You can change the skip threshold in Game.cpp if you prefer a different cutoff.
- If you want deterministic benchmark inputs, call srand(42) or populate arrays with specific patterns (sorted, reverse-sorted, nearly-sorted) to show algorithm sensitivity to input order.
- If you want me to add an in-class slide deck or printable handout based on this plan, I can generate a short slide outline or a one-page handout and commit it to lab-info/week11.

---

Files updated/created for Week 11 (branch week11):
- dungeongame/src/Game.cpp — added array benchmarks, inventory-run-all-sorts, menu entries
- lab-info/week11/game_lab_activity.md — full lab instructions
- lab-info/week11/lesson-plan.md — (this file) updated for Week 11
- lab-info/week11/worksheet.md — student worksheet
- lab-info/week11/sample_sort_results.csv — example CSV output


If you'd like, I can now:
- Generate a short slide deck (PDF) for the 75-minute lesson,
- Change the O(n²) skip threshold, or
- Make the benchmarks write results automatically to lab-info/week11/last_run_results.csv.

Which of these would you like next?