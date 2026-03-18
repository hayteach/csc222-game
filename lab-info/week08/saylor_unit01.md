# Saylor Unit 1: Algorithm Efficiency
## 1.1: The Importance of Algorithm Efficiency
### Introducing Algorithm Efficiency
https://computerscience.chemeketa.edu/cs160Reader/Algorithms/Efficiency.html

The linked page defines algorithm efficiency as a way to measure and compare
how much "work" an algorithm requires for a problem of size **n**.  Instead of
clock time, it counts primitive steps (moves, turns, loop iterations, etc.)
because the work measure is independent of machine speed or load.  The authors
point out that execution time depends on many variables (machine speed,
background load, input values) and is therefore a poor metric when comparing
algorithms; work required remains constant across platforms.

Two toy examples illustrate the idea.  A `DrawSquare` routine always does ten
steps (pen down, four moves, four turns, pen up), regardless of square size.
A more general `DrawShape` routine repeats a move/turn sequence **x** times; it
uses about `2x+2` steps (or `f(x)=2x+2`) when accounting for pen actions.  The
work grows with the number of sides: a triangle takes 8 units, a pentagon 12,
and a decagon 22.  Even if the accounting method changes (ignore pen up/down,
count loop overhead), the qualitative conclusion stays the same—`DrawShape`
requires more work than `DrawSquare` as **x** increases.  A graph on the page
illustrates these growth curves and reinforces the main takeaway: **growth rate
matters more than absolute counts**.

The page also stresses that any reasonable accounting system yields the same
ordering when comparing algorithms, so students should focus on how work
grows with input size rather than the exact number of steps.




### More on Algorithm Efficiency
The video covers key concepts about Python lists, mutation, dictionaries, function structure, and an introduction to algorithm efficiency.

#### 🔁 Mutable Lists
- Lists can be changed in-place using operations like `append`, deletion, or by assigning to an element.  
- Altering an element (e.g. `ivys[1] = -5`) mutates the existing list object rather than rebinding the variable name.  
- Trying to assign to an index beyond the current length raises an error; use `append` to grow a list.  
- Lists may contain heterogeneous types.  
- Assigning one list to another (e.g. `L2 = L1`) creates an alias: both names refer to the same object. Mutations via either name are visible to the other. Rebinding the variable (e.g. `L1 = []`) breaks the alias.

#### 🔄 Immutables vs. Mutables
- Immutable objects (numbers, strings, tuples) behave differently: `a = 1; b = a; a = 2` does not affect `b` because reassignment creates a new object.

#### 📚 Dictionaries
- Unordered, mutable collections of key–value pairs.  
- Keys can be any immutable type, values can be any type.  
- Access with `d[key]`; missing keys raise `KeyError`.  
- There is no intrinsic ordering; iterating over `d.keys()` yields an arbitrary order.  
- Dictionaries provide constant‑time average lookup via hashing, unlike a linear search on a list of pairs.

#### 🧩 Using Functions for Structure
- Start problem solving with pseudocode to identify modules, data types, control flow, and abstraction boundaries.  
- Example: computing a hypotenuse:
  1. read base and height as floats with validation loops,
  2. calculate `math.sqrt(b**2 + h**2)`,
  3. print result.
- Refactor repeated input‑validation logic into a helper function `get_float(prompt, error_msg)` that loops until a float is entered.  
- Benefits: reduced duplication, clearer code, separation of implementation from usage. Callers need not know how input is obtained or checked.

#### ⏱️ Algorithm Efficiency (Introduction)
- Efficiency matters despite fast hardware because problem sizes grow faster than machine speeds.  
- Measure resources in terms of input size (e.g., list length, integer magnitude) and count basic steps (assume random‑access model and constant‑time primitives).  
- Focus on **worst‑case** time complexity to obtain reliable upper bounds.  
- Conceptually, efficiency is about choosing an appropriate algorithm class rather than inventing a one‑off trick.  
- Future discussions will explore orders of growth and common algorithm families.
This summary replaces the raw transcript to clarify what the instructor discussed in the video.

#### Algorithm Analysis
Read this article for an excellent discussion that ties many pieces together. You need to understand how to determine the resource complexity of an algorithm so that you can make efficient and effective implementation choices. Those choices must be based on all the resources the algorithm uses, including time, memory, data interchange, and hardware, while still meeting functional goals.
How long will it take to process the company payroll once we complete our planned merger? Should I buy a new payroll program from vendor X or vendor Y? If a particular program is slow, is it badly implemented or is it solving a hard problem? Questions like these ask us to consider the difficulty of a problem, or the relative efficiency of two or more approaches to solving a problem.

This chapter introduces the motivation, basic notation, and fundamental techniques of algorithm analysis. We focus on a methodology known as asymptotic algorithm analysis, or simply asymptotic analysis. Asymptotic analysis attempts to estimate the resource consumption of an algorithm. It allows us to compare the relative costs of two or more algorithms for solving the same problem. Asymptotic analysis also gives algorithm designers a tool for estimating whether a proposed solution is likely to meet the resource constraints for a problem before they implement an actual program. After reading this chapter, you should understand

the concept of a growth rate, the rate at which the cost of an algorithm grows as the size of its input grows; 
the concept of upper and lower bounds for a growth rate, and how to estimate these bounds for a simple program, algorithm, or problem; and
the difference between the cost of an algorithm (or program) and the cost of a problem. 
The chapter concludes with a brief discussion of the practical difficulties encountered when empirically measuring the cost of a program, and some principles for code tuning to improve program efficiency.
#### Introduction

### Big-O Analysis
### Space-Time Tradeoff
