# Week 15 Game Lab Activity: Binary Tree Recursion

## Goal
Add a Week 15 lab that teaches recursive binary tree traversal through a game decision tree example.

This lab uses binary tree recursion to count nodes, leaves, and single-parent nodes.

## Before You Start
- Make sure the `game/dungeongame` project builds.
- Open `game/dungeongame/include/dungeongame/Game.h` and `game/dungeongame/src/Game.cpp`.
- Review the existing Week 14 and Week 13 lab methods.

## Step 1: Add the new lab menu option
1. Open `Game.h` and add Week 15 method declarations.
2. In `createLabsMenu(bool& done)`, add a new menu option:
   - `9) Binary Tree Lab`
   - Shift `Back` to `10)`.
3. Implement `Game::runBinaryTreeLab()` in `Game.cpp`.

## Step 2: Implement the binary tree helper methods
1. Add a simple `BinaryTreeNode` type inside `Game`.
2. Add recursive methods:
   - `countTreeNodes()`
   - `countTreeLeaves()`
   - `countSingleParentNodes()`
3. Create a small sample tree in the demo methods to exercise the recursion.

## Step 3: Create the Node & Leaf Count Demo
1. Implement `runBinaryTreeCountDemo()`.
2. Build a sample tree that represents a quest decision tree.
3. Print:
   - total node count
   - total leaf count
4. Explain the game meaning of leaves as final outcomes.

## Step 4: Create the Single-Parent Demo
1. Implement `runBinaryTreeSingleParentDemo()`.
2. Reuse the sample tree.
3. Count nodes that have exactly one child.
4. Explain how these nodes represent one-way story branches or forced decisions.

## Step 5: Keep Week 15 helpers together
In `Game.cpp`, place all Week 15 binary tree methods in the same area with one comment block, for example:
- `runBinaryTreeLab()`
- `createSampleBinaryTree()`
- `deleteBinaryTree()`
- `countTreeNodes()`
- `countTreeLeaves()`
- `countSingleParentNodes()`
- `runBinaryTreeCountDemo()`
- `runBinaryTreeSingleParentDemo()`

## Step 6: Test the lab
1. Build and run the game.
2. Open `Labs Menu` and select `Binary Tree Lab`.
3. Run both the Node & Leaf Count Demo and the Single-Parent Node Demo.
4. Verify the output is clear and explains the game scenario.

## Notes for students
- Recursive tree methods are a natural match for binary trees.
- Leaf nodes often correspond to final outcomes in a story or game event.
- Single-parent nodes represent a branch where only one next step is possible.
- This lab shows how tree analysis can support game decision design.

## Game Development Example
The sample tree in this lab represents a game decision tree:
- The root node is the first choice, like "accept the quest" or "explore the ruins." 
- Internal nodes are branching decisions, such as "search left" or "search right." 
- Leaf nodes are endings such as "treasure found," "enemy defeated," or "character retreats." 
- Single-parent nodes represent forced progression, such as a one-way path or a required story event.

Students should be able to describe how this relates to branching quests, skill trees, and NPC decision trees in actual game development.

## Reflection
- Why does the node count method need to visit both left and right subtrees?
- How does the leaf count method know when it reached a final outcome?
- What makes a node a "single-parent" node?
- How can counting these nodes help a game designer evaluate a quest tree?
