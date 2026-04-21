# Week 14 Game Lab Activity: Shortest Distance and Traveling Salesman

## Goal
Extend the Dungeon Game with a Week 14 lab that teaches weighted graph routing.

This lab introduces Dijkstra's shortest-path algorithm and a simple Traveling Salesman Problem heuristic.

## Before You Start
- Make sure the `game/dungeongame` project builds.
- Open `game/dungeongame/include/dungeongame/Game.h` and `game/dungeongame/src/Game.cpp`.
- Review the existing Week 13 graph search demo methods.

## Step 1: Add the new lab menu option
1. Open `Game.h` and add Week 14 method declarations.
2. In `createLabsMenu(bool& done)`, add a new menu option:
   - `8) Shortest Distance Lab`
   - Shift `Back` to `9)`.
3. Implement `Game::runShortestDistanceLab()` in `Game.cpp`.

## Step 2: Implement the Dijkstra demo
1. Add a sample directed weighted graph in `runDijkstraDistanceDemo()`.
2. Use Dijkstra's algorithm to compute the shortest path from node `0` to every other node.
3. Print each reachable node's distance and the path taken.
4. Set the scene as a game mission: node `0` is the player's current location and the other nodes are quest locations or supply points with travel costs.
5. Use the example graph below:
   - `0 -> 1 (2)`
   - `0 -> 2 (4)`
   - `0 -> 3 (6)`
   - `1 -> 2 (5)`
   - `1 -> 4 (3)`
   - `2 -> 3 (1)`
   - `2 -> 4 (2)`
   - `3 -> 2 (2)`
   - `3 -> 5 (3)`
   - `4 -> 5 (5)`
   - `4 -> 6 (1)`
   - `5 -> 6 (2)`

## Step 3: Add TSP route-planning support
1. Implement `runTravelingSalesmanDemo()`.
2. Build a small complete weighted distance matrix.
3. Use a nearest-neighbor heuristic to choose the next closest unvisited node.
4. Return to the starting node and print the full tour cost.

## Step 4: Keep Week 14 helpers together
In `Game.cpp`, place all Week 14 route-planning methods in the same area with a clear comment block, for example:
- `runShortestDistanceLab()`
- `computeDijkstraDistances()`
- `reconstructPath()`
- `solveTSPNearestNeighbor()`
- `runDijkstraDistanceDemo()`
- `runTravelingSalesmanDemo()`

## Game Scenario
- Make the lab feel like a real game mission.
- In `runDijkstraDistanceDemo()`, describe the source node as the player's current position and other nodes as destinations with travel cost.
- In `runTravelingSalesmanDemo()`, describe the route as a merchant or adventurer visiting all required waypoints and returning home.
- Encourage students to explain how this would help NPC path planning or quest routing in a real game.

## Step 5: Test the lab
1. Build and run the game.
2. Open `Labs Menu` and select `Shortest Distance Lab`.
3. Run both the Dijkstra demo and the Traveling Salesman challenge.
4. Verify the output shows:
   - shortest distances from node `0` to all reachable nodes
   - the path for each computed shortest route
   - a tour through all TSP nodes returning to the start

## Notes for students
- Dijkstra is used when you want the shortest cost to each destination.
- The Traveling Salesman heuristic approximates a route that visits all nodes.
- This lab demonstrates the difference between exact shortest-path routing and route planning for multiple stops.

## Reflection
- How does Dijkstra use the current shortest distance to choose the next node?
- Why is the nearest-neighbor TSP route only an approximation?
- What would happen if some edges had weight `0` or negative values?
- How can you use weighted graph routing in a game?
