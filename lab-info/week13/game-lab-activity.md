# Week 13 Game Lab Activity: Dungeon Graph Search

## Goal
Extend the Dungeon Game with Breadth-First Search (BFS) and Depth-First Search (DFS) so students can explore the game map using graph search algorithms.

This activity uses the existing game code and adds a new lab that demonstrates how BFS and DFS work when searching a dungeon.

## Before You Start
- Confirm the `game/dungeongame` project builds successfully.
- Open `game/dungeongame/include/dungeongame/Game.h` and `game/dungeongame/src/Game.cpp`.
- Find the existing menu and map logic for the Dungeon Game.
- Review `game/lab-info/week13/lesson-plan.md`.

## Step 1: Add the Graph Search Lab Menu
Add a new lab option in the `Game` menu so students can run the search demo from the game.

1. Open `game/dungeongame/include/dungeongame/Game.h`.
2. Add the following new method declarations under the existing lab/demo methods:
   - `void runGraphSearchLab();`
   - `void runBFSPathDemo();`
   - `void runDFSExploreDemo();`
   - `std::vector<Position> breadthFirstSearch(const std::vector<std::string>& map, const Position& start, const Position& goal) const;`
   - `std::vector<Position> depthFirstSearch(const std::vector<std::string>& map, const Position& start, const Position& goal) const;`
   - `std::vector<Position> getNeighbors(const std::vector<std::string>& map, const Position& current) const;`
3. Add a new menu item in the existing Labs menu, for example:
   - `8) Graph Search Demo` or `9) Graph Search Demo` depending on current numbering.

## Step 2: Create the Search Demo Map
Use the existing dungeon map representation and add a small maze for the demo.

The game already has a `map` array and `MAP_WIDTH` / `MAP_HEIGHT` constants.

Example demo map in `Game.cpp`:
```cpp
std::vector<std::string> graphMap = {
    "##########", // top wall row
    "#P..#....#", // P = player start, . = open floor, # = wall
    "#.#.##.#E#", // E = exit tile, graph edges exist between adjacent open tiles
    "#...#....#",
    "##########" // bottom wall row
};
```

Use the map from the current game or convert the existing `map[y][x]` layout into a `std::vector<std::string>` for the demo.

## Step 3: Add the BFS and DFS Helpers
Add the following helper functions in `Game.cpp` with clear comments.

### Get neighbors
```cpp
std::vector<Position> Game::getNeighbors(const std::vector<std::string>& map, const Position& current) const {
    std::vector<Position> neighbors; // stores adjacent open tiles
    const int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // up, down, left, right

    for (int i = 0; i < 4; ++i) {
        int nx = current.x + directions[i][0]; // next x coordinate
        int ny = current.y + directions[i][1]; // next y coordinate

        // Skip positions outside the map bounds.
        if (ny < 0 || ny >= static_cast<int>(map.size())) continue;
        if (nx < 0 || nx >= static_cast<int>(map[ny].size())) continue;

        // Treat '#' as a wall and do not visit it.
        if (map[ny][nx] == '#') continue;

        neighbors.push_back({nx, ny}); // add reachable position
    }

    return neighbors;
}
```

### BFS implementation
```cpp
std::vector<Position> Game::breadthFirstSearch(
    const std::vector<std::string>& map,
    const Position& start,
    const Position& goal
) const {
    int rows = static_cast<int>(map.size());
    int cols = static_cast<int>(map[0].size());

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    // visited[y][x] is true when the tile has already been queued.

    std::vector<std::vector<Position>> parent(rows, std::vector<Position>(cols, {-1, -1}));
    // parent[y][x] stores the previous tile on the path to this tile.

    std::queue<Position> frontier; // BFS queue holds tiles to visit in breadth-first order.
    frontier.push(start); // start searching from the player's position.
    visited[start.y][start.x] = true; // mark the start tile as visited.

    while (!frontier.empty()) {
        Position current = frontier.front(); // examine the next tile in the queue.
        frontier.pop(); // remove it from the queue.

        if (current.x == goal.x && current.y == goal.y) {
            break; // goal reached, stop the search.
        }

        for (const Position& neighbor : getNeighbors(map, current)) {
            if (!visited[neighbor.y][neighbor.x]) {
                visited[neighbor.y][neighbor.x] = true; // mark neighbor as visited.
                parent[neighbor.y][neighbor.x] = current; // remember how we reached it.
                frontier.push(neighbor); // add neighbor to the BFS queue.
            }
        }
    }

    // Reconstruct the path from goal back to start.
    std::vector<Position> path;
    Position step = goal;
    while (!(step.x == -1 && step.y == -1)) {
        path.push_back(step); // add current tile to the final path.
        step = parent[step.y][step.x]; // move to the previous tile.
    }
    std::reverse(path.begin(), path.end()); // reverse so path goes from start to goal.
    return path;
}
```

### DFS implementation
```cpp
std::vector<Position> Game::depthFirstSearch(
    const std::vector<std::string>& map,
    const Position& start,
    const Position& goal
) const {
    int rows = static_cast<int>(map.size());
    int cols = static_cast<int>(map[0].size());

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    // visited[y][x] prevents revisiting the same tile.

    std::vector<Position> path; // stores the current path from the start.
    bool found = false; // true once the goal is reached.

    std::function<void(const Position&)> dfs = [&](const Position& current) {
        if (found) {
            return; // stop further recursion after goal is found.
        }

        visited[current.y][current.x] = true; // mark this tile visited.
        path.push_back(current); // add this tile to the current DFS path.

        if (current.x == goal.x && current.y == goal.y) {
            found = true; // reached the goal.
            return;
        }

        for (const Position& neighbor : getNeighbors(map, current)) {
            if (!visited[neighbor.y][neighbor.x]) {
                dfs(neighbor); // explore this neighbor deeply.
                if (found) {
                    return; // stop exploring other neighbors once goal found.
                }
            }
        }

        if (!found) {
            path.pop_back(); // backtrack from this tile when the goal is not found here.
        }
    };

    dfs(start); // begin recursive DFS from the start position.
    return path; // return the path that reached the goal, if any.
}
```

## Why BFS and DFS?

- **Breadth-First Search (BFS)** explores the map in layers. It checks all tiles one step away from the start before moving to tiles two steps away. This makes BFS ideal when you want the shortest path in a maze or dungeon where all steps cost the same.
- **Depth-First Search (DFS)** follows one path as far as it can go before backtracking. DFS is useful when you want to explore deeply, inspect a branch fully, or quickly find any path to a target.

### When to use each algorithm
- Use **BFS** when you need the shortest route from the player to an exit or goal in an unweighted grid.
- Use **DFS** when you want to explore a region deeply, search for a hidden feature, or when the exact shortest path is not required.

### Game situations for BFS and DFS
- BFS: finding the nearest exit, finding the closest treasure, or exploring the dungeon in a way that minimizes steps.
- DFS: searching a single corridor to the end, checking one branch of a maze, or exploring until a dead end is reached.

## Step 4: Create the Demo Routines
Add three demo methods to the game:
1. `runBFSPathDemo()` should:
   - build or reuse a dungeon map
   - find the nearest exit using BFS
   - display the path step-by-step or print coordinates
2. `runDFSExploreDemo()` should:
   - build the same dungeon map
   - explore the dungeon using DFS
   - show the order in which tiles were visited
3. `runRandomGraphMapDemo()` should:
   - generate a random dungeon map with a guaranteed path from start to exit
   - display the generated map
   - run both BFS and DFS on the same generated map for comparison

## Step 5: Use Existing Game Structures
This lab should reuse the Dungeon Game's current data and menu style.

- Use `player.getPosition()` as the BFS/DFS start position.
- Use `map[y][x]` if the game already stores the dungeon layout in a 2D array.
- Reuse `displayMap()` or create a small helper that prints the demo map and the path.
- Add the new demo in the existing `runLabsMenu()` function so it fits with the current menu flow.

## Step 6: Compare BFS and DFS Behavior
After implementing both demos, run them with the same map and answer these questions:
- Which algorithm reached the exit first?
- Which algorithm produced the shortest path?
- Which algorithm explored more tiles before it stopped?
- What does the `visited` list do in each algorithm?
- How would the result change if the map had more open space?

## Example Student Tasks
1. Add a new `Graph Search Demo` option to the Labs menu.
2. Implement BFS and DFS using the example code.
3. Create a demo dungeon map for graph search.
4. Add a method to display the computed path on the map.
5. Run both demos and record the result.
6. Write a short reflection describing the differences.

## Reflection Questions
- How does BFS choose which tile to explore next?
- How does DFS choose which tile to explore next?
- Why is BFS the best choice for finding the shortest path in an open dungeon?
- Why can DFS be helpful when you want to explore a branch deeply?
- What is one real game feature that could use BFS or DFS?

## Extension Ideas
- Show the path found by BFS on the map as `*` markers.
- Add multiple exits and use BFS to find the closest one.
- Add a second DFS demo that uses an explicit stack instead of recursion.
- Add a ``visited`` map display so students can see which tiles were considered.
- Use the existing inventory or combat features to add a guard patrol search using DFS.
