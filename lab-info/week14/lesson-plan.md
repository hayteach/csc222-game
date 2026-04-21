# Week 14 Lesson Plan: Shortest Distance and Traveling Salesman

## Topic
Weighted graphs, shortest-path routing, and the Traveling Salesman Problem (TSP).

This week builds on the Week 13 graph search material and adds weighted path planning to the Dungeon Game.

## Learning Objectives
- Explain how weighted graphs differ from unweighted graphs.
- Describe Dijkstra's algorithm for finding the shortest path from a single source.
- Explain how the Traveling Salesman Problem models route optimization.
- Implement a Dijkstra demo in the game that computes the shortest distance from one node to every other node.
- Implement a simple TSP route planner using a nearest-neighbor heuristic.

## Materials
- `game/dungeongame/include/dungeongame/Game.h`
- `game/dungeongame/src/Game.cpp`
- `game/lab-info/week14/lesson-plan.md`
- `game/lab-info/week14/game-lab-activity.md`

## Preparation
1. Open the `game/dungeongame` project in the editor.
2. Locate the existing Week 13 graph search demo code in `Game.cpp`.
3. Review the current Labs menu and confirm the game builds.
4. Open `game/lab-info/week14/game-lab-activity.md` for student instructions.

## Agenda
1. Intro to weighted graphs and path cost (10 minutes)
2. Instructor demo of Dijkstra's algorithm on a sample graph (15 minutes)
3. Student implementation work in the game lab (25 minutes)
4. Class discussion and reflection (10 minutes)

## Lesson Flow

### 1. Weighted Graphs Review
- Define graph elements: nodes, directed edges, and weights.
- Explain that weights represent cost, distance, or difficulty.
- Show the assignment graph and point out the edge weights from node 0 to the other nodes.

### 2. Dijkstra Demonstration
- Introduce Dijkstra's algorithm and explain why it finds the shortest path in a weighted graph with non-negative weights.
- Walk through a small example using the provided graph.
- Show how the game can print the shortest distance from node 0 to all other nodes.

### 3. TSP and Route Planning
- Explain the Traveling Salesman Problem: visit all nodes and return to the start with minimum cost.
- State that exact TSP is hard, so this lab uses a greedy nearest-neighbor approximation.
- Compare TSP route planning with the shortest-path calculation from Dijkstra.

### 4. Student Coding
- Students should add the new Week 14 lab menu option.
- Implement `Game::runDijkstraDistanceDemo()` to compute shortest distances and paths.
- Implement `Game::runTravelingSalesmanDemo()` to build a tour using a nearest-neighbor heuristic.
- Test both demos in the game and observe the output.

### 5. Reflection
Ask students:
- Which path costs were lowest from node 0?
- How did the Dijkstra path differ from the first path a greedy TSP heuristic chose?
- Why is Dijkstra appropriate for shortest-distance problems but not enough for the full TSP?
- What conditions must be true for Dijkstra to work correctly?

## In-Game Application
- Add a new `Shortest Distance Lab` option under the `Labs Menu`.
- Use `runDijkstraDistanceDemo()` to compute and display shortest paths from node 0.
- Use `runTravelingSalesmanDemo()` to show a route through a small set of locations.
- Keep all Week 14 helper methods grouped together and clearly commented in `Game.cpp`.

## Game Scenario
- Frame the lab as a game task: a courier or adventurer needs the shortest route to deliver a potion, reach an objective, or rescue an ally.
- Use Dijkstra to plan the safest, quickest route through a weighted dungeon or road network.
- Use the TSP demo to plan a merchant's tour visiting every village or collecting all artifacts before returning home.
- Explain that path planning is how games choose routes for NPCs, quests, and supply deliveries.

## Assessment
- Verify the game now has a `Shortest Distance Lab` option.
- Confirm Dijkstra output shows a valid path and distance for each reachable node.
- Confirm the TSP demo prints a full tour returning to the start.
- Check student code for clear comments and well-organized Week 14 helper methods.

## Extension Ideas
- Add a second Dijkstra demo that accepts a custom source node.
- Show a map-style visualization of the Dijkstra path on a grid.
- Add a second TSP heuristic using a cheapest insertion strategy.
- Compare the greedy TSP tour with the actual shortest Hamiltonian cycle for a small graph.
