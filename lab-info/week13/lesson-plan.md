# Week 13 Lesson Plan: Graph Search with BFS and DFS

## Topic
Breadth-First Search (BFS) and Depth-First Search (DFS) for game map exploration.

This lesson uses the CS201 Saylor.org Section 8.2.1 material and applies it directly to the existing Dungeon Game project.

## Learning Objectives
- Explain the difference between BFS and DFS graph traversal.
- Describe why BFS finds the shortest path in an unweighted graph.
- Describe why DFS explores deeply and can be used to search a maze.
- Read and write a C++ implementation of BFS and DFS.
- Apply BFS and DFS to a dungeon map in the game.
- Compare how BFS and DFS behave when searching for an exit or exploring a room.

## Materials
- `game/dungeongame` source code
- `game/dungeongame/include/dungeongame/Game.h`
- `game/dungeongame/src/Game.cpp`
- `game/lab-info/week13/lesson-plan.md`
- `game/lab-info/week13/game-lab-activity.md`

## Preparation
1. Open the `game/dungeongame` project in the editor.
2. Locate the existing `Game` class and the current map display implementation.
3. Confirm the game runs and that the menu system is available.
4. Review the Week 12 menu structure so you can add a new `Graph Search` lab option.

## Agenda
1. Warm-up and definitions (10 minutes)
2. Instructor demo of BFS and DFS on the dungeon map (15 minutes)
3. Student implementation and game lab work (25 minutes)
4. Class discussion and reflection (10 minutes)

## Lesson Flow

### 1. Warm-up and Definitions
- Review graph vocabulary:
  - node / vertex
  - edge
  - queue
  - stack
  - visited set
  - path
- Explain that a dungeon map can be represented as a graph:
  - each open tile is a node
  - each adjacent step between tiles is an edge
- Introduce BFS and DFS at a conceptual level:
  - BFS explores by distance from the start
  - DFS explores by following one branch as far as possible

### 2. Instructor Demo
- Show the existing dungeon map and the player starting position.
- Demonstrate a BFS path to the nearest exit: a short, level-by-level search.
- Demonstrate a DFS exploration from the player: a deep, branch-first search.
- Use the code examples in this lesson to explain each variable and each step.

### 3. Student Work
- Students should follow `game-lab-activity.md` to add the Graph Search lab.
- Have students implement `Game::runGraphSearchLab()` and add menu options.
- Students should use the existing map data and menu system from the game.
- Students should test both BFS and DFS on the dungeon.

### 4. Discussion and Reflection
Ask students:
- Which search strategy found the exit faster?
- Why does BFS find the shortest route in the dungeon?
- Why did DFS sometimes go down a long dead end?
- What is the role of the `visited` array in both algorithms?
- How would you use graph search in a real game feature?

## Example Code
Use these examples as a reference when teaching and implementing the lab.

### BFS Example
```cpp
#include <queue>
#include <vector>

struct Position {
    int x;      // column index in the map grid
    int y;      // row index in the map grid
};

// Return valid neighbors for the current tile.
std::vector<Position> getNeighbors(const std::vector<std::string>& map, const Position& current) {
    std::vector<Position> neighbors; // list of reachable adjacent positions
    const int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // up, down, left, right

    for (int i = 0; i < 4; ++i) {
        int nx = current.x + directions[i][0]; // next x coordinate
        int ny = current.y + directions[i][1]; // next y coordinate

        if (ny < 0 || ny >= static_cast<int>(map.size())) {
            continue; // skip if outside top/bottom bounds
        }
        if (nx < 0 || nx >= static_cast<int>(map[ny].size())) {
            continue; // skip if outside left/right bounds
        }
        if (map[ny][nx] == '#') {
            continue; // skip walls, only open space is allowed
        }

        neighbors.push_back({nx, ny}); // this neighbor is reachable
    }

    return neighbors;
}

std::vector<Position> breadthFirstSearch(
    const std::vector<std::string>& map,
    const Position& start,
    const Position& goal
) {
    int rows = static_cast<int>(map.size());
    int cols = static_cast<int>(map[0].size());

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    // visited[y][x] tracks whether we already added a tile to the queue

    std::vector<std::vector<Position>> parent(rows, std::vector<Position>(cols, {-1, -1}));
    // parent[y][x] stores the previous tile in the discovered path

    std::queue<Position> frontier; // queue for BFS
    frontier.push(start); // begin search from the start tile
    visited[start.y][start.x] = true; // mark start as visited

    while (!frontier.empty()) {
        Position current = frontier.front(); // get the next tile to explore
        frontier.pop(); // remove it from the queue

        if (current.x == goal.x && current.y == goal.y) {
            break; // found the goal, stop searching
        }

        for (const Position& neighbor : getNeighbors(map, current)) {
            if (!visited[neighbor.y][neighbor.x]) {
                visited[neighbor.y][neighbor.x] = true;
                // record where we came from to reconstruct the path later
                parent[neighbor.y][neighbor.x] = current;
                frontier.push(neighbor); // add the neighbor to the BFS queue
            }
        }
    }

    std::vector<Position> path; // path from start to goal
    Position current = goal;
    while (!(current.x == -1 && current.y == -1)) {
        path.push_back(current); // add the current tile to the path
        current = parent[current.y][current.x]; // follow parent pointers backward
    }
    std::reverse(path.begin(), path.end()); // reverse the path to start->goal order
    return path;
}
```

### DFS Example
```cpp
#include <vector>

std::vector<Position> depthFirstSearch(
    const std::vector<std::string>& map,
    const Position& start,
    const Position& goal
) {
    int rows = static_cast<int>(map.size());
    int cols = static_cast<int>(map[0].size());

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    // visited[y][x] ensures we do not visit the same tile twice

    std::vector<Position> path; // stores the current DFS path
    bool found = false; // becomes true when the goal is reached

    std::function<void(const Position&)> dfs = [&](const Position& current) {
        if (found) {
            return; // stop recursion once the goal is found
        }

        visited[current.y][current.x] = true; // mark this tile as visited
        path.push_back(current); // add the current tile to the DFS path

        if (current.x == goal.x && current.y == goal.y) {
            found = true; // goal reached
            return;
        }

        for (const Position& neighbor : getNeighbors(map, current)) {
            if (!visited[neighbor.y][neighbor.x]) {
                dfs(neighbor); // recursively explore the neighbor
                if (found) {
                    return; // stop exploring once the goal is found
                }
            }
        }

        if (!found) {
            path.pop_back(); // backtrack because this branch did not reach the goal
        }
    };

    dfs(start); // start recursive DFS
    return path; // path will contain the route taken when the goal was found
}
```

## Teaching Notes
- Emphasize that the `visited` structure prevents infinite loops on graphs with cycles.
- Show students how the map is a grid representation of a graph.
- Explain the difference between the queue used in BFS and the recursion/stack behavior of DFS.
- Reinforce that BFS is best for shortest paths, and DFS is best for deep exploration.

## In-Game Application Ideas
- Add a `Graph Search` lab option to the game menu.
- Use BFS to find the nearest exit from the player’s current position.
- Use DFS to explore a maze and record the route taken.
- Add a map legend with:
  - `.` open floor
  - `#` wall
  - `E` exit
  - `P` player
- Let students toggle between BFS and DFS to compare search patterns.

## Assessment
- Verify students can explain the role of the queue and the stack/recursion.
- Check that students can trace both algorithms on a sample map.
- Confirm students can apply BFS or DFS to a simple dungeon search task.
- Look for working code that uses existing game structures and adds only the graph search logic.
