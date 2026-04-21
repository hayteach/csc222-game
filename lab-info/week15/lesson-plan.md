# Week 15 Lesson Plan: Binary Tree Recursion and Single-Parent Nodes

## Topic
Recursive binary tree traversal, node counting, leaf counting, and single-parent detection.

This week builds on data structure recursion and applies it to a game decision tree.

## Learning Objectives
- Explain how a binary tree represents hierarchical game decisions.
- Write recursive functions to count all nodes in a tree.
- Write recursive functions to count leaf nodes.
- Write recursive functions to count nodes with exactly one child.
- Apply these tree counts to a game scenario like a quest decision tree or skill tree.

## Materials
- `game/dungeongame/include/dungeongame/Game.h`
- `game/dungeongame/src/Game.cpp`
- `game/lab-info/week15/lesson-plan.md`
- `game/lab-info/week15/game-lab-activity.md`

## Preparation
1. Open the `game/dungeongame` project in the editor.
2. Locate the Week 14 and Week 13 lab code in `Game.cpp`.
3. Review recursive tree traversal patterns from lecture.
4. Open `game/lab-info/week15/game-lab-activity.md` for student instructions.

## Agenda
1. Review binary tree structure and recursion (10 minutes)
2. Instructor demo of recursive tree counts (15 minutes)
3. Student implementation and game lab work (25 minutes)
4. Reflection and game design discussion (10 minutes)

## Lesson Flow

### 1. Binary Tree Review
- Define binary tree concepts:
  - node
  - left child
  - right child
  - leaf node
  - single-parent node
- Explain how a binary tree can represent a quest decision tree or skill evolution tree.

### 2. Recursive Counting Demo
- Walk through the recursive node counting algorithm.
- Explain the base case for `nullptr`.
- Show how leaf counting checks for both children being absent.
- Show how single-parent counting checks for exactly one child.

### 3. Student Coding
- Have students add the Week 15 binary tree lab menu.
- Implement `runBinaryTreeCountDemo()` and `runBinaryTreeSingleParentDemo()`.
- Build a sample tree in the demo and compute counts.
- Run the game lab and read the output.

### 4. Discussion
Ask students:
- What makes a node a leaf in a binary tree?
- Why does counting nodes naturally use recursion?
- What kind of game decision would produce a single-parent node?
- How could this be used for NPC behavior or quest design?

## In-Game Application
- Add a new `Binary Tree Lab` option under the `Labs Menu`.
- Use `runBinaryTreeCountDemo()` to count total nodes and leaves.
- Use `runBinaryTreeSingleParentDemo()` to count single-parent nodes.
- Frame the tree as a quest decision tree where leaves are final outcomes.

## Game Scenario
- Describe the sample tree as a quest decision tree for a game hero.
- Leaves represent final quest outcomes like victory, escape, or treasure.
- Single-parent nodes represent forced choices or one-way story branches.
- Explain that recursive tree counting helps analyze game decision complexity.

## Game Development Example
Use the sample binary tree to represent a quest-decision system:
- The root node is the opening choice, such as "Enter the haunted castle" or "Travel through the forest." 
- Each left/right child represents a different next action or branch in the story.
- Leaves are final outcomes, for example "defeat the boss," "find the hidden treasure," or "escape safely." 
- A single-parent node models a forced progression point where only one next step is available, such as a locked door or one-way escape tunnel.

This shows students how binary tree analysis helps game developers understand the complexity of branching storylines and decision trees.

## Assessment
- Verify the game has a `Binary Tree Lab` option.
- Confirm the demo prints the total node count and leaf count.
- Confirm the demo prints the number of single-parent nodes.
- Check student code for recursive methods and clear comments.

## Extension Ideas
- Add a tree visualization helper that prints the structure.
- Add a demo that builds a tree from sample input values.
- Use the same tree helpers to compute tree height or depth.
- Compare binary tree counts for different game decision trees.
