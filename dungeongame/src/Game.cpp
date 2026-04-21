/* File: Game.cpp
    Name: CSC 222 Students
    Date: 01/28/2026
    Last Edit: 01/28/2026
    Course: CSC 222 - Programming and Algorithms II
    Desc: Game class implementation for the Dungeon of Data Structures game.
    Usage: Compile and run the program to start the game.
  
    Other files required: Character.h, Player.h, Game.h,
                              Character.cpp, Player.cpp, NPC.cpp, NPC.h
*/
#include "Game.h"
#include "NPC.h"
#include "NPCSpawner.h"
#include "ActionHistory.h"
#include "SpellEvaluator.h"

#include <algorithm>
#include <cmath>
#include <cctype>
#include <chrono>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

namespace dungeongame {

Game::Game()
    : running(true), player("Adventurer") {
    // Optional: load inventory items from a file at startup
    loadInventoryFromFile("data/inventory.txt");

    initMap();
    placePlayerOnMap();
    initializeGrimoire();
}

void Game::loadInventoryFromFile(const std::string& path) {
    // Try both the provided path and a project-relative path so the game can be
    // run from either the repo root or the `dungeongame/` folder.
    std::ifstream in(path);
    std::string actualPath = path;
    if (!in) {
        std::string altPath = "dungeongame/" + path;
        in.open(altPath);
        if (in) {
            actualPath = altPath;
        }
    }

    if (!in) {
        cout << "(No inventory file found at '" << path << "' or 'dungeongame/" << path
             << "'. Starting with empty inventory.)\n";
        return;
    }

    cout << "Loading inventory from file: " << actualPath << "\n";
    std::string line;
    int loaded = 0;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        std::string name;
        if (!std::getline(ss, name, ',')) continue;
        std::string valueStr;
        if (!std::getline(ss, valueStr)) continue;
        int value = 0;
        try {
            value = std::stoi(valueStr);
        } catch (...) {
            // ignore malformed lines
            continue;
        }
        player.addItem(Item(name, value));
        loaded++;
    }

    cout << "  Loaded " << loaded << " item(s) into inventory.\n";
}

void Game::initMap() {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            map[y][x] = '.'; // empty floor
        }
    }
}

void Game::placePlayerOnMap() {
    // reset previous positions every time
    initMap();
    Position p = player.getPosition();
    map[p.y][p.x] = 'P';
}

void Game::displayMap() const {
    cout << "Map:\n";
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            cout << map[y][x] << ' ';
        }
        cout << '\n';
    }
}

void Game::displayMenu() {
    auto menu = createMainMenu();
    dungeongame::displayMenu(menu);
}

void Game::processChoice(int choice) {
    auto menu = createMainMenu();
    dungeongame::dispatchMenuChoice(menu, choice);
    placePlayerOnMap();
}

MenuScreen Game::createMainMenu() {
    return MenuScreen{
        "Main Menu",
        {
            {1, "Move Up", [this] { movePlayer(0, -1); }},
            {2, "Move Down", [this] { movePlayer(0, 1); }},
            {3, "Move Left", [this] { movePlayer(-1, 0); }},
            {4, "Move Right", [this] { movePlayer(1, 0); }},
            {5, "Show Stats", [this] { player.displayStats(); }},
            {6, "Inventory", [this] { runInventoryMenu(); }},
            {7, "Demos", [this] { runDemosMenu(); }},
            {8, "Labs", [this] { runLabsMenu(); }},
            {9, "View Grimoire", [this] { viewGrimoire(); }},
            {10, "Quit", [this] { const_cast<Game*>(this)->running = false; }}
        }
    };
}

MenuScreen Game::createInventoryMenu(bool& done) {
    return MenuScreen{
        "Inventory Menu",
        {
            {1, "Show Inventory", [this] { player.showInventory(); }},
            {2, "Use Potion", [this] {
                int prevH = player.getHealth();
                Item used;
                int healAmt = 0;
                if (!player.usePotionAndGet(used, healAmt)) {
                    std::cout << "No potions available." << std::endl;
                } else {
                    history.pushUsePotion(used, prevH);
                }
            }},
            {3, "Pick Item", [this] { handlePickItem(); }},
            {4, "Drop Item", [this] { handleDropItem(); }},
            {5, "Back", [&done] { done = true; }}
        }
    };
}

MenuScreen Game::createDemosMenu(bool& done) {
    return MenuScreen{
        "Demos Menu",
        {
            {1, "Encounter Enemy", [this] {
                NPC goblin("Goblin", 10, 3, 0, 10, 5);
                std::cout << "You encounter a Goblin!" << std::endl;
                processCombat(goblin);
            }},
            {2, "Potions Demo", [this] { runPointersDemo(); }},
            {3, "Linked List Demo", [this] { runLinkedListDemo(); }},
            {4, "NPC Group Demo", [this] { runNPCGroupDemo(); }},
            {5, "NPC Spawner Demo", [this] { runNPCSpawnerDemo(); }},
            {6, "Show Spawn Queue", [this] { showSpawnQueue(); }},
            {7, "Show History", [this] { showActionHistory(); }},
            {8, "Back", [&done] { done = true; }}
        }
    };
}

MenuScreen Game::createLabsMenu(bool& done) {
    return MenuScreen{
        "Labs Menu",
        {
            {1, "Sort/Search Demo", [this] { runSortSearchDemo(); }},
            {2, "Compare Sorts", [this] { runSortCompareDemo(); }},
            {3, "Benchmarks", [this] { runArraySortBenchmarks(); }},
            {4, "Inventory Sort Demo", [this] { runSortInventoryAllDemo(); }},
            {5, "Student Tests", [this] { runStudentSortTests(); }},
            {6, "Hashing Challenge", [this] { runHashingLab(); }},
            {7, "Graph Search Demo", [this] { runGraphSearchLab(); }},
            {8, "Shortest Distance Lab", [this] { runShortestDistanceLab(); }},
            {9, "Back", [&done] { done = true; }}
        }
    };
}

void Game::runMenuScreen(const std::function<MenuScreen(bool&)>& buildMenu) {
    bool done = false;
    while (!done) {
        auto menu = buildMenu(done);
        dungeongame::displayMenu(menu);
        int choice = dungeongame::promptMenuChoice();
        dungeongame::dispatchMenuChoice(menu, choice);
    }
}

void Game::runInventoryMenu() {
    runMenuScreen([this](bool& done) { return createInventoryMenu(done); });
}

void Game::runDemosMenu() {
    runMenuScreen([this](bool& done) { return createDemosMenu(done); });
}

void Game::runLabsMenu() {
    runMenuScreen([this](bool& done) { return createLabsMenu(done); });
}

// Week 13 Graph Search Lab
// These methods were added for the Week 13 lesson to demonstrate BFS and DFS
// exploration inside the dungeon game using a small demo map.
//
// BFS explores the dungeon by visiting nearby tiles first and is best when
// the goal is to find the shortest path in an unweighted grid.
// DFS explores one branch as deeply as possible and is useful when the goal
// is to investigate a path or search until a dead end.
void Game::runGraphSearchLab() {
    bool done = false;
    while (!done) {
        MenuScreen menu{
            "Graph Search Lab",
            {
                {1, "BFS Path Demo", [this] { runBFSPathDemo(); }},
                {2, "DFS Explore Demo", [this] { runDFSExploreDemo(); }},
                {3, "Random Graph Search Demo", [this] { runRandomGraphMapDemo(); }},
                {4, "Back", [&done] { done = true; }}
            }
        };
        dungeongame::displayMenu(menu);
        int choice = dungeongame::promptMenuChoice();
        dungeongame::dispatchMenuChoice(menu, choice);
    }
}

std::vector<Position> Game::getNeighbors(const std::vector<std::string>& map, const Position& current) const {
    std::vector<Position> neighbors;
    const int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    for (int i = 0; i < 4; ++i) {
        int nx = current.x + directions[i][0];
        int ny = current.y + directions[i][1];

        if (ny < 0 || ny >= static_cast<int>(map.size())) continue;
        if (nx < 0 || nx >= static_cast<int>(map[ny].size())) continue;
        if (map[ny][nx] == '#') continue;

        neighbors.push_back({nx, ny});
    }

    return neighbors;
}

std::vector<Position> Game::breadthFirstSearch(const std::vector<std::string>& map, const Position& start, const Position& goal) const {
    int rows = static_cast<int>(map.size());
    int cols = static_cast<int>(map[0].size());

    // BFS uses a queue so it explores all tiles at one distance before moving
    // to tiles that are farther away. This guarantees the first path found to
    // the goal is the shortest path in an unweighted grid.
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<Position>> parent(rows, std::vector<Position>(cols, {-1, -1}));
    std::queue<Position> frontier;

    frontier.push(start);
    visited[start.y][start.x] = true;

    while (!frontier.empty()) {
        Position current = frontier.front();
        frontier.pop();

        if (current.x == goal.x && current.y == goal.y) {
            break;
        }

        for (const Position& neighbor : getNeighbors(map, current)) {
            if (!visited[neighbor.y][neighbor.x]) {
                visited[neighbor.y][neighbor.x] = true;
                parent[neighbor.y][neighbor.x] = current;
                frontier.push(neighbor);
            }
        }
    }

    if (!visited[goal.y][goal.x]) {
        return {};
    }

    std::vector<Position> path;
    Position current = goal;
    while (!(current.x == -1 && current.y == -1)) {
        path.push_back(current);
        current = parent[current.y][current.x];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Position> Game::depthFirstSearch(const std::vector<std::string>& map, const Position& start, const Position& goal) const {
    int rows = static_cast<int>(map.size());
    int cols = static_cast<int>(map[0].size());

    // DFS uses recursion (a stack) to explore one branch deeply before moving to
    // another branch. It is useful for exploring a maze or searching for any path
    // to the goal, even when it is not the shortest path.
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<Position> path;
    bool found = false;

    std::function<void(const Position&)> dfs = [&](const Position& current) {
        if (found) {
            return;
        }

        visited[current.y][current.x] = true;
        path.push_back(current);

        if (current.x == goal.x && current.y == goal.y) {
            found = true;
            return;
        }

        for (const Position& neighbor : getNeighbors(map, current)) {
            if (!visited[neighbor.y][neighbor.x]) {
                dfs(neighbor);
                if (found) {
                    return;
                }
            }
        }

        if (!found) {
            path.pop_back();
        }
    };

    dfs(start);
    return found ? path : std::vector<Position>{};
}

void Game::runBFSPathDemo() {
    // This demo uses BFS to find the shortest path from P to E.
    // BFS explores the dungeon evenly, so the first path found is the shortest.
    // The map below contains an open route around the wall barrier.
    std::vector<std::string> graphMap = {
        "##########",
        "#P..#...E#",
        "#.#....#.#",
        "#...#....#",
        "##########"
    };

    Position start{-1, -1};
    Position goal{-1, -1};
    for (int y = 0; y < static_cast<int>(graphMap.size()); ++y) {
        for (int x = 0; x < static_cast<int>(graphMap[y].size()); ++x) {
            if (graphMap[y][x] == 'P') {
                start = {x, y};
            }
            if (graphMap[y][x] == 'E') {
                goal = {x, y};
            }
        }
    }

    if (start.x == -1 || goal.x == -1) {
        cout << "Could not locate start or exit on the demo map." << endl;
        return;
    }

    std::vector<Position> path = breadthFirstSearch(graphMap, start, goal);
    if (path.empty()) {
        cout << "BFS did not find a path to the exit." << endl;
        return;
    }

    std::vector<std::string> displayMap = graphMap;
    for (const Position& step : path) {
        if (displayMap[step.y][step.x] == '.') {
            displayMap[step.y][step.x] = '*';
        }
    }

    cout << "\n--- BFS Path Demo ---" << endl;
    cout << "Path length: " << path.size() << " steps" << endl;
    cout << "BFS visited the shortest path from P to E." << endl;
    for (const std::string& row : displayMap) {
        cout << row << endl;
    }
    cout << "Path coordinates:" << endl;
    for (const Position& step : path) {
        cout << "  (" << step.x << ", " << step.y << ")" << endl;
    }
}

void Game::runDFSExploreDemo() {
    // This demo uses DFS to explore one branch deeply and find a path to E.
    // DFS is useful for exploring a maze or walking down corridors to a dead end.
    // The same reachable map is used here so students can compare the two algorithms.
    std::vector<std::string> graphMap = {
        "##########",
        "#P..#...E#",
        "#.#....#.#",
        "#...#....#",
        "##########"
    };

    Position start{-1, -1};
    Position goal{-1, -1};
    for (int y = 0; y < static_cast<int>(graphMap.size()); ++y) {
        for (int x = 0; x < static_cast<int>(graphMap[y].size()); ++x) {
            if (graphMap[y][x] == 'P') {
                start = {x, y};
            }
            if (graphMap[y][x] == 'E') {
                goal = {x, y};
            }
        }
    }

    if (start.x == -1 || goal.x == -1) {
        cout << "Could not locate start or exit on the demo map." << endl;
        return;
    }

    std::vector<Position> path = depthFirstSearch(graphMap, start, goal);
    if (path.empty()) {
        cout << "DFS did not find a path to the exit." << endl;
        return;
    }

    std::vector<std::string> displayMap = graphMap;
    for (const Position& step : path) {
        if (displayMap[step.y][step.x] == '.') {
            displayMap[step.y][step.x] = '*';
        }
    }

    cout << "\n--- DFS Explore Demo ---" << endl;
    cout << "DFS exploration path length: " << path.size() << " steps" << endl;
    cout << "DFS followed one branch deeply until the exit was found." << endl;
    for (const std::string& row : displayMap) {
        cout << row << endl;
    }
    cout << "Path coordinates:" << endl;
    for (const Position& step : path) {
        cout << "  (" << step.x << ", " << step.y << ")" << endl;
    }
}

std::vector<std::string> Game::createRandomGraphMap(int rows, int cols, Position& start, Position& goal, int openChance) const {
    std::vector<std::string> map(rows, std::string(cols, '#'));

    start = {1, 1};
    goal = {cols - 2, rows - 2};
    int x = start.x;
    int y = start.y;
    map[y][x] = 'P';

    // Carve one guaranteed path between P and E.
    while (x != goal.x || y != goal.y) {
        bool moveHoriz;
        if (x == goal.x) {
            moveHoriz = false;
        } else if (y == goal.y) {
            moveHoriz = true;
        } else {
            moveHoriz = (rand() % 2) == 0;
        }

        if (moveHoriz) {
            x += (goal.x > x ? 1 : -1);
        } else {
            y += (goal.y > y ? 1 : -1);
        }

        map[y][x] = '.';
    }
    map[goal.y][goal.x] = 'E';
    map[start.y][start.x] = 'P';

    // Randomly open additional floor spaces while preserving the guaranteed path.
    for (int row = 1; row < rows - 1; ++row) {
        for (int col = 1; col < cols - 1; ++col) {
            if (map[row][col] == '#') {
                if ((rand() % 100) < openChance) {
                    map[row][col] = '.';
                }
            }
        }
    }

    // Protect path endpoints.
    map[start.y][start.x] = 'P';
    map[goal.y][goal.x] = 'E';

    return map;
}

void Game::runRandomGraphMapDemo() {
    Position start{-1, -1};
    Position goal{-1, -1};
    std::vector<std::string> graphMap = createRandomGraphMap(9, 19, start, goal, 35);

    cout << "\n--- Random Graph Search Demo ---" << endl;
    cout << "Generated random dungeon map with a guaranteed path from P to E." << endl;
    for (const std::string& row : graphMap) {
        cout << row << endl;
    }

    auto bfsPath = breadthFirstSearch(graphMap, start, goal);
    auto dfsPath = depthFirstSearch(graphMap, start, goal);

    if (bfsPath.empty() || dfsPath.empty()) {
        cout << "Error: generated map is unexpectedly unreachable. Try again." << endl;
        return;
    }

    std::vector<std::string> bfsMap = graphMap;
    for (const Position& step : bfsPath) {
        if (bfsMap[step.y][step.x] == '.') {
            bfsMap[step.y][step.x] = '*';
        }
    }

    cout << "\nBFS path (shortest path):" << endl;
    for (const std::string& row : bfsMap) {
        cout << row << endl;
    }
    cout << "BFS path length: " << bfsPath.size() << " steps" << endl;

    std::vector<std::string> dfsMap = graphMap;
    for (const Position& step : dfsPath) {
        if (dfsMap[step.y][step.x] == '.') {
            dfsMap[step.y][step.x] = '+';
        }
    }

    cout << "\nDFS path (first found path):" << endl;
    for (const std::string& row : dfsMap) {
        cout << row << endl;
    }
    cout << "DFS path length: " << dfsPath.size() << " steps" << endl;

    cout << "\nNote: BFS finds the shortest route, while DFS finds a path by exploring one branch deeply." << endl;
}

// Week 14 shortest-distance / traveling salesman lab
// These methods were added for Week 14 to demonstrate weighted graph
// route planning with Dijkstra's shortest path and a simple Traveling Salesman
// nearest-neighbor heuristic.
void Game::runShortestDistanceLab() {
    bool done = false;
    while (!done) {
        MenuScreen menu{
            "Week 14 Shortest Distance Lab",
            {
                {1, "Dijkstra Shortest Distances", [this] { runDijkstraDistanceDemo(); }},
                {2, "Traveling Salesman Challenge", [this] { runTravelingSalesmanDemo(); }},
                {3, "Back", [&done] { done = true; }}
            }
        };
        dungeongame::displayMenu(menu);
        int choice = dungeongame::promptMenuChoice();
        dungeongame::dispatchMenuChoice(menu, choice);
    }
}

std::vector<int> Game::computeDijkstraDistances(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& prev) const {
    const int INF = std::numeric_limits<int>::max() / 4;
    int n = static_cast<int>(graph.size());
    std::vector<int> dist(n, INF);
    prev.assign(n, -1);
    std::vector<bool> visited(n, false);

    dist[start] = 0;
    for (int step = 0; step < n; ++step) {
        int node = -1;
        int best = INF;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && dist[i] < best) {
                best = dist[i];
                node = i;
            }
        }

        if (node == -1) {
            break;
        }

        visited[node] = true;
        for (int neighbor = 0; neighbor < n; ++neighbor) {
            int weight = graph[node][neighbor];
            if (weight > 0 && !visited[neighbor]) {
                int candidate = dist[node] + weight;
                if (candidate < dist[neighbor]) {
                    dist[neighbor] = candidate;
                    prev[neighbor] = node;
                }
            }
        }
    }

    return dist;
}

std::vector<int> Game::reconstructPath(int goal, const std::vector<int>& prev) const {
    std::vector<int> path;
    for (int current = goal; current != -1; current = prev[current]) {
        path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> Game::solveTSPNearestNeighbor(const std::vector<std::vector<int>>& distances, int start) const {
    int n = static_cast<int>(distances.size());
    const int INF = std::numeric_limits<int>::max() / 4;
    std::vector<bool> visited(n, false);
    std::vector<int> path;

    int current = start;
    visited[current] = true;
    path.push_back(current);

    for (int step = 1; step < n; ++step) {
        int nextNode = -1;
        int bestWeight = INF;

        for (int candidate = 0; candidate < n; ++candidate) {
            if (!visited[candidate] && distances[current][candidate] > 0 && distances[current][candidate] < bestWeight) {
                bestWeight = distances[current][candidate];
                nextNode = candidate;
            }
        }

        if (nextNode == -1) {
            return {};
        }

        visited[nextNode] = true;
        path.push_back(nextNode);
        current = nextNode;
    }

    if (distances[current][start] <= 0) {
        return {};
    }

    path.push_back(start);
    return path;
}

void Game::runDijkstraDistanceDemo() {
    std::vector<std::vector<int>> graph = {
        {0, 2, 4, 6, 0, 0, 0},
        {0, 0, 5, 0, 3, 0, 0},
        {0, 0, 0, 1, 2, 0, 0},
        {0, 0, 2, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 5, 1},
        {0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0}
    };

    int source = 0;
    std::vector<int> prev;
    std::vector<int> distances = computeDijkstraDistances(graph, source, prev);
    const int INF = std::numeric_limits<int>::max() / 4;

    cout << "\n--- Week 14 Shortest Distance Lab: Dijkstra Demo ---" << endl;
    cout << "This scenario models a game courier planning the fastest route to reach quest locations." << endl;
    cout << "Graph edges (directed):" << endl;
    for (int i = 0; i < static_cast<int>(graph.size()); ++i) {
        for (int j = 0; j < static_cast<int>(graph[i].size()); ++j) {
            if (graph[i][j] > 0) {
                cout << "  " << i << " -> " << j << " (weight " << graph[i][j] << ")" << endl;
            }
        }
    }

    cout << "\nShortest distance from node " << source << " to every other node:" << endl;
    for (int target = 0; target < static_cast<int>(graph.size()); ++target) {
        if (target == source) {
            continue;
        }

        if (distances[target] >= INF) {
            cout << "  Node " << target << " is unreachable." << endl;
            continue;
        }

        std::vector<int> path = reconstructPath(target, prev);
        cout << "  To " << target << ": distance = " << distances[target] << ", path = ";
        for (int i = 0; i < static_cast<int>(path.size()); ++i) {
            if (i > 0) cout << " -> ";
            cout << path[i];
        }
        cout << endl;
    }
}

void Game::runTravelingSalesmanDemo() {
    std::vector<std::vector<int>> distances = {
        {0, 2, 9, 10, 7},
        {2, 0, 6, 4, 3},
        {9, 6, 0, 8, 5},
        {10, 4, 8, 0, 1},
        {7, 3, 5, 1, 0}
    };

    int start = 0;
    std::vector<int> tour = solveTSPNearestNeighbor(distances, start);

    cout << "\n--- Week 14 Traveling Salesman Challenge ---" << endl;
    cout << "This scenario models an adventurer or merchant visiting all required locations" << endl;
    cout << "and then returning home with the shortest possible route." << endl;
    cout << "\nDistance matrix:" << endl;
    for (int i = 0; i < static_cast<int>(distances.size()); ++i) {
        cout << "  ";
        for (int j = 0; j < static_cast<int>(distances[i].size()); ++j) {
            cout << distances[i][j] << (j + 1 < static_cast<int>(distances[i].size()) ? " ": "");
        }
        cout << endl;
    }

    if (tour.empty()) {
        cout << "No complete TSP tour could be found with the current heuristic." << endl;
        return;
    }

    int totalDistance = 0;
    for (int i = 1; i < static_cast<int>(tour.size()); ++i) {
        int from = tour[i - 1];
        int to = tour[i];
        totalDistance += distances[from][to];
    }

    cout << "\nTraveling Salesman tour starting at node " << start << ":" << endl;
    for (int i = 0; i < static_cast<int>(tour.size()); ++i) {
        if (i > 0) cout << " -> ";
        cout << tour[i];
    }
    cout << "\nTotal tour distance: " << totalDistance << endl;
    cout << "This route approximates the TSP with a greedy nearest-neighbor strategy." << endl;
}
// End of Week 14 lab methods.

void Game::movePlayer(int dx, int dy) {
    Position prev = player.getPosition();
    player.move(dx, dy);
    history.pushMove(prev);
}

void Game::processCombat(NPC& enemy) {
    // simple turn-based loop
    while (player.isAlive() && enemy.isAlive()) {
        cout << "\n--- Combat ---" << endl;
        player.displayStats();
        enemy.displayStats();

        cout << "Choose action: 1) Attack  2) Flee\n";
        int action = 0;
        if (!(cin >> action)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number." << endl;
            continue;
        }

        if (action == 1) {
            int atk = player.calculateAttack();
            int damage = atk - enemy.getDefense();
            if (damage < 1) damage = 1;
            cout << "You hit the " << enemy.getName() << " for " << damage << " damage." << endl;
            enemy.takeDamage(damage);
            if (!enemy.isAlive()) {
                cout << "You defeated the " << enemy.getName() << "!" << endl;
                player.gainExperience(enemy.getExpReward());
                player.addGold(enemy.getGoldReward());
                
                // Create and add loot to the loot bag
                int lootValue = 10 + (rand() % 30);
                Item loot(enemy.getName() + " Loot", lootValue);
                lootBag.add(loot);
                cout << "  *** " << loot.name << " (value: " << loot.value << ") dropped into loot bag! ***" << endl;
                
                break;
            }
            // enemy retaliates
            int eatk = enemy.calculateAttack();
            int edamage = eatk - player.getDefense();
            if (edamage < 1) edamage = 1;
            cout << "The " << enemy.getName() << " hits you for " << edamage << " damage." << endl;
            player.takeDamage(edamage);
            if (!player.isAlive()) {
                cout << "You have been defeated..." << endl;
                running = false;
                break;
            }
        } else if (action == 2) {
            // 50% chance to flee
            if (rand() % 2 == 0) {
                cout << "You fled successfully." << endl;
                break;
            } else {
                cout << "Flee failed! The " << enemy.getName() << " attacks." << endl;
                int eatk = enemy.calculateAttack();
                int edamage = eatk - player.getDefense();
                if (edamage < 1) edamage = 1;
                cout << "The " << enemy.getName() << " hits you for " << edamage << " damage." << endl;
                player.takeDamage(edamage);
                if (!player.isAlive()) {
                    cout << "You have been defeated..." << endl;
                    running = false;
                    break;
                }
            }
        } else {
            cout << "Invalid action." << endl;
        }
    }
}

void Game::runPointersDemo() {
    cout << "\n--- Potions Prep (Pointers Demo) ---" << endl;
    cout << "How many potions would you like to prepare? ";
    int potionNum;
    if (!(cin >> potionNum) || potionNum <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input; defaulting to 5." << endl;
        potionNum = 5;
    }

    int* iptr = &potionNum;
    cout << "potionNum value: " << potionNum << '\n';
    cout << "iptr address: " << static_cast<const void*>(iptr) << '\n';
    cout << "*iptr value: " << *iptr << "\n\n";

    // Manipulate potionNum through its pointer (demonstrates inspecting/modifying via pointer)
    cout << "Incrementing potionNum via iptr...\n";
    (*iptr)++;
    cout << "potionNum after increment: " << potionNum << "\n\n";

    // Dynamic integer array allocated using the (possibly updated) potionNum
    int* myArray = new int[potionNum];
    for (int i = 0; i < potionNum; ++i) myArray[i] = i + 1;

    cout << "Array values (direct indexing): ";
    for (int i = 0; i < potionNum; ++i) cout << myArray[i] << (i + 1 == potionNum ? '\n' : ' ');

    int* ptrToMyArray = myArray;
    cout << "Enhancing potions via pointer arithmetic (multiply values by 10)...\n";
    for (int i = 0; i < potionNum; ++i) *(ptrToMyArray + i) *= 10;

    cout << "Array values (via pointer ptrToMyArray): ";
    for (int i = 0; i < potionNum; ++i) cout << *(ptrToMyArray + i) << (i + 1 == potionNum ? '\n' : ' ');

    // Transfer dynamic array items into the player's Inventory (player owns potions now)
    for (int i = 0; i < potionNum; ++i) {
        player.addItem(Item("Potion #" + to_string(i + 1), myArray[i]));
    }

    // Free manually-allocated array
    delete[] myArray;
    cout << "Manual delete[] called. All dynamically allocated memory released.\n\n";

    cout << "Added " << potionNum << " potions to your inventory. Use 'Show Inventory' and 'Use Potion' from the main menu.\n";

}

void Game::runLinkedListDemo() {
    cout << "\n--- Linked List Demo (Template Class) ---" << endl;
    cout << "This demo shows how to use a template class for a generic linked list." << endl;
    cout << "We'll create linked lists of different types and demonstrate operations." << endl;

    // Demo 1: Linked list of integers
    cout << "\n1. Creating a linked list of integers:" << endl;
    LinkedList<int> intList;
    intList.append(10);
    intList.append(20);
    intList.append(30);
    cout << "Added 10, 20, 30: ";
    intList.print();

    cout << "Prepending 5: ";
    intList.prepend(5);
    intList.print();

    cout << "Size: " << intList.size() << endl;
    cout << "Element at index 2: " << intList.get(2) << endl;

    // Demo 2: Linked list of strings
    cout << "\n2. Creating a linked list of strings:" << endl;
    LinkedList<std::string> stringList;
    stringList.append("Hello");
    stringList.append("Template");
    stringList.append("World");
    cout << "Added 'Hello', 'Template', 'World': ";
    stringList.print();

    // Demo 3: Linked list of custom objects (Items)
    cout << "\n3. Creating a linked list of Items (custom objects):" << endl;
    LinkedList<Item> itemList;
    itemList.append(Item("Sword", 100));
    itemList.append(Item("Shield", 80));
    itemList.append(Item("Potion", 25));
    cout << "Added Sword ($100), Shield ($80), Potion ($25):" << endl;
    cout << "Linked list contents:" << endl;
    for (size_t i = 0; i < itemList.size(); ++i) {
        const Item& item = itemList.get(i);
        cout << "  " << item.name << " (value: $" << item.value << ")" << endl;
    }

    // Demo 4: Using range-based for loop (iterator)
    cout << "\n4. Using range-based for loop to traverse the string list:" << endl;
    for (const std::string& str : stringList) {
        cout << str << " ";
    }
    cout << endl;

    // Demo 5: Removing elements
    cout << "\n5. Removing element at index 1 from integer list:" << endl;
    cout << "Before removal: ";
    intList.print();
    intList.removeAt(1);
    cout << "After removal: ";
    intList.print();

    // Demo 6: Copying linked lists
    cout << "\n6. Copying linked list (deep copy):" << endl;
    LinkedList<std::string> copiedList = stringList;
    cout << "Original: ";
    stringList.print();
    cout << "Copy: ";
    copiedList.print();

    cout << "\nTemplate classes allow us to create reusable data structures that work with any type!" << endl;
    cout << "This linked list template can store integers, strings, or any custom class." << endl;
}
// ------------------------------------------------------
// Lab 07 activity: Linked String ADT demonstration
// ------------------------------------------------------

void Game::runLinkedStringLab() {
    using namespace std;
    cout << "\n--- Linked String Lab ---" << endl;
    cout << "Enter first string: ";
    string s1;
    cin >> ws;
    getline(cin, s1);
    cout << "Enter second string: ";
    string s2;
    getline(cin, s2);

    LinkedString ls1(s1);
    LinkedString ls2(s2);

    cout << "You entered:\n";
    cout << "  1) " << ls1.toStdString() << " (length=" << ls1.length() << ")\n";
    cout << "  2) " << ls2.toStdString() << " (length=" << ls2.length() << ")\n";

    if (ls1.equals(ls2))
        cout << "The two strings are equal.\n";
    else
        cout << "The two strings are NOT equal.\n";

    cout << "Demo: change first char of first string to 'X' (if exists)" << endl;
    if (ls1.length() > 0) {
        ls1.set(0, 'X');
        cout << "Modified 1) " << ls1.toStdString() << "\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ------------------------------------------------------
// Homework 05 activity: Linked Bag demonstration
// ------------------------------------------------------

void Game::runBagDemo() {
    using namespace std;
    cout << "\n--- Linked Bag Demo ---" << endl;
    LinkedBag<string> bag;
    cout << "We'll add several strings to a linked bag, then remove and query." << endl;
    vector<string> samples = {"apple", "banana", "cherry", "date", "banana"};
    for (auto &w : samples) {
        bag.add(w);
        cout << "added '" << w << "'\n";
    }
    cout << "current bag size: " << bag.getCurrentSize() << "\n";
    cout << "Bag contains 'banana'? " << (bag.contains("banana") ? "yes" : "no") << "\n";
    cout << "Removing 'banana'...\n";
    bag.remove("banana");
    cout << "Size after removal: " << bag.getCurrentSize() << "\n";
    cout << "Contents via toVector(): ";
    auto vec = bag.toVector();
    for (auto &x : vec) cout << x << " ";
    cout << "\n";
    cout << "Clear bag.\n";
    bag.clear();
    cout << "Bag empty? " << (bag.isEmpty() ? "yes" : "no") << "\n";

    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ------------------------------------------------------
// Week 12 Hashing Lab
// ------------------------------------------------------
void Game::runHashingLab() {
    cout << "\n--- Hashing Challenge (Week 12) ---" << endl;
    cout << "This activity includes both a number hashing game and a color hash table demo." << endl;

    bool done = false;
    while (!done) {
        cout << "\nHashing Challenge Menu:\n";
        cout << "1) Number hashing guess game\n";
        cout << "2) Color hash table demo\n";
        cout << "3) Game element hashing demo\n";
        cout << "0) Return to main menu\n";
        cout << "Choose an option: ";

        int mode = 0;
        if (!(cin >> mode)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number." << endl;
            continue;
        }

        switch (mode) {
            case 1:
                runGuessHashDemo();
                break;
            case 2:
                runColorHashTableDemo();
                break;
            case 3:
                runGameElementHashDemo();
                break;
            case 0:
                done = true;
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
}

// Week 12 hash function helper (alternative formula, not the homework lab formula)
int Game::computeGuessHash(int k) const {
    constexpr int A = 127;
    constexpr int B = 41;
    constexpr int MOD = 100;
    int mixed = (k * A + B) % MOD;
    return mixed / 10;  // map result into 0-9 range
}

std::string Game::normalizeString(const std::string& input) const {
    std::string output = input;
    for (char& c : output) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return output;
}

// Week 12 color table hashing helper
int Game::computeColorHash(const std::string& color) const {
    int sum = 0;
    std::string normalized = normalizeString(color);
    for (char c : normalized) {
        if (c != ' ') {
            sum += static_cast<unsigned char>(c);
        }
    }
    return sum % 15;
}

// Week 12 game element hashing helper
int Game::computeGameElementHash(const std::string& key) const {
    int hash = 0;
    std::string normalized = normalizeString(key);
    for (char c : normalized) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            hash = (hash * 31 + static_cast<unsigned char>(c)) % 100;
        }
    }
    return hash % 10; // map to 10 bins for game element hashing
}

void Game::runGameElementHashDemo() {
    cout << "\n--- Game Element Hashing Demo ---" << endl;
    cout << "This demo hashes your current inventory item names into bins." << endl;

    const int binCount = 10;
    std::vector<std::vector<std::string>> table(binCount);
    int count = static_cast<int>(player.inventorySize());
    if (count == 0) {
        cout << "Your inventory is empty. Add an item first or restart the game with inventory items." << endl;
        return;
    }

    for (size_t i = 0; i < player.inventorySize(); ++i) {
        const auto& item = player[i];
        int bin = computeGameElementHash(item.name);
        table[bin].push_back(item.name);
    }

    cout << "\nInventory item hash bins:\n";
    for (int i = 0; i < binCount; ++i) {
        cout << "  Bin " << i << " (" << table[i].size() << "): ";
        for (size_t j = 0; j < table[i].size(); ++j) {
            cout << table[i][j];
            if (j + 1 < table[i].size()) cout << ", ";
        }
        cout << "\n";
    }

    cin.ignore(10000, '\n');
    while (true) {
        cout << "\nEnter an inventory item name to search (or type 'quit' to return): ";
        std::string query;
        std::getline(cin, query);
        if (query.empty()) continue;
        std::string normalized = normalizeString(query);
        if (normalized == "quit") break;

        int bin = computeGameElementHash(query);
        bool found = false;
        for (const std::string& name : table[bin]) {
            if (normalizeString(name) == normalized) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "Found '" << query << "' in inventory bin " << bin << "." << endl;
            cout << "This demonstrates how inventory item names can be grouped by a hash function." << endl;
        } else {
            cout << "'" << query << "' is not in inventory. "
                 << "If you want, add the item to your inventory manually in the game." << endl;
        }
    }
}

// Week 12 helper: load sample color data for the hash table demo
std::vector<std::string> Game::loadColorListFromFile(const std::string& path) const {
    std::vector<std::string> colors;
    std::ifstream in(path);
    if (!in) {
        std::string altPath = "dungeongame/" + path;
        in.open(altPath);
    }
    if (!in) {
        return colors;
    }
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        colors.push_back(line);
    }
    return colors;
}

void Game::runGuessHashDemo() {
    cout << "\n--- Number Hashing Guess Game ---" << endl;
    cout << "A hidden value is chosen between 0 and 99. Your guesses are compared by hash values." << endl;
    cout << "If your guess hash matches the target hash, the game will tell you.\n";

    int target = rand() % 100;
    int targetHash = computeGuessHash(target);
    int tries = 0;

    while (true) {
        cout << "Enter a guess between 0 and 99 (or -1 to stop): ";
        int guess = 0;
        if (!(cin >> guess)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number." << endl;
            continue;
        }
        if (guess == -1) {
            cout << "Stopping the hashing game. The hidden value was " << target << "." << endl;
            break;
        }
        if (guess < 0 || guess > 99) {
            cout << "Please guess a number between 0 and 99." << endl;
            continue;
        }

        ++tries;
        int guessHash = computeGuessHash(guess);
        cout << "  Guess hash: " << guessHash << endl;

        if (guessHash == targetHash) {
            if (guess == target) {
                cout << "\n*** Found it! ***" << endl;
                cout << "Original target value: " << target << endl;
                cout << "Target hashed value: " << targetHash << endl;
                cout << "Final guess: " << guess << endl;
                cout << "Final guess hash: " << guessHash << endl;
                cout << "Total tries: " << tries << endl;
                break;
            } else {
                cout << "Hash collision! Your guess shares the same hash value, but it is not the hidden number." << endl;
            }
        } else {
            cout << "No match yet. Keep trying." << endl;
        }
    }
}

void Game::runColorHashTableDemo() {
    cout << "\n--- Color Hash Table Demo ---" << endl;
    std::vector<std::string> colors = loadColorListFromFile("data/ColorList.txt");
    if (colors.empty()) {
        colors = {"red", "orange", "yellow", "green", "blue", "indigo", "violet",
                  "black", "white", "gray", "cyan", "magenta", "maroon",
                  "olive", "teal", "navy", "lime", "pink", "brown", "silver", "gold", "beige"};
        cout << "Could not open ColorList.txt; using built-in sample colors." << endl;
    }

    const int binCount = 15;
    std::vector<std::vector<std::string>> table(binCount);
    for (const std::string& color : colors) {
        int bin = computeColorHash(color);
        table[bin].push_back(color);
    }

    int nonEmptyBins = 0;
    int maxBinSize = 0;
    int totalInNonEmpty = 0;
    cout << "\nHash table bins:\n";
    for (int i = 0; i < binCount; ++i) {
        int size = static_cast<int>(table[i].size());
        if (size > 0) {
            nonEmptyBins++;
            totalInNonEmpty += size;
        }
        maxBinSize = std::max(maxBinSize, size);
        cout << "  Bin " << i << " (" << size << "): ";
        for (size_t j = 0; j < table[i].size(); ++j) {
            cout << table[i][j];
            if (j + 1 < table[i].size()) cout << ", ";
        }
        cout << "\n";
    }

    double average = nonEmptyBins > 0 ? static_cast<double>(totalInNonEmpty) / nonEmptyBins : 0.0;
    cout << "\nAverage colors per non-empty bin: " << average << endl;
    cout << "Maximum colors in a single bin: " << maxBinSize << endl;

    cin.ignore(10000, '\n');
    while (true) {
        cout << "\nEnter a color to search for (or type 'quit' to return): ";
        std::string query;
        std::getline(cin, query);
        if (query.empty()) continue;
        std::string normalized = normalizeString(query);
        if (normalized == "quit") break;

        int bin = computeColorHash(query);
        bool found = false;
        for (const std::string& entry : table[bin]) {
            if (normalizeString(entry) == normalized) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "Found '" << query << "' in bin " << bin << "." << endl;
        } else {
            table[bin].push_back(query);
            cout << "'" << query << "' was not found. Added to bin " << bin << "." << endl;
        }
    }
}

// ---------------- Week 04 helper implementations ----------------

void Game::handleSpawnSkip()
{
    cout << "Enter number of enemies to skip (n): ";
    int n = 0;
    if (!(cin >> n)) {
        cin.clear(); cin.ignore(10000, '\n');
        cout << "Invalid input." << endl;
        return;
    }
    spawner.skipEnemies(n);
    cout << "Skipped " << n << " enemies.\n";
}

void Game::handleUndo()
{
    cout << "Undo how many actions? (default 1): ";
    int k = 1;
    if (!(cin >> k)) {
        cin.clear(); cin.ignore(10000, '\n');
        k = 1;
    }
    int undone = history.undoLast(k, player);
    cout << "Undone " << undone << " action(s).\n";
}

void Game::handleCastSpell()
{
    cout << "Enter postfix expression (tokens separated by spaces), e.g. '6 3 + 2 *': ";
    cin.ignore(10000, '\n');
    std::string expr;
    std::getline(cin, expr);
    try {
        int val = SpellEvaluator::evaluatePostfix(expr);

        // provide multiple effects for demo: ask user which effect to apply
        cout << "Choose effect: 1) Heal player  2) Give gold  3) Damage enemy (demo)\n";
        cout << "Enter choice (1-3): ";
        int eff = 1;
        if (!(std::cin >> eff)) { std::cin.clear(); std::cin.ignore(10000, '\n'); eff = 1; }

        switch (eff) {
            case 1:
                cout << "Spell evaluated to: " << val << " (healing player)\n";
                player.heal(val);
                break;
            case 2:
                cout << "Spell evaluated to: " << val << " (granting gold)\n";
                player.addGold(val);
                break;
            case 3:
                cout << "Spell evaluated to: " << val << " (demo damage to next spawned enemy)\n";
                if (spawner.hasEnemies()) {
                    NPC* e = spawner.nextEnemy();
                    e->takeDamage(val);
                    if (e->isAlive()) {
                        cout << e->getName() << " survived the blast (hp=" << e->getHealth() << ") and is re-queued.\n";
                        spawner.addEnemy(e);
                    } else {
                        cout << e->getName() << " was destroyed by the spell!\n";
                        delete e; 

                    }
                } else {
                    cout << "No enemies to affect.\n";
                }
                break;
            default:
                cout << "Unknown effect; applying heal by default." << endl;
                player.heal(val);
                break;
        }
    } catch (const std::exception& ex) {
        cout << "Error evaluating expression: " << ex.what() << "\n";
    }
}

void Game::handlePickItem()
{
    cout << "Enter item name: ";
    std::string name;
    if (!(std::cin >> name)) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Invalid name." << std::endl; return; }
    cout << "Enter item value: ";
    int v = 0;
    if (!(std::cin >> v)) { std::cin.clear(); std::cin.ignore(10000, '\n'); v = 1; }

    Item it(name, v);
    player.addItem(it);
    history.pushPick(it, player.inventorySize() - 1);
    cout << "Picked up: " << it.name << " (" << it.value << ")\n";
}

// simple demo stubs to satisfy menu
void Game::runNPCGroupDemo() {
    cout << "\n--- NPC Group Demo ---\n";
    cout << "(This demo would show a container of NPC pointers.)\n";
}

static size_t bubbleSortCount(Inventory& inv) {
    size_t n = inv.size();
    size_t comparisons = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (inv[j].name > inv[j + 1].name) {
                Item tmp = inv[j];
                inv[j]   = inv[j + 1];
                inv[j + 1] = tmp;
            }
        }
    }
    return comparisons;
}

static size_t insertionSortCount(Inventory& inv) {
    size_t comparisons = 0;
    int n = static_cast<int>(inv.size());
    for (int i = 1; i < n; i++) {
        Item key = inv[static_cast<size_t>(i)];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (inv[static_cast<size_t>(j)].name > key.name) {
                inv[static_cast<size_t>(j + 1)] = inv[static_cast<size_t>(j)];
                j--;
            } else {
                break;
            }
        }
        inv[static_cast<size_t>(j + 1)] = key;
    }
    return comparisons;
}

void Game::runSortSearchDemo() {
    cout << "\n=== Sort/Search Demo ===\n";

    if (player.inventorySize() == 0) {
        cout << "Inventory is empty — adding demo items...\n";
        player.addItem(Item("Potion", 10));
        player.addItem(Item("Sword", 50));
        player.addItem(Item("Bow", 45));
        player.addItem(Item("Shield", 30));
        player.addItem(Item("Elixir", 20));
    }

    cout << "\nInventory (before sorting):\n";
    player.showInventory();

    cout << "\nChoose sorting algorithm:\n";
    cout << "  1) Bubble sort (O(n²))\n";
    cout << "  2) Insertion sort (O(n²))\n";
    cout << "Select (1 or 2): ";
    int sortChoice = 0;
    if (!(cin >> sortChoice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        sortChoice = 1;
    }

    if (sortChoice == 2) {
        cout << "\nSorting inventory by name (insertion sort)...\n";
        player.sortInventoryByNameInsertion();
    } else {
        cout << "\nSorting inventory by name (bubble sort)...\n";
        player.sortInventoryByName();
    }
    player.showInventory();

    const std::string target = "Potion";
    int linearComparisons = 0;
    int binaryComparisons = 0;
    int linearIndex = -1;
    int binaryIndex = -1;

    // Linear search count
    for (size_t i = 0; i < player.inventorySize(); ++i) {
        linearComparisons++;
        if (player[i].name == target) {
            linearIndex = static_cast<int>(i);
            break;
        }
    }

    // Binary search count (requires sorted inventory)
    int lo = 0;
    int hi = static_cast<int>(player.inventorySize()) - 1;
    while (lo <= hi) {
        binaryComparisons++;
        int mid = lo + (hi - lo) / 2;
        const std::string& midName = player[mid].name;
        if (midName == target) {
            binaryIndex = mid;
            break;
        }
        if (midName < target) lo = mid + 1;
        else hi = mid - 1;
    }

    cout << "\nSearch for '" << target << "':\n";
    cout << "  Linear search: index=" << linearIndex << ", comparisons=" << linearComparisons << "\n";
    cout << "  Binary search: index=" << binaryIndex << ", comparisons=" << binaryComparisons << "\n";
}

void Game::runSortCompareDemo() {
    cout << "\n=== Sort Comparison Demo (Bubble vs Insertion) ===\n";

    // Ensure there's inventory to work with
    if (player.inventorySize() == 0) {
        cout << "Inventory is empty — adding demo items...\n";
        player.addItem(Item("Potion", 10));
        player.addItem(Item("Sword", 50));
        player.addItem(Item("Bow", 45));
        player.addItem(Item("Shield", 30));
        player.addItem(Item("Elixir", 20));
    }

    // Copy the current inventory so both algorithms start from the same data
    Inventory base;
    for (size_t i = 0; i < player.inventorySize(); ++i) {
        base.add(player[i]);
    }

    auto runAndMeasure = [&](Inventory inv, const std::string& label,
                             size_t (*sortFn)(Inventory&)) {
        auto start = std::chrono::steady_clock::now();
        size_t comparisons = sortFn(inv);
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        cout << "\n" << label << ":\n";
        cout << "  Sorted result:\n";
        for (size_t i = 0; i < inv.size(); ++i) {
            cout << "    " << i << ") " << inv[i].name << " (" << inv[i].value << ")\n";
        }
        cout << "  Comparisons: " << comparisons << "\n";
        cout << "  Time: " << ms << " microseconds\n";
        return comparisons;
    };

    cout << "Starting with the same inventory for both sorts...\n";
    cout << "Base inventory:\n";
    for (size_t i = 0; i < base.size(); ++i) {
        cout << "  " << i << ") " << base[i].name << " (" << base[i].value << ")\n";
    }

    runAndMeasure(base, "Bubble sort", bubbleSortCount);
    runAndMeasure(base, "Insertion sort", insertionSortCount);

    cout << "\n(Observation: comparisons/time vary depending on sorting algorithm and input order.)\n";
}

// ---------------- Week 11: Array-based sorts & inventory-wide demos ----------------

// Instrumented array sorts (operate on vector<int>) — return comparison count
static size_t bubbleSortArray(std::vector<int>& arr) {
    size_t n = arr.size();
    size_t comparisons = 0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j + 1 < n - i; ++j) {
            comparisons++;
            if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
        }
    }
    return comparisons;
}

static size_t insertionSortArray(std::vector<int>& arr) {
    size_t comparisons = 0;
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[static_cast<size_t>(j)] > key) {
                arr[static_cast<size_t>(j + 1)] = arr[static_cast<size_t>(j)];
                --j;
            } else break;
        }
        arr[static_cast<size_t>(j + 1)] = key;
    }
    return comparisons;
}

static size_t mergeSortArrayRec(std::vector<int>& arr, std::vector<int>& tmp, int lo, int hi) {
    if (lo >= hi) return 0;
    int mid = lo + (hi - lo) / 2;
    size_t comps = 0;
    comps += mergeSortArrayRec(arr, tmp, lo, mid);
    comps += mergeSortArrayRec(arr, tmp, mid + 1, hi);
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        comps++;
        if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }
    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= hi) tmp[k++] = arr[j++];
    for (int x = lo; x <= hi; ++x) arr[x] = tmp[x];
    return comps;
}

static size_t mergeSortArray(std::vector<int>& arr) {
    std::vector<int> tmp(arr.size());
    return mergeSortArrayRec(arr, tmp, 0, static_cast<int>(arr.size()) - 1);
}

static int partitionQS(std::vector<int>& arr, int lo, int hi, size_t& comps) {
    int pivot = arr[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; ++j) {
        comps++;
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[hi]);
    return i + 1;
}

static size_t quickSortArrayRec(std::vector<int>& arr, int lo, int hi) {
    size_t comps = 0;
    if (lo < hi) {
        int p = partitionQS(arr, lo, hi, comps);
        comps += quickSortArrayRec(arr, lo, p - 1);
        comps += quickSortArrayRec(arr, p + 1, hi);
    }
    return comps;
}

static size_t quickSortArray(std::vector<int>& arr) {
    if (arr.empty()) return 0;
    // quickSortArrayRec uses partitionQS which accumulates comparisons via return values
    return quickSortArrayRec(arr, 0, static_cast<int>(arr.size()) - 1);
}

void Game::runArraySortBenchmarks() {
    using namespace std::chrono;
    cout << "\n=== Array Sort Benchmarks ===\n";
    // Extended sizes — include larger sizes for deeper experiments
    std::vector<int> sizes = {100, 1000, 10000, 50000, 100000, 200000, 500000, 1000000};
    cout << "size,algorithm,time_us,comparisons\n";

    // We'll skip O(n^2) sorts for very large sizes to avoid excessively long runs
    const int O2_SKIP_THRESHOLD = 100000; // skip bubble/insertion for sizes > 100k
    for (int s : sizes) {
        cout << "\n-- Running benchmarks for size=" << s << " --\n";
        // generate random array with values [0, s*10)
        std::vector<int> base(s);
        for (int i = 0; i < s; ++i) base[i] = rand() % (s * 10);

        // Bubble (skip if too large)
        if (s <= O2_SKIP_THRESHOLD) {
            auto arr1 = base;
            auto t0 = steady_clock::now();
            size_t comps1 = bubbleSortArray(arr1);
            auto t1 = steady_clock::now();
            auto us1 = duration_cast<microseconds>(t1 - t0).count();
            cout << s << ",bubble," << us1 << "," << comps1 << "\n";
        } else {
            cout << s << ",bubble,skipped,skipped\n";
            cout << "(bubble sort skipped for size " << s << " — O(n^2) would be very slow)\n";
        }

        // Insertion (skip if too large)
        if (s <= O2_SKIP_THRESHOLD) {
            auto arr2 = base;
            auto t0 = steady_clock::now();
            size_t comps2 = insertionSortArray(arr2);
            auto t1 = steady_clock::now();
            auto us2 = duration_cast<microseconds>(t1 - t0).count();
            cout << s << ",insertion," << us2 << "," << comps2 << "\n";
        } else {
            cout << s << ",insertion,skipped,skipped\n";
            cout << "(insertion sort skipped for size " << s << " — O(n^2) would be very slow)\n";
        }

        // Merge
        auto arr3 = base;
        auto t0 = std::chrono::steady_clock::now();
        size_t comps3 = mergeSortArray(arr3);
        auto t1 = std::chrono::steady_clock::now();
        auto us3 = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        cout << s << ",merge," << us3 << "," << comps3 << "\n";

        // Quick
        auto arr4 = base;
        t0 = std::chrono::steady_clock::now();
        size_t comps4 = quickSortArray(arr4);
        t1 = std::chrono::steady_clock::now();
        auto us4 = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        cout << s << ",quick," << us4 << "," << comps4 << "\n";

        // Small sanity check: print first 5 of merge-sorted array
        cout << "sample_sorted_first5:";
        for (int i = 0; i < std::min(5, s); ++i) cout << " " << arr3[i];
        cout << "\n";
    }
    cout << "(CSV output above — copy into Excel/Google Sheets and create log-log or semilog plots.)\n";
}

void Game::runSortInventoryAllDemo() {
    using namespace std::chrono;
    cout << "\n=== Inventory: Run All Sorts (compare) ===\n";
    if (player.inventorySize() == 0) {
        cout << "Inventory is empty — adding demo items...\n";
        player.addItem(Item("Potion", 10));
        player.addItem(Item("Sword", 50));
        player.addItem(Item("Bow", 45));
        player.addItem(Item("Shield", 30));
        player.addItem(Item("Elixir", 20));
    }

    // Copy inventory into a vector<Item> so array-style sorts are fair (random access)
    std::vector<Item> base;
    for (size_t i = 0; i < player.inventorySize(); ++i) base.push_back(player[i]);

    // Helper to run a name-based sort on vector<Item>
    auto runNameSort = [&](std::vector<Item> data, const std::string& label,
                           std::function<size_t(std::vector<int>&)> /*unused*/) {
        // We'll implement using integer mapping: map each name to a hash by comparing strings
        // But for comparisons counting, we will compare strings directly in adapted algorithms below.
        // For simplicity reuse std::sort for merge/quick timing comparison but count string comps via lambda.
    };

    // For clarity, implement three instrumented sorts operating on vector<Item> comparing .name
    auto bubbleItems = [&](std::vector<Item> v) {
        size_t comps = 0;
        size_t n = v.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j + 1 < n - i; ++j) {
                comps++;
                if (v[j].name > v[j + 1].name) std::swap(v[j], v[j + 1]);
            }
        }
        return std::make_pair(v, comps);
    };

    auto insertionItems = [&](std::vector<Item> v) {
        size_t comps = 0;
        for (size_t i = 1; i < v.size(); ++i) {
            Item key = v[i];
            int j = static_cast<int>(i) - 1;
            while (j >= 0) {
                comps++;
                if (v[static_cast<size_t>(j)].name > key.name) {
                    v[static_cast<size_t>(j + 1)] = v[static_cast<size_t>(j)];
                    --j;
                } else break;
            }
            v[static_cast<size_t>(j + 1)] = key;
        }
        return std::make_pair(v, comps);
    };

    // Merge sort for Items
    std::function<size_t(std::vector<Item>&, std::vector<Item>&, int, int)> mergeItemsRec;
    mergeItemsRec = [&](std::vector<Item>& arr, std::vector<Item>& tmp, int lo, int hi) -> size_t {
        if (lo >= hi) return 0;
        int mid = lo + (hi - lo) / 2;
        size_t comps = 0;
        comps += mergeItemsRec(arr, tmp, lo, mid);
        comps += mergeItemsRec(arr, tmp, mid + 1, hi);
        int i = lo, j = mid + 1, k = lo;
        while (i <= mid && j <= hi) {
            comps++;
            if (arr[i].name <= arr[j].name) tmp[k++] = arr[i++];
            else tmp[k++] = arr[j++];
        }
        while (i <= mid) tmp[k++] = arr[i++];
        while (j <= hi) tmp[k++] = arr[j++];
        for (int x = lo; x <= hi; ++x) arr[x] = tmp[x];
        return comps;
    };

    auto mergeItems = [&](std::vector<Item> v) {
        std::vector<Item> tmp(v.size());
        size_t comps = 0;
        if (!v.empty()) comps = mergeItemsRec(v, tmp, 0, static_cast<int>(v.size()) - 1);
        return std::make_pair(v, comps);
    };

    // Quick sort for Items
    std::function<size_t(std::vector<Item>&, int, int)> quickItemsRec;
    std::function<int(std::vector<Item>&, int, int, size_t&)> partitionItems;

    partitionItems = [&](std::vector<Item>& arr, int lo, int hi, size_t& comps) -> int {
        std::string pivot = arr[hi].name;
        int i = lo - 1;
        for (int j = lo; j < hi; ++j) {
            comps++;
            if (arr[j].name < pivot) {
                ++i; std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[hi]);
        return i + 1;
    };

    quickItemsRec = [&](std::vector<Item>& arr, int lo, int hi) -> size_t {
        size_t comps = 0;
        if (lo < hi) {
            int p = partitionItems(arr, lo, hi, comps);
            comps += quickItemsRec(arr, lo, p - 1);
            comps += quickItemsRec(arr, p + 1, hi);
        }
        return comps;
    };

    auto quickItems = [&](std::vector<Item> v) {
        size_t comps = 0;
        if (!v.empty()) comps = quickItemsRec(v, 0, static_cast<int>(v.size()) - 1);
        return std::make_pair(v, comps);
    };

    // Run and measure each algorithm
    auto start = steady_clock::now();
    {
        auto t0 = steady_clock::now();
        auto res = bubbleItems(base);
        auto t1 = std::chrono::steady_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        cout << "Bubble sort:\n";
        for (size_t i = 0; i < res.first.size(); ++i) cout << "  " << i << ") " << res.first[i].name << " (" << res.first[i].value << ")\n";
        cout << "  Comparisons: " << res.second << "  Time: " << us << " microseconds\n\n";
    }

    {
        auto t0 = steady_clock::now();
        auto res = insertionItems(base);
        auto t1 = steady_clock::now();
        auto us = duration_cast<microseconds>(t1 - t0).count();
        cout << "Insertion sort:\n";
        for (size_t i = 0; i < res.first.size(); ++i) cout << "  " << i << ") " << res.first[i].name << " (" << res.first[i].value << ")\n";
        cout << "  Comparisons: " << res.second << "  Time: " << us << " microseconds\n\n";
    }

    {
        auto t0 = steady_clock::now();
        auto res = mergeItems(base);
        auto t1 = steady_clock::now();
        auto us = duration_cast<microseconds>(t1 - t0).count();
        cout << "Merge sort:\n";
        for (size_t i = 0; i < res.first.size(); ++i) cout << "  " << i << ") " << res.first[i].name << " (" << res.first[i].value << ")\n";
        cout << "  Comparisons: " << res.second << "  Time: " << us << " microseconds\n\n";
    }

    {
        auto t0 = steady_clock::now();
        auto res = quickItems(base);
        auto t1 = steady_clock::now();
        auto us = duration_cast<microseconds>(t1 - t0).count();
        cout << "Quick sort:\n";
        for (size_t i = 0; i < res.first.size(); ++i) cout << "  " << i << ") " << res.first[i].name << " (" << res.first[i].value << ")\n";
        cout << "  Comparisons: " << res.second << "  Time: " << us << " microseconds\n\n";
    }

    cout << "(Observation: merge/quick are typically O(n log n); bubble/insertion are O(n^2). Times/comparisons depend on input order and size.)\n";
}

void Game::runNPCSpawnerDemo() {
    cout << "\n--- NPC Spawner Demo ---\n";
    cout << "(This demo shows the NPCSpawner in action.)\n";
}

void Game::handleDropItem()
{
    player.showInventory();
    cout << "Enter index of item to drop: ";
    int idx = -1;
    if (!(std::cin >> idx)) { std::cin.clear(); std::cin.ignore(10000, '\n'); cout << "Invalid input." << endl; return; }
    if (idx < 0 || static_cast<size_t>(idx) >= player.inventorySize()) { cout << "Index out of range." << endl; return; }

    Item removed = player.removeItemAt(static_cast<size_t>(idx));
    history.pushDrop(removed, static_cast<size_t>(idx));
    cout << "Dropped: " << removed.name << "\n";
}

void Game::showSpawnQueue() const
{
    spawner.showQueue();
}

void Game::showActionHistory() const
{
    history.showHistory();
}


void Game::run() {
    // seed rand for flee chance
    srand((unsigned)time(nullptr));

    while (running) {
        displayMap();
        displayMenu();
        int choice = 0;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number." << endl;
            continue;
        }
        processChoice(choice);
    }
    cout << "Thanks for playing!" << endl;
}

// ======================================================
// Spell Grimoire implementations (using LinkedBag<Spell>)
// ======================================================

void Game::initializeGrimoire() {
    // Start the player with a few spells
    grimoire.learnSpell(Spell("Fireball", 20, 30, "deals 30 fire damage"));
    grimoire.learnSpell(Spell("Ice Storm", 25, 35, "deals 35 ice damage"));
    grimoire.learnSpell(Spell("Lightning", 15, 25, "deals 25 lightning damage"));
    cout << "Your grimoire has been initialized with starter spells!" << endl;
}

void Game::viewGrimoire() const {
    cout << "\n=== Your Spell Grimoire ===" << endl;
    if (grimoire.isEmpty()) {
        cout << "Your grimoire is empty. Learn some spells!" << endl;
        return;
    }
    
    auto spells = grimoire.getAllSpells();
    cout << "You know " << spells.size() << " spell(s):\n" << endl;
    for (size_t i = 0; i < spells.size(); ++i) {
        cout << i + 1 << ") " << spells[i].getNameAsString() << endl;
        cout << "   Mana Cost: " << spells[i].getManaCost() 
             << " | Damage: " << spells[i].getDamage() 
             << " | Effect: " << spells[i].getEffect() << endl;
    }
    cout << endl;
}

void Game::learnNewSpell(const Spell& spell) {
    if (grimoire.learnSpell(spell)) {
        cout << "You learned the spell \"" << spell.getNameAsString() << "\"!" << endl;
    } else {
        cout << "Could not learn the spell." << endl;
    }
}

void Game::castSpellFromGrimoire() {
    if (grimoire.isEmpty()) {
        cout << "\nYour grimoire is empty! Learn some spells first." << endl;
        return;
    }
    
    cout << "\n=== Cast Spell from Grimoire ===" << endl;
    viewGrimoire();
    
    auto spells = grimoire.getAllSpells();
    cout << "Choose a spell to cast (1-" << spells.size() << "), or 0 to cancel: ";
    int choice = 0;
    if (!(cin >> choice) || choice < 0 || choice > static_cast<int>(spells.size())) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid choice." << endl;
        return;
    }
    
    if (choice == 0) {
        cout << "Spell casting cancelled." << endl;
        return;
    }
    
    Spell spell = spells[choice - 1];
    cout << "You cast " << spell.getNameAsString() << "!" << endl;
    cout << "  Effect: " << spell.getEffect() << endl;
    cout << "  (Mana cost: " << spell.getManaCost() << ")" << endl;
}

// ======================================================
// Loot Bag implementations (using LinkedBag<Item>)
// ======================================================

void Game::handleLootBag() {
    cout << "\n=== Loot Bag ===" << endl;
    if (lootBag.isEmpty()) {
        cout << "Your loot bag is empty." << endl;
        return;
    }
    
    auto lootItems = lootBag.toVector();
    cout << "You have " << lootItems.size() << " item(s) in your loot bag:\n" << endl;
    for (size_t i = 0; i < lootItems.size(); ++i) {
        cout << i + 1 << ") " << lootItems[i].name 
             << " (value: $" << lootItems[i].value << ")" << endl;
    }
    
    cout << "\nOptions: 1) Transfer all to inventory  2) Cancel\n";
    cout << "Choose: ";
    int choice = 0;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    
    if (choice == 1) {
        transferLootToInventory();
    }
}

void Game::transferLootToInventory() {
    auto lootItems = lootBag.toVector();
    int transferred = 0;
    
    for (auto& item : lootItems) {
        player.addItem(item);
        transferred++;
    }
    
    lootBag.clear();
    cout << "Transferred " << transferred << " item(s) to inventory." << endl;
}
}

