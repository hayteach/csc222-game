# 🎮 C++ Game Project: Text-Based Adventure RPG
## Semester-Long Data Structures Implementation

### 📚 Overview
Students will build a progressively more complex text-based adventure RPG game throughout the entire semester. Each week introduces new data structures and algorithms that enhance the game's functionality. This is a **cumulative project** where each week builds on previous work, demonstrating how advanced data structures solve real-world programming problems.

---

## 🎯 Learning Objectives

By the end of this project, students will be able to:
- Implement and apply fundamental data structures (ADTs, linked lists, stacks, queues, trees, graphs, hash tables)
- Analyze algorithm efficiency and make informed optimization decisions
- Use pointers, references, and dynamic memory allocation effectively
- Apply searching and sorting algorithms to game data
- Design complex systems using object-oriented principles
- Build a complete, playable game that showcases data structures knowledge
- Debug and test programs with advanced data structures

---

## 🎲 Game Concept: "Dungeon of Data Structures"

**Game Description:** An evolving text-based RPG where players explore interconnected dungeons, battle enemies with strategic combat, manage inventory, navigate complex maps, and make choices that affect the story. Each week's new data structure adds a significant feature to the game.

**Why this game format?**
- Perfect for demonstrating data structures (inventory = lists, maps = graphs, undo = stacks)
- Console-based keeps focus on algorithms, not graphics
- Naturally expands with each new topic
- Students see immediate, tangible results of their data structure implementations

---

## 📋 Semester-Long Lesson Breakdown

### **Week 1: Introduction to C++ & Game Foundation (Setup Week)**

#### Topic: C++ Basics Review
#### Game Feature: Core Game Structure

#### Learning Goals
- Review C++ syntax (coming from Java/Python)
- Set up multi-file project structure
- Create basic game loop and console I/O

#### Activities
1. **Project Introduction** (15 min)
   - Show completed game demo (instructor plays)
   - Explain semester-long nature of project
   - Discuss how each week adds a new data structure

2. **Initial Design** (20 min)
   - Core game concept: dungeon exploration RPG
   - Identify what data we'll need to manage
   - Sketch initial class structure

3. **Set Up Project** (20 min)
   ```
   DungeonGame/
   ├── main.cpp
   ├── Game.h / Game.cpp
   ├── Player.h / Player.cpp
   └── [more files added each week]
   ```

#### Homework
- Create basic game loop with menu
- Implement simple player movement (console-based grid)
- Test compilation and project structure

---

### **Week 2: OOP Review - Classes and Objects**

#### Topic: Object-Oriented Programming in C++
#### Game Feature: Character System & Basic Combat

#### Learning Goals
- Review class design with header/implementation files
- Practice encapsulation and member functions
- Understand constructors and destructors

#### Activities
1. **Create Character Classes** (30 min)
   ```cpp
   // Character.h - Base class for all characters
   class Character {
   protected:
       string name;
       int health, maxHealth;
       int attack, defense;
       Position location;
   public:
       Character(string n, int hp, int atk, int def);
       virtual void takeDamage(int damage);
       virtual int calculateAttack() const;
       void displayStats() const;
       bool isAlive() const;
   };
   
   // Player.h - Inherits from Character
   class Player : public Character {
   private:
       int experience;
       int level;
       int gold;
   public:
       Player(string name);
       void gainExperience(int exp);
       void levelUp();
       void addGold(int amount);
   };
   
   // Enemy.h - Inherits from Character
   class Enemy : public Character {
   private:
       int expReward;
       int goldReward;
   public:
       Enemy(string name, int hp, int atk, int def, int exp, int gold);
       int getExpReward() const;
       int getGoldReward() const;
   };
   ```

2. **Implement Turn-Based Combat** (25 min)
   - Simple combat loop
   - Player chooses action
   - Damage calculation
   - Victory/defeat conditions

#### Homework
- Complete all Character, Player, and Enemy methods
- Create 5 different enemy types
- Implement experience and leveling system
- Test combat with various enemy types

#### Program: Week 2 — Session Plan & In-Class Activities 🔧

- **Session 3 (90 min) — OOP Review & Character Classes**
  - 10 min: Quick recap / 5-question warmup quiz (classes, members, access)
  - 20 min: Instructor live-coding: implement `Character` constructor, `takeDamage`, `calculateAttack`, and `displayStats` in `Character.cpp`
  - 30 min: Guided lab (pair-program): students implement `Player` and `Enemy` methods (`gainExperience`, `levelUp`, rewards getters)
  - 20 min: Small test harness: compile and run simple scenarios (instantiate characters, simulate an attack)
  - Exit ticket: push a small commit with a comment describing one thing learned

- **Session 4 (90 min) — Turn-Based Combat & Integration**
  - 10 min: Warm-up: run and discuss homework results
  - 30 min: Instructor walkthrough: implement simple turn-based combat loop and damage calculation
  - 30 min: Lab: students add 3 enemy types, test experience/gold rewards, and debug combat edge cases
  - 15 min: Two short demos (student volunteers show a combat run)
  - 5 min: Wrap-up & homework assignment (add more enemy types, prepare items for Week 3)

**Formative Assessment & Checkpoints ✅**
- In-class checklist for students:
  - Code compiles and runs (no crashes)
  - `Character` methods tested (unit or simple harness)
  - At least 3 enemy types implemented and battle tested
  - Commit with a descriptive message pushed to repo
- Instructor quick rubric for in-class work:
  - Implementation correctness (60%), runs and compiles (20%), test/demonstration (20%)

**Materials & Starter Files**
- Point students to the `dungeongame/src/` starter code (`Character.cpp`, `Player.cpp`, `Enemy.cpp`, `main.cpp`) and test harness in `tests/`
- Provide a short starter test file (suggested: `tests/combat_test.cpp`) that exercises attack and death conditions

**Extensions & Challenge Tasks (for early finishers) 💡**
- Add status effects (poison, stun) to `Character`
- Add critical hits or random variance to damage
- Make equipment modify attack/defense via simple equip/unequip methods

**Notes for instructors**
- Encourage pair programming and sharing of commits
- Use the demos to assess understanding rather than only final correctness

---

### **Week 3: Abstract Data Types (ADT) with Intro to Pointers**

#### Topic: ADTs and Pointer Basics
#### Game Feature: Generic Item System & Item Management

#### Learning Goals
- Design and implement an Abstract Data Type
- Understand pointer syntax and usage
- Use pointers to create flexible game systems

#### Activities
1. **Design Item ADT** (20 min)
   ```cpp
   // ItemADT.h - Abstract interface for all items
   class ItemADT {
   public:
       virtual string getName() const = 0;
       virtual string getDescription() const = 0;
       virtual void use(Player* player) = 0;  // Pointer to modify player
       virtual ItemADT* clone() const = 0;    // Create copy
       virtual ~ItemADT() {}  // Virtual destructor
   };
   
   // Weapon.h - Implements ItemADT
   class Weapon : public ItemADT {
   private:
       string name;
       int attackBonus;
   public:
       string getName() const override;
       void use(Player* player) override;  // Equips weapon
       ItemADT* clone() const override;
   };
   
   // Potion.h - Implements ItemADT
   class Potion : public ItemADT {
   private:
       string name;
       int healAmount;
   public:
       void use(Player* player) override;  // Consumes potion, heals player
       ItemADT* clone() const override;
   };
   ```

2. **Pointer Practice** (25 min)
   - Pass characters by pointer in combat
   - Use `new` and `delete` for dynamic items
   - Prevent memory leaks

3. **Polymorphism Demo** (10 min)
   ```cpp
   void useItem(ItemADT* item, Player* player) {
       cout << "Using " << item->getName() << "...\n";
       item->use(player);  // Calls appropriate derived class method
   }
   ```

#### Homework
- Implement 3+ different item types (weapons, potions, armor)
- Create item factory function using pointers
- Add item usage to game loop
- Ensure no memory leaks (test with valgrind or similar)

**🎯 Key Concept:** ADTs allow different item types to be treated uniformly while maintaining unique behaviors!

---

### **Week 4: Linked Lists and Arrays**

#### Topic: Linked List Implementation
#### Game Feature: Dynamic Inventory System

#### Learning Goals
- Implement a linked list from scratch
- Compare linked list vs array performance
- Manage dynamic memory with linked structures

#### Activities
1. **Build Inventory Linked List** (35 min)
   ```cpp
   // InventoryNode.h
   struct InventoryNode {
       ItemADT* item;
       int quantity;
       InventoryNode* next;
       
       InventoryNode(ItemADT* itm, int qty) 
           : item(itm), quantity(qty), next(nullptr) {}
   };
   
   // Inventory.h
   class Inventory {
   private:
       InventoryNode* head;
       int itemCount;
       int maxCapacity;
   public:
       Inventory(int capacity);
       ~Inventory();  // Must delete all nodes!
       
       bool addItem(ItemADT* item, int quantity = 1);
       bool removeItem(string itemName, int quantity = 1);
       ItemADT* findItem(string itemName);
       void displayInventory() const;
       bool isFull() const;
       int getItemCount() const;
   };
   ```

2. **Implement Core Methods** (20 min)
   - Add item (insert at head or tail)
   - Remove item (search and delete node)
   - Find item (linear search)
   - Display inventory (traverse list)

3. **Memory Management Practice** (10 min)
   - Destructor must free all nodes
   - Deep copy for copy constructor
   - Handle edge cases (empty list, single item)

#### Homework
- Complete all inventory methods
- Add sorting capability (sort by name or type)
- Implement weight/capacity system
- Add item stacking (multiple of same item)
- Test with large inventories

**🎯 Key Concept:** Linked lists allow dynamic inventory size without pre-allocated arrays!

---

### **Week 5: Introduction to Stacks and Queues**

#### Topic: Stack and Queue ADTs
#### Game Feature: Undo System & Turn Queue

#### Learning Goals
- Implement stack and queue from scratch
- Understand LIFO vs FIFO
- Apply stacks/queues to real problems

#### Activities
1. **Create Action Stack for Undo** (25 min)
   ```cpp
   // GameAction.h
   struct GameAction {
       enum ActionType { MOVE, USE_ITEM, COMBAT, PICKUP };
       ActionType type;
       // Data needed to undo action
       Position previousPosition;
       int previousHealth;
       ItemADT* usedItem;
       
       void undo(Player* player);
   };
   
   // ActionStack.h
   class ActionStack {
   private:
       struct Node {
           GameAction action;
           Node* next;
       };
       Node* top;
       int size;
       int maxSize;  // Limit undo history
   public:
       void push(const GameAction& action);
       GameAction pop();
       bool isEmpty() const;
       bool isFull() const;
   };
   ```

2. **Implement Turn Queue** (25 min)
   ```cpp
   // TurnQueue.h - For battles with multiple enemies
   class TurnQueue {
   private:
       struct Node {
           Character* character;
           Node* next;
       };
       Node* front;
       Node* rear;
   public:
       void enqueue(Character* character);
       Character* dequeue();
       Character* peek() const;
       bool isEmpty() const;
       void displayQueue() const;
   };
   ```

3. **Integrate into Game** (15 min)
   - Add "undo" command to main menu
   - Use turn queue for multi-enemy battles
   - Test undo functionality

#### Homework
- Complete stack and queue implementations
- Add redo functionality (second stack)
- Implement turn-based combat with 3+ enemies
- Limit undo to last 10 actions

**🎯 Key Concept:** Stacks are perfect for undo systems; queues manage turn order fairly!

---

### **Week 6: Pointers and References in C++**

#### Topic: Advanced Pointer Usage & Reference Parameters
#### Game Feature: Smart Enemy AI & Object Relationships

#### Learning Goals
- Master pointer arithmetic and dereferencing
- Use references for efficient parameter passing
- Implement object relationships with pointers

#### Activities
1. **Enemy AI with Pointers** (30 min)
   ```cpp
   // Enemy.h - Enhanced with AI
   class Enemy : public Character {
   private:
       Player* target;  // Pointer to player
       Enemy* ally;     // Pointer to another enemy
       float aggressionLevel;
   public:
       void setTarget(Player* p) { target = p; }
       void setAlly(Enemy* e) { ally = e; }
       
       // AI decision making
       Action decideAction();
       bool shouldCallForHelp() const;
       void assistAlly();
   };
   ```

2. **Combat System Refactor** (20 min)
   ```cpp
   // Pass by reference for efficiency
   void processCombat(Player& player, Enemy& enemy);
   void applyStatusEffect(Character& target, StatusEffect& effect);
   
   // Return pointers for optional results
   Enemy* findNearestEnemy(Position pos, vector<Enemy*>& enemies);
   ItemADT* checkForLoot(Enemy* defeated);
   ```

3. **Pointer Safety** (15 min)
   - Check for nullptr before dereferencing
   - Avoid dangling pointers
   - Use const pointers where appropriate

#### Homework
- Implement enemy AI that targets weakest player ally
- Create enemy formations (enemies point to each other)
- Add status effects using pointers (poison, buffs)
- Implement proper pointer safety checks

**🎯 Key Concept:** Pointers enable complex object relationships and efficient memory usage!

---

### **Week 7: Memory Allocation / Linked Stacks and Queues**

#### Topic: Dynamic Memory Management
#### Game Feature: Dynamic Enemy Spawning & Room Management

#### Learning Goals
- Use `new` and `delete` correctly
- Implement linked stack/queue with dynamic allocation
- Manage memory in complex systems

#### Activities
1. **Dynamic Room System** (25 min)
   ```cpp
   // Room.h
   class Room {
   private:
       string description;
       vector<Enemy*> enemies;  // Dynamically allocated
       vector<ItemADT*> items;  // Dynamically allocated
       Room* north;
       Room* south;
       Room* east;
       Room* west;
   public:
       Room(string desc);
       ~Room();  // Must free all dynamic memory!
       
       void spawnEnemy(string enemyType);
       void addItem(ItemADT* item);
       void connectRoom(Room* other, Direction dir);
       void cleanup();  // Remove defeated enemies
   };
   ```

2. **Enemy Spawn Queue** (20 min)
   ```cpp
   // SpawnQueue.h - Manages timed enemy spawns
   class SpawnQueue {
   private:
       struct SpawnEvent {
           string enemyType;
           int turnsUntilSpawn;
           Room* location;
       };
       queue<SpawnEvent*> pendingSpawns;
   public:
       void scheduleSpawn(string type, int turns, Room* room);
       void processTurn();  // Check if any enemies should spawn
       ~SpawnQueue();  // Free all event memory
   };
   ```

3. **Memory Leak Prevention** (20 min)
   - Rule of Three (destructor, copy constructor, assignment operator)
   - Using valgrind or similar tools
   - Smart pointer preview (unique_ptr, shared_ptr)

#### Homework
- Implement complete Room system with connections
- Create dungeon with 10+ rooms
- Add enemy respawn mechanics
- Test for memory leaks
- Bonus: Implement save system that saves room states

**🎯 Key Concept:** Dynamic memory allows unlimited enemies/items but requires careful management!

---

### **Week 8: Algorithm Efficiency**

#### Topic: Big-O Analysis & Optimization
#### Game Feature: Performance Profiling & Optimization

#### Learning Goals
- Analyze time and space complexity
- Profile code to find bottlenecks
- Optimize critical game loops

#### Activities
1. **Analyze Current Code** (30 min)
   ```cpp
   // Example: Inventory search
   // Current: O(n) linear search through linked list
   ItemADT* Inventory::findItem(string name) {
       InventoryNode* current = head;
       while (current != nullptr) {  // O(n)
           if (current->item->getName() == name)
               return current->item;
           current = current->next;
       }
       return nullptr;
   }
   
   // Questions:
   // - How often is findItem() called?
   // - Is O(n) acceptable for our inventory size?
   // - Could we use a better data structure? (foreshadowing hash tables!)
   ```

2. **Profile Game Performance** (20 min)
   - Add timing code to measure function execution
   - Identify slowest functions
   - Count iterations in main game loop

3. **Optimize Critical Paths** (15 min)
   - Cache frequently accessed items
   - Reduce redundant calculations
   - Optimize combat calculations

#### Homework
- Analyze Big-O of all major game functions
- Create performance report showing:
  - Most called functions
  - Slowest functions
  - Memory usage over time
- Propose optimizations for next weeks
- Implement at least 2 optimizations

**🎯 Key Concept:** Understanding efficiency helps make informed data structure choices!

---

### **Week 9: Searching & Sorting (Bubble, Insertion Sort)**

#### Topic: Basic Sorting Algorithms
#### Game Feature: Inventory Sorting & Search

#### Learning Goals
- Implement bubble sort and insertion sort
- Compare algorithm performance
- Apply sorting to game data

#### Activities
1. **Sort Inventory** (30 min)
   ```cpp
   // Inventory.h - Add sorting methods
   class Inventory {
   public:
       void sortByName();          // Alphabetical
       void sortByValue();         // Most valuable first
       void sortByType();          // Group by item type
       void sortByWeight();        // Heaviest first
       
   private:
       void bubbleSort(bool (*compare)(ItemADT*, ItemADT*));
       void insertionSort(bool (*compare)(ItemADT*, ItemADT*));
   };
   
   // Comparison functions
   bool compareByName(ItemADT* a, ItemADT* b) {
       return a->getName() < b->getName();
   }
   
   bool compareByValue(ItemADT* a, ItemADT* b) {
       return a->getValue() > b->getValue();
   }
   ```

2. **Implement Both Algorithms** (25 min)
   - Bubble sort: Simple but slow
   - Insertion sort: Better for small lists
   - Count comparisons and swaps

3. **Binary Search** (10 min)
   ```cpp
   // Only works on sorted inventory!
   ItemADT* Inventory::binarySearch(string name) {
       // Convert linked list to array for binary search
       // O(log n) vs O(n) linear search
   }
   ```

#### Homework
- Implement all sorting methods
- Add "sort inventory" command
- Compare performance of bubble vs insertion sort
- Create visual display showing sort in action
- Implement binary search for sorted inventory

**🎯 Key Concept:** Sorting enables efficient searching; different algorithms suit different situations!

---

### **Week 10: Searching & Sorting (Merge & Quick Sort)**

#### Topic: Advanced Sorting Algorithms
#### Game Feature: Leaderboard & Statistics

#### Learning Goals
- Implement merge sort and quick sort
- Understand divide-and-conquer strategies
- Compare all sorting algorithms

#### Activities
1. **High Score System** (25 min)
   ```cpp
   // HighScore.h
   struct PlayerScore {
       string playerName;
       int score;
       int level;
       int playtime;  // in minutes
       time_t date;
   };
   
   class Leaderboard {
   private:
       vector<PlayerScore> scores;
   public:
       void addScore(const PlayerScore& score);
       void sortByScore();      // Quick sort
       void sortByPlaytime();   // Merge sort
       void display(int topN) const;
       void saveToFile(string filename);
       void loadFromFile(string filename);
   };
   ```

2. **Implement Advanced Sorts** (30 min)
   ```cpp
   // Quick sort - generally fastest
   void Leaderboard::quickSort(int left, int right) {
       if (left >= right) return;
       int pivot = partition(left, right);
       quickSort(left, pivot - 1);
       quickSort(pivot + 1, right);
   }
   
   // Merge sort - stable, predictable
   void Leaderboard::mergeSort(vector<PlayerScore>& arr) {
       if (arr.size() <= 1) return;
       // Divide, recursively sort, merge
   }
   ```

3. **Performance Comparison** (10 min)
   - Test all 4 sorts on large datasets
   - Graph performance results
   - Discuss when to use each algorithm

#### Homework
- Complete leaderboard with both sorts
- Add game statistics tracking
- Compare performance of all 4 sorts (bubble, insertion, merge, quick)
- Add score submission at end of game
- Bonus: Add filter/search in leaderboard

**🎯 Key Concept:** Merge/quick sort are much faster (O(n log n)) than bubble/insertion (O(n²))!

---

### **Week 11: Hash Tables**

#### Topic: Hash Table Implementation
#### Game Feature: Fast Item Lookup & Skill System

#### Learning Goals
- Implement hash table with chaining
- Design hash functions
- Understand collision resolution

#### Activities
1. **Item Database with Hash Table** (30 min)
   ```cpp
   // ItemDatabase.h
   class ItemDatabase {
   private:
       struct HashNode {
           string key;           // Item name
           ItemADT* value;       // Item object
           HashNode* next;       // Chaining for collisions
       };
       
       vector<HashNode*> table;
       int tableSize;
       int itemCount;
       
       int hashFunction(const string& key) const;
       void resize();  // When load factor > 0.75
   public:
       ItemDatabase(int size = 101);
       ~ItemDatabase();
       
       void insert(string name, ItemADT* item);
       ItemADT* find(string name);  // O(1) average!
       bool remove(string name);
       void displayStats() const;  // Show distribution
   };
   ```

2. **Implement Hash Function** (20 min)
   ```cpp
   int ItemDatabase::hashFunction(const string& key) const {
       int hash = 0;
       for (char c : key) {
           hash = (hash * 31 + c) % tableSize;
       }
       return hash;
   }
   ```

3. **Skill System** (15 min)
   ```cpp
   // SkillTree.h - Uses hash table for fast skill lookup
   class SkillTree {
   private:
       unordered_map<string, Skill*> skills;  // STL hash table
   public:
       void learnSkill(string name);
       bool hasSkill(string name) const;
       void useSkill(string name, Enemy* target);
   };
   ```

#### Homework
- Complete hash table with collision handling
- Replace linear search in inventory with hash lookup
- Implement skill system with 10+ skills
- Test hash function distribution
- Compare lookup performance: linked list vs hash table

**🎯 Key Concept:** Hash tables provide O(1) lookup—perfect for item databases!

---

### **Week 12: Graphs (BFS and DFS)**

#### Topic: Graph Representation and Traversal
#### Game Feature: Dungeon Map & Exploration

#### Learning Goals
- Represent graphs with adjacency lists
- Implement BFS and DFS
- Apply graph traversal to game maps

#### Activities
1. **Dungeon as Graph** (25 min)
   ```cpp
   // DungeonMap.h
   class DungeonMap {
   private:
       struct Room {
           int id;
           string description;
           vector<int> connectedRooms;  // Adjacency list
           bool visited;
           bool hasEnemies;
           bool hasTreasure;
       };
       
       vector<Room> rooms;
       int startRoomId;
   public:
       void addRoom(int id, string desc);
       void connectRooms(int room1, int room2);
       
       // BFS: Explores nearby rooms first (good for fog of war)
       void breadthFirstSearch(int startId);
       
       // DFS: Explores deeply (good for finding exits)
       void depthFirstSearch(int startId);
       
       vector<int> findPath(int start, int goal);
       void displayMap() const;
   };
   ```

2. **Implement BFS** (20 min)
   ```cpp
   void DungeonMap::breadthFirstSearch(int startId) {
       queue<int> toVisit;
       vector<bool> visited(rooms.size(), false);
       
       toVisit.push(startId);
       visited[startId] = true;
       
       while (!toVisit.empty()) {
           int current = toVisit.front();
           toVisit.pop();
           
           cout << "Exploring: " << rooms[current].description << "\n";
           
           for (int neighbor : rooms[current].connectedRooms) {
               if (!visited[neighbor]) {
                   visited[neighbor] = true;
                   toVisit.push(neighbor);
               }
           }
       }
   }
   ```

3. **Implement DFS** (20 min)
   - Recursive version
   - Stack-based version
   - Compare BFS vs DFS exploration patterns

#### Homework
- Create dungeon with 20+ interconnected rooms
- Implement fog of war (only show visited rooms)
- Add "auto-explore" using BFS
- Add "find exit" using DFS
- Create map visualization in console

**🎯 Key Concept:** Graphs represent connected spaces; BFS/DFS explore them systematically!

---

### **Week 13: Graphs (Shortest Distance)**

#### Topic: Dijkstra's Algorithm & Shortest Paths
#### Game Feature: Enemy Pathfinding & Fast Travel

#### Learning Goals
- Implement Dijkstra's algorithm
- Find shortest paths in weighted graphs
- Apply pathfinding to game mechanics

#### Activities
1. **Weighted Dungeon Graph** (25 min)
   ```cpp
   // DungeonMap.h - Enhanced with weights
   class DungeonMap {
   private:
       struct Edge {
           int toRoom;
           int distance;  // Weight: danger level, travel time
       };
       
       struct Room {
           int id;
           vector<Edge> connections;  // Weighted edges
       };
   public:
       // Dijkstra's algorithm
       vector<int> findShortestPath(int start, int goal);
       int getPathDistance(vector<int> path);
       void displayPath(vector<int> path);
   };
   ```

2. **Implement Dijkstra's** (30 min)
   ```cpp
   vector<int> DungeonMap::findShortestPath(int start, int goal) {
       vector<int> distance(rooms.size(), INT_MAX);
       vector<int> previous(rooms.size(), -1);
       vector<bool> visited(rooms.size(), false);
       
       distance[start] = 0;
       
       // Priority queue for efficiency
       priority_queue<pair<int, int>> pq;  // (distance, room)
       pq.push({0, start});
       
       while (!pq.empty()) {
           int current = pq.top().second;
           pq.pop();
           
           if (visited[current]) continue;
           visited[current] = true;
           
           if (current == goal) break;
           
           for (Edge& edge : rooms[current].connections) {
               int newDist = distance[current] + edge.distance;
               if (newDist < distance[edge.toRoom]) {
                   distance[edge.toRoom] = newDist;
                   previous[edge.toRoom] = current;
                   pq.push({-newDist, edge.toRoom});
               }
           }
       }
       
       // Reconstruct path
       return reconstructPath(previous, start, goal);
   }
   ```

3. **Enemy AI Pathfinding** (10 min)
   - Enemies use shortest path to chase player
   - Consider danger levels (avoid traps)

#### Homework
- Complete Dijkstra's implementation
- Add "fast travel" using shortest paths
- Implement enemy pathfinding AI
- Add different edge weights (traps = high cost, shortcuts = low cost)
- Visualize path finding

**🎯 Key Concept:** Dijkstra's finds optimal paths—critical for AI and navigation!

---

### **Week 14: Trees (Binary Trees, Binary Search Trees)**

#### Topic: Tree Structures & BST Operations
#### Game Feature: Skill Tree & Dialogue System

#### Learning Goals
- Implement binary trees and BSTs
- Perform tree traversals (inorder, preorder, postorder)
- Balance trees for efficiency

#### Activities
1. **Skill Tree System** (30 min)
   ```cpp
   // SkillNode.h
   struct SkillNode {
       string skillName;
       string description;
       int requiredLevel;
       int cost;
       bool unlocked;
       SkillNode* prerequisite;  // Parent skill
       SkillNode* leftChild;     // Alternative path
       SkillNode* rightChild;    // Alternative path
   };
   
   // SkillTree.h
   class SkillTree {
   private:
       SkillNode* root;
   public:
       void displayTree() const;          // Visual tree
       void displayUnlockable() const;    // BFS to find available
       bool unlockSkill(string name);
       void displayInorder() const;       // Sorted by level
       int countUnlockedSkills() const;
   };
   ```

2. **BST for Fast Item Lookup** (25 min)
   ```cpp
   // ItemBST.h - Alternative to hash table
   class ItemBST {
   private:
       struct Node {
           ItemADT* item;
           Node* left;
           Node* right;
       };
       Node* root;
       
       Node* insertHelper(Node* node, ItemADT* item);
       Node* findHelper(Node* node, string name);
   public:
       void insert(ItemADT* item);
       ItemADT* find(string name);  // O(log n) if balanced
       void displayInorder() const;  // Sorted output
   };
   ```

3. **Dialogue Tree** (10 min)
   ```cpp
   // DialogueNode.h - For NPC conversations
   struct DialogueNode {
       string text;
       vector<DialogueNode*> choices;  // Player responses
       bool endsConversation;
   };
   ```

#### Homework
- Create skill tree with 15+ skills
- Implement BST for item management
- Add NPC dialogue system with branching conversations
- Compare BST vs hash table performance
- Implement tree balancing (AVL or Red-Black preview)

**🎯 Key Concept:** Trees organize hierarchical data; BSTs provide efficient sorted access!

---

### **Week 15: More Trees**

#### Topic: Advanced Tree Structures (AVL, Heaps, Tries)
#### Game Feature: Priority Systems & Autocomplete

#### Learning Goals
- Implement self-balancing trees
- Use heaps for priority queues
- Apply tries for string matching

#### Activities
1. **Priority Event System with Heap** (25 min)
   ```cpp
   // EventHeap.h - Min-heap for timed events
   class EventHeap {
   private:
       struct GameEvent {
           string type;
           int priority;  // Lower = more urgent
           int turnNumber;
           function<void()> action;
       };
       
       vector<GameEvent> heap;
       
       void heapifyUp(int index);
       void heapifyDown(int index);
   public:
       void addEvent(GameEvent event);
       GameEvent getNextEvent();
       void processEvents(int currentTurn);
   };
   ```

2. **Command Autocomplete with Trie** (25 min)
   ```cpp
   // CommandTrie.h - For command autocomplete
   class CommandTrie {
   private:
       struct TrieNode {
           char character;
           bool isEndOfWord;
           map<char, TrieNode*> children;
       };
       TrieNode* root;
   public:
       void insert(string command);
       vector<string> autocomplete(string prefix);
       bool isValidCommand(string command);
   };
   ```

3. **AVL Tree for Balanced Inventory** (15 min)
   - Show how rotations maintain balance
   - Guarantee O(log n) operations
   - Compare performance with unbalanced BST

#### Homework
- Implement heap-based event system
- Add trie for command autocomplete
- Create AVL tree version of item BST
- Compare all tree structures performance
- Polish and finalize game features

**🎯 Key Concept:** Advanced trees solve specific problems: heaps for priority, tries for strings, AVL for balance!

---

### **Final Week: Project Completion & Presentations**

#### Activities
1. **Final Polish** (20 min)
   - Bug fixes
   - User interface improvements
   - Add help system

2. **Code Review** (25 min)
   - Review data structure usage
   - Identify optimization opportunities
   - Discuss design decisions

3. **Presentations** (30+ min)
   - Each student demos their game (5 min)
   - Explain one data structure in detail
   - Show before/after performance metrics

4. **Reflection** (10 min)
   - What data structure was most useful?
   - What would you change?
   - How does this apply to real-world projects?

---

#### Learning Goals
- Understand game requirements
- Plan class structure
- Identify data types and variables needed

#### Activities
1. **Brainstorm Game Features** (10 min)
   - Discuss: What makes a good RPG?
   - Core features: Character stats, combat, inventory, exploration
   - Keep it simple - we can add features later!

2. **Design Class Structure** (15 min)
   - What classes do we need?
     - `Character` (for player and enemies)
     - `Item` (for weapons, potions)
     - `Game` (game controller/manager)
   - What data does each class need?
   - What actions can each class perform?

3. **Create UML Diagram** (10 min)
   - Draw class diagrams on whiteboard/paper
   - List member variables and functions for each class
   - Discuss relationships between classes

4. **Set Up Project Structure** (10 min)
   ```
   HeroQuest/
   ├── Character.h
   ├── Character.cpp
   ├── Item.h
   ├── Item.cpp
   ├── Game.h
   ├── Game.cpp
   └── main.cpp
   ```

#### Homework/Lab Work
- Create empty files for all classes
- Add include guards to all header files
- Write comments outlining what each class will do

---

### **Session 2: Building the Character Class (45-60 minutes)**

#### Learning Goals
- Create header files with class declarations
- Implement constructors and member functions
- Use proper include guards and file structure

#### Activities

1. **Review Include Guards** (5 min)
   ```cpp
   #ifndef CHARACTER_H
   #define CHARACTER_H
   // class declaration here
   #endif
   ```

2. **Design Character Class Together** (15 min)
   - Discuss what data a character needs:
     - Name (string)
     - Health (int)
     - Attack power (int)
     - Defense (int)
     - Level (int)
     - Experience points (int)
   
3. **Write Character.h as a Class** (15 min)
   ```cpp
   // Live coding with students following along
   class Character {
   private:
       string name;
       int health;
       int maxHealth;
       int attackPower;
       int defense;
       int level;
       int experience;
       
   public:
       // Constructor
       Character(string n, int hp, int atk, int def);
       
       // Getters
       string getName() const;
       int getHealth() const;
       int getLevel() const;
       
       // Actions
       void takeDamage(int damage);
       void heal(int amount);
       void attack(Character& target);
       void displayStats() const;
       bool isAlive() const;
       void gainExperience(int exp);
   };
   ```

4. **Implement Character.cpp** (20 min)
   - Start with constructor
   - Implement 2-3 simple functions together
   - Students complete remaining functions

5. **Discussion: Public vs Private** (5 min)
   - Why keep member variables private?
   - When to use getters/setters?

#### Homework/Lab Work
- Complete all Character class functions
- Write a simple main.cpp to test Character class
- Create a player character and display their stats
- Test taking damage and healing

---

### **Session 3: Implementing Game Combat (45-60 minutes)**

#### Learning Goals
- Use control flow for game logic
- Implement turn-based combat system
- Practice using objects and calling methods

#### Activities

1. **Review Character Class** (10 min)
   - Demo completed Character class
   - Fix any common bugs students encountered

2. **Design Combat System** (10 min)
   - Turn-based combat flow:
     1. Player chooses action (attack, defend, use item)
     2. Calculate damage
     3. Enemy takes turn
     4. Check if battle is over
     5. Repeat

3. **Code Combat Function Together** (30 min)
   ```cpp
   // In Game class or as standalone function
   void battle(Character& player, Character& enemy) {
       cout << "A wild " << enemy.getName() << " appears!\n";
       
       while (player.isAlive() && enemy.isAlive()) {
           // Display status
           player.displayStats();
           enemy.displayStats();
           
           // Player turn
           cout << "\nYour turn! (1) Attack (2) Defend: ";
           int choice;
           cin >> choice;
           
           if (choice == 1) {
               player.attack(enemy);
           }
           
           // Enemy turn
           if (enemy.isAlive()) {
               enemy.attack(player);
           }
       }
       
       // Battle results
       if (player.isAlive()) {
           cout << "Victory! You defeated " << enemy.getName() << "!\n";
           player.gainExperience(50);
       } else {
           cout << "You were defeated...\n";
       }
   }
   ```

4. **Test Combat** (10 min)
   - Create player and enemy in main()
   - Run battle function
   - Debug any issues together

#### Homework/Lab Work
- Add more combat options (special attacks, defend)
- Implement random damage variation
- Add critical hit chance
- Balance combat (adjust stats so battles aren't too easy/hard)

---

### **Session 4: Adding Items and Inventory (45-60 minutes)**

#### Learning Goals
- Create another class following the same pattern
- Use vectors/arrays to store collections
- Practice class interaction

#### Activities

1. **Design Item Class** (15 min)
   ```cpp
   class Item {
   private:
       string name;
       string description;
       int healAmount;
       int attackBoost;
       
   public:
       Item(string n, string desc, int heal, int atk);
       string getName() const;
       void use(Character& target);
       void displayInfo() const;
   };
   ```

2. **Add Inventory to Character** (20 min)
   - Modify Character.h to include vector of Items
   - Add functions:
     - `void addItem(Item item)`
     - `void useItem(int index)`
     - `void displayInventory()`

3. **Create Starting Items** (10 min)
   ```cpp
   Item healthPotion("Health Potion", "Restores 50 HP", 50, 0);
   Item sword("Iron Sword", "Increases attack by 10", 0, 10);
   ```

4. **Integrate Items into Combat** (15 min)
   - Add "Use Item" option to battle menu
   - Let player select from inventory
   - Apply item effects

#### Homework/Lab Work
- Create 5+ different items
- Add item drops from enemies (random chance)
- Implement max inventory size
- Add item rarity levels (common, rare, legendary)

---

### **Session 5: Building the Game Manager (45-60 minutes)**

#### Learning Goals
- Create a main game loop
- Organize code into a Game class
- Implement game state management

#### Activities

1. **Design Game Class** (10 min)
   ```cpp
   class Game {
   private:
       Character player;
       vector<Character> enemies;
       bool gameRunning;
       int currentLevel;
       
   public:
       Game();
       void start();
       void mainMenu();
       void explore();
       void rest();
       void displayStats();
       void gameLoop();
   };
   ```

2. **Implement Main Menu** (15 min)
   - Welcome screen
   - Player character creation
   - Options: Start Game, Instructions, Quit

3. **Create Game Loop** (20 min)
   ```cpp
   void Game::gameLoop() {
       while (gameRunning && player.isAlive()) {
           cout << "\n=== Hero's Quest ===\n";
           cout << "1. Explore\n";
           cout << "2. View Stats\n";
           cout << "3. Rest\n";
           cout << "4. Quit\n";
           
           int choice;
           cin >> choice;
           
           switch(choice) {
               case 1: explore(); break;
               case 2: displayStats(); break;
               case 3: rest(); break;
               case 4: gameRunning = false; break;
           }
       }
   }
   ```

4. **Implement Explore Function** (15 min)
   - Random encounter chance
   - Create enemy on the fly
   - Initiate battle
   - Reward player if victorious

#### Homework/Lab Work
- Add save/load game functionality
- Create multiple enemy types with different stats
- Implement difficulty levels
- Add story text/narrative elements

---

### **Session 6: Polish and Enhancement (45-60 minutes)**

#### Learning Goals
- Debug and test complete game
- Add quality-of-life features
- Discuss potential GUI implementation

#### Activities

1. **Playtesting Session** (15 min)
   - Students play each other's games
   - Note bugs and balance issues
   - Gather feedback

2. **Bug Fixing Workshop** (20 min)
   - Address common issues together
   - Input validation (what if player enters text instead of number?)
   - Edge cases (what if health goes negative?)

3. **Add Enhancements** (15 min)
   - Color text output (if console supports it)
   - ASCII art for enemies/items
   - Sound effects (console beep)
   - Save high scores to file

4. **Discussion: Console vs GUI** (10 min)
   - Show how game could work with GUI (buttons, graphics)
   - Libraries: SDL, SFML, Qt
   - Same classes, different interface
   - Future project idea!

#### Homework/Lab Work
- Final polish and bug fixes
- Add at least 3 custom features
- Write README explaining how to play
- Prepare for demo presentation

---

### **Session 7: Presentations & Retrospective (30-45 minutes)**

#### Activities

1. **Student Demos** (20 min)
   - Each student shows their game (2-3 min each)
   - Highlight unique features they added
   - Celebrate creativity!

2. **Code Review** (10 min)
   - Look at different implementation approaches
   - Discuss best practices
   - What would we do differently?

3. **Retrospective Discussion** (10 min)
   - What was challenging?
   - What concepts clicked?
   - How did C++ classes make this easier?
   - Where could we take this project next?

4. **Next Steps** (5 min)
   - Ideas for expansion:
     - Multiple levels/dungeons
     - Shops to buy items
     - Party system (multiple heroes)
     - Boss battles
     - Quest system
     - Multiplayer?

---

## � Assessment Rubric (Total: 100 points)

### **Weekly Progress Submissions (40 points)**
- **Each week's feature implementation (2-3 points per week)**
  - Code compiles and runs without errors
  - Implements the week's data structure correctly
  - Follows proper C++ conventions
  - Includes comments explaining data structure usage
  - Demonstrates understanding through implementation

### **Code Quality & Data Structures (30 points)**
- **Correct Implementation (15 points)**
  - Each data structure implemented correctly
  - Proper algorithm implementation (sorting, searching, graph algorithms)
  - Correct Big-O complexity for operations
  
- **Memory Management (10 points)**
  - No memory leaks (verified with valgrind or similar)
  - Proper use of new/delete
  - Correct destructor implementation
  - Proper pointer handling
  
- **Code Organization (5 points)**
  - Clean header/implementation file separation
  - Consistent naming conventions
  - Meaningful variable/function names
  - Proper encapsulation

### **Technical Documentation (15 points)**
- **README.md (5 points)**
  - Compilation instructions
  - How to play the game
  - Features list
  
- **Algorithm Analysis (10 points)**
  - Written analysis of Big-O complexity for major operations
  - Comparison of data structure choices
  - Performance metrics (before/after optimization)
  - Discussion of trade-offs

### **Final Presentation (15 points)**
- **Game Demo (5 points)**
  - Demonstrates working game
  - Shows all major features
  - Handles edge cases gracefully
  
- **Technical Explanation (7 points)**
  - Explains 2-3 data structures in detail
  - Discusses design decisions
  - Shows code examples
  - Answers questions about implementation
  
- **Professionalism (3 points)**
  - Clear communication
  - Well-organized presentation
  - Stays within time limit (5-7 minutes)

---

## 📚 Required Features by Week

| Week | Topic | Required Game Feature | Required Implementation |
|------|-------|----------------------|------------------------|
| 1-2 | C++ Review & OOP | Basic game loop, Character classes | Multi-file project, classes with header/implementation |
| 3 | ADTs & Pointers | Item system with polymorphism | ItemADT interface, derived classes, pointer usage |
| 4 | Linked Lists | Dynamic inventory | Custom linked list implementation (not STL) |
| 5 | Stacks & Queues | Undo system and turn queue | Custom stack and queue (not STL) |
| 6 | Pointers & References | Enemy AI relationships | Proper pointer/reference usage, null checks |
| 7 | Memory Allocation | Dynamic room spawning | Proper new/delete, no memory leaks |
| 8 | Algorithm Efficiency | Performance analysis | Big-O analysis document, timing measurements |
| 9 | Basic Sorting | Inventory sorting with 2 algorithms | Bubble sort and insertion sort from scratch |
| 10 | Advanced Sorting | Leaderboard system | Merge sort and quick sort from scratch |
| 11 | Hash Tables | Fast item lookup | Custom hash table with chaining |
| 12 | BFS/DFS | Map exploration | Graph with BFS and DFS traversal |
| 13 | Shortest Path | Pathfinding AI | Dijkstra's algorithm implementation |
| 14 | BST | Skill tree system | Binary search tree implementation |
| 15 | Advanced Trees | Priority event system | Heap, trie, or AVL implementation |

---

## 🎯 Grading Guidelines

### **Weekly Submissions**
- **Excellent (3 points)**: Feature complete, well-implemented, demonstrates clear understanding
- **Good (2 points)**: Feature works but has minor issues or lacks polish
- **Satisfactory (1 point)**: Feature partially implemented or has significant issues
- **Incomplete (0 points)**: Feature missing or non-functional

### **Data Structure Implementation**
- **Must implement from scratch**: No STL containers for the data structure being learned that week
- **Can use STL for supporting code**: Example—when learning linked lists, can use std::string but not std::list
- **Exception**: Week 11 onwards can use STL for previously learned structures

### **Code Quality Standards**
```cpp
// GOOD: Clear, well-documented
class Inventory {
private:
    InventoryNode* head;  // Linked list head pointer
    int itemCount;        // Total items in inventory
    
public:
    /**
     * Adds an item to the inventory
     * @param item Pointer to item (ownership transferred)
     * @return true if added successfully, false if inventory full
     * Time Complexity: O(1) - inserts at head
     */
    bool addItem(ItemADT* item);
};

// BAD: Unclear, no documentation
class Inv {
    Node* n;
    int c;
public:
    bool add(ItemADT* i);  // What does this do? What's the complexity?
};
```

---

## 💡 Teaching Tips

### **Pacing Strategy**
- **Weeks 1-2**: Let students get comfortable with C++ syntax and project structure
- **Weeks 3-7**: Core data structures—ensure solid understanding before moving on
- **Weeks 8-10**: Algorithm analysis and optimization—connect theory to practice
- **Weeks 11-15**: Advanced structures—show how they solve real problems

### **Common Student Struggles & Solutions**

1. **"I don't know where to start!"**
   - Solution: Provide starter code for week 1-2
   - Give detailed pseudocode for first data structure
   - Pair programming for first implementation

2. **Memory leaks**
   - Solution: Introduce valgrind early
   - Require passing valgrind test for full credit
   - Live demo of tracking down leaks

3. **"Why not just use vector/list from STL?"**
   - Solution: Explain learning objectives
   - Show "black box" problem
   - Promise they can use STL after implementing once

4. **Falling behind**
   - Solution: Weekly check-ins
   - Allow "simplified" versions with reduced points
   - Peer code review sessions

### **Engagement Techniques**

1. **Live Coding Sessions**
   - Implement one data structure together in class
   - Deliberately make mistakes to show debugging
   - Think aloud about design decisions

2. **Code Competitions**
   - "Fastest pathfinding algorithm" competition
   - "Most creative item system" showcase
   - "Best game balance" award

3. **Guest Lectures**
   - Invite game developer to discuss real-world data structure usage
   - Show how AAA games use graphs for AI
   - Demonstrate profiling tools used in industry

4. **Optional Extensions**
   - Offer bonus points for graphics (SFML, SDL)
   - Encourage sound effects
   - Allow networking for multiplayer (advanced)

### **Assessment Flexibility**

- **Grace Days**: Allow 2 late submissions without penalty
- **Revised Submissions**: Accept revisions for 80% credit
- **Alternative Topics**: Student can propose different data structure application
- **Creative Freedom**: Encourage personalization beyond requirements

### **Resource Management**

Provide students with:
- Starter code template for week 1
- Example implementations (after assignment due)
- Style guide for C++ code
- Debugging guide with common errors
- Office hours schedule for help

### **Collaboration Policy**

✅ **Allowed:**
- Discussing algorithms and approaches
- Helping debug syntax errors
- Pair programming during designated times
- Sharing resources and documentation

❌ **Not Allowed:**
- Copying code from classmates
- Using online complete implementations
- Submitting AI-generated code without understanding

---

## 🚀 Extension Ideas for Advanced Students

1. **Graphics**: Use SFML or SDL for visual dungeon
2. **Networking**: Multiplayer dungeon using TCP/IP
3. **AI**: Implement A* pathfinding with heuristics
4. **Procedural Generation**: Generate random dungeons
5. **Save System**: Serialize game state to file
6. **Sound**: Add sound effects and music
7. **Advanced Algorithms**: Implement more complex data structures
8. **Testing**: Write unit tests for all data structures

---

## 📖 Weekly Code Example Snippets

### **Example: Week 4 Inventory Linked List**

```cpp
// Inventory.cpp - Complete implementation example
bool Inventory::addItem(ItemADT* item, int quantity) {
    // Check if inventory is full
    if (isFull()) {
        return false;
    }
    
    // Check if item already exists
    InventoryNode* current = head;
    while (current != nullptr) {
        if (current->item->getName() == item->getName()) {
            current->quantity += quantity;
            delete item;  // Don't need this item object
            return true;
        }
        current = current->next;
    }
    
    // Add new item at head
    InventoryNode* newNode = new InventoryNode(item, quantity);
    newNode->next = head;
    head = newNode;
    itemCount++;
    
    return true;
}

// Destructor - CRITICAL for preventing memory leaks
Inventory::~Inventory() {
    InventoryNode* current = head;
    while (current != nullptr) {
        InventoryNode* next = current->next;
        delete current->item;  // Free item object
        delete current;        // Free node
        current = next;
    }
}
```

### **Example: Week 5 Action Stack**

```cpp
// ActionStack.cpp
void ActionStack::push(const GameAction& action) {
    if (isFull()) {
        // Remove oldest action from bottom
        Node* temp = top;
        Node* prev = nullptr;
        while (temp->next != nullptr) {
            prev = temp;
            temp = temp->next;
        }
        if (prev) prev->next = nullptr;
        delete temp;
        size--;
    }
    
    Node* newNode = new Node();
    newNode->action = action;
    newNode->next = top;
    top = newNode;
    size++;
}

GameAction ActionStack::pop() {
    if (isEmpty()) {
        throw runtime_error("Cannot undo: no actions in history");
    }
    
    Node* temp = top;
    GameAction action = top->action;
    top = top->next;
    delete temp;
    size--;
    
    return action;
}

// In Game.cpp - Using the undo system
void Game::undoLastAction() {
    if (!actionHistory.isEmpty()) {
        GameAction lastAction = actionHistory.pop();
        lastAction.undo(&player);
        cout << "Action undone!\n";
    } else {
        cout << "Nothing to undo.\n";
    }
}
```

### **Example: Week 11 Hash Table**

```cpp
// ItemDatabase.cpp
void ItemDatabase::insert(string name, ItemADT* item) {
    int index = hashFunction(name);
    
    // Check if item already exists
    HashNode* current = table[index];
    while (current != nullptr) {
        if (current->key == name) {
            delete current->value;  // Replace old item
            current->value = item;
            return;
        }
        current = current->next;
    }
    
    // Insert new item at head of chain
    HashNode* newNode = new HashNode();
    newNode->key = name;
    newNode->value = item;
    newNode->next = table[index];
    table[index] = newNode;
    itemCount++;
    
    // Check load factor and resize if needed
    if ((double)itemCount / tableSize > 0.75) {
        resize();
    }
}

ItemADT* ItemDatabase::find(string name) {
    int index = hashFunction(name);
    HashNode* current = table[index];
    
    while (current != nullptr) {
        if (current->key == name) {
            return current->value;  // O(1) average case!
        }
        current = current->next;
    }
    
    return nullptr;  // Not found
}

void ItemDatabase::displayStats() const {
    cout << "Hash Table Statistics:\n";
    cout << "Size: " << tableSize << "\n";
    cout << "Items: " << itemCount << "\n";
    cout << "Load Factor: " << (double)itemCount / tableSize << "\n";
    
    // Show distribution
    int emptyBuckets = 0;
    int maxChainLength = 0;
    
    for (int i = 0; i < tableSize; i++) {
        int chainLength = 0;
        HashNode* current = table[i];
        
        if (current == nullptr) {
            emptyBuckets++;
        } else {
            while (current != nullptr) {
                chainLength++;
                current = current->next;
            }
            maxChainLength = max(maxChainLength, chainLength);
        }
    }
    
    cout << "Empty buckets: " << emptyBuckets << "\n";
    cout << "Max chain length: " << maxChainLength << "\n";
}
```

---

## 🎓 Learning Outcomes

By completing this project, students will be able to:

1. **Implement core data structures from scratch** without relying on standard libraries
2. **Analyze algorithm efficiency** using Big-O notation and empirical testing
3. **Manage dynamic memory** properly without leaks or dangling pointers
4. **Apply data structures to solve real problems** in an integrated application
5. **Make informed decisions** about which data structure to use for different scenarios
6. **Debug complex pointer-based code** using tools like valgrind and gdb
7. **Design object-oriented systems** with proper encapsulation and inheritance
8. **Document code professionally** with clear comments and technical analysis
9. **Present technical work** to peers with clarity and confidence
10. **Think like a software engineer** by considering trade-offs, performance, and maintainability

---

## 📝 Sample Student Project Structure

```
DungeonOfDataStructures/
├── README.md                 # Project documentation
├── Makefile                  # Build automation
├── docs/
│   ├── algorithm-analysis.md
│   ├── design-decisions.md
│   └── performance-metrics.md
├── src/
│   ├── main.cpp
│   ├── Game.h / Game.cpp
│   ├── Character.h / Character.cpp
│   ├── Player.h / Player.cpp
│   ├── Enemy.h / Enemy.cpp
│   │
│   ├── items/
│   │   ├── ItemADT.h
│   │   ├── Weapon.h / Weapon.cpp
│   │   ├── Potion.h / Potion.cpp
│   │   └── Armor.h / Armor.cpp
│   │
│   ├── datastructures/
│   │   ├── Inventory.h / Inventory.cpp
│   │   ├── ActionStack.h / ActionStack.cpp
│   │   ├── TurnQueue.h / TurnQueue.cpp
│   │   ├── ItemDatabase.h / ItemDatabase.cpp
│   │   ├── DungeonMap.h / DungeonMap.cpp
│   │   └── SkillTree.h / SkillTree.cpp
│   │
│   └── algorithms/
│       ├── Sorting.h / Sorting.cpp
│       ├── Searching.h / Searching.cpp
│       └── Pathfinding.h / Pathfinding.cpp
│
└── tests/
    ├── test_inventory.cpp
    ├── test_pathfinding.cpp
    └── run_tests.sh
```

---

## 🔗 Additional Resources for Students

### **C++ References**
- [cppreference.com](https://en.cppreference.com/) - Comprehensive C++ documentation
- [learncpp.com](https://www.learncpp.com/) - Excellent C++ tutorials

### **Data Structures Visualizations**
- [VisuAlgo](https://visualgo.net/) - Animated visualizations of algorithms
- [Data Structure Visualizations](https://www.cs.usfca.edu/~galles/visualization/) - Interactive demos

### **Debugging Tools**
- valgrind - Memory leak detection
- gdb - GNU debugger
- Visual Studio Code debugger

### **Game Development (Optional)**
- [SFML](https://www.sfml-dev.org/) - Simple and Fast Multimedia Library
- [SDL](https://www.libsdl.org/) - Simple DirectMedia Layer

---

## 🎮 Sample Game Session

```
=================================================
    WELCOME TO DUNGEON OF DATA STRUCTURES
=================================================

You wake up in a dark dungeon. Your memory is foggy,
but you recall you're a Data Structures student who
fell asleep studying and somehow ended up here...

Current Location: Starting Chamber
HP: 100/100 | Level: 1 | EXP: 0/100

Available actions:
1. Move (north, south, east, west)
2. Inventory
3. Use Item
4. Stats
5. Save Game
6. Help
7. Quit

> 1 north

You enter the Linked List Corridor.
A corridor where rooms are connected like nodes...

You encounter a Wild Pointer!
Enemy HP: 30/30

Combat Menu:
1. Attack
2. Use Item
3. Run
4. Undo (3 actions remaining)

> 1

You attack for 15 damage!
Wild Pointer attacks for 8 damage!
Your HP: 92/100

> 1

You attack for 15 damage!
Wild Pointer is defeated!

You gained 25 EXP and 10 gold!
Found: Health Potion

Continue...
```

---

## Summary

This semester-long project transforms abstract data structures concepts into a concrete, engaging game development experience. Students will:

- ✅ Build a complete text-based RPG
- ✅ Implement 10+ data structures from scratch
- ✅ Analyze algorithm complexity
- ✅ Manage memory properly
- ✅ Apply CS theory to practical problems

The cumulative nature ensures students see how data structures work together in a real application, while weekly deliverables keep them on track and provide regular feedback opportunities.

---

**Ready to start? Let's build the Dungeon of Data Structures!** 🏰💻

### Minimum Game Features
- ✅ Character class with stats (health, attack, defense)
- ✅ Turn-based combat system
- ✅ At least 3 different enemy types
- ✅ Item class and inventory system
- ✅ Experience and leveling system
- ✅ Game loop with menu options
- ✅ Proper use of header and implementation files
- ✅ Include guards on all headers
- ✅ Input validation
- ✅ Proper encapsulation (private/public)

### Bonus Features (Optional)
- 🌟 Save/Load game to file
- 🌟 Multiple character classes (warrior, mage, rogue)
- 🌟 Shop system
- 🌟 Equipment system (weapons, armor)
- 🌟 Status effects (poison, stun, buff)
- 🌟 ASCII art
- 🌟 Story/narrative
- 🌟 Boss battles
- 🌟 Achievement system

---

## 📝 Assessment Rubric

### Code Quality (40%)
- Proper class structure and organization
- Correct use of header/implementation files
- Include guards present
- Good variable naming
- Comments explaining complex logic
- No memory leaks (if using dynamic memory)

### Functionality (30%)
- Game runs without crashes
- All core features implemented
- Combat system works correctly
- Input validation handles errors
- Game loop functions properly

### Creativity (15%)
- Unique features or mechanics
- Interesting enemy types or items
- Engaging gameplay
- Polish and presentation

### Code Understanding (15%)
- Can explain design decisions
- Understands OOP concepts used
- Can identify areas for improvement
- Participates in class discussions

---

## 🎓 Key Concepts Reinforced

### Week 1 Concepts
- ✅ Variables and data types (int, string, bool)
- ✅ Console I/O (cout, cin)
- ✅ Control flow (if/else, while loops, switch)
- ✅ Functions
- ✅ Basic syntax and compilation

### Week 2 Concepts
- ✅ Classes and objects
- ✅ Header files (.h) and implementation files (.cpp)
- ✅ Include guards
- ✅ Constructors
- ✅ Member functions
- ✅ Public vs private access
- ✅ Encapsulation
- ✅ Object interaction

### Additional Concepts
- ✅ Game loop design
- ✅ State management
- ✅ Random number generation
- ✅ File I/O (for save/load)
- ✅ Collections (vector/array)
- ✅ Project organization

---

## 💡 Teaching Tips

### Pacing
- Don't rush! It's okay if this takes 2-3 weeks
- Let students experiment and break things
- Encourage peer programming and collaboration

### Common Pitfalls
- **Forgetting semicolons** - Classic C++ mistake!
- **Include guard typos** - Hard to debug
- **Circular dependencies** - Plan file structure carefully
- **Infinite game loops** - Make sure there's an exit condition
- **Input validation** - Always assume users will type something unexpected

### Engagement Strategies
- Let students suggest game features
- Have "feature of the day" where one student demos their addition
- Create a class "high score" board
- Hold mini-tournaments with different versions

### Differentiation
- **Struggling students:** Provide more starter code, pair with stronger student
- **Advanced students:** Suggest bonus features, introduce new concepts (polymorphism, inheritance)
- **Visual learners:** Use diagrams to show object relationships
- **Kinesthetic learners:** Have them act out game logic (role-play as objects)

---

## 🔗 Resources for Students

### C++ References
- [cplusplus.com](http://www.cplusplus.com/) - Function reference
- [learncpp.com](https://www.learncpp.com/) - Tutorials
- Course textbook sections on classes and OOP

### Game Development Inspiration
- Classic text games: Zork, Adventure, Hunt the Wumpus
- Modern indie games with simple mechanics
- Game design patterns

### Tools
- VS Code with C++ extension
- Debugger practice
- Git for version control (optional)

---

## 🚀 Future Extensions

### Week 3+ Ideas
- Add inheritance (Hero, Warrior, Mage inherit from Character)
- Use polymorphism for different enemy AI
- Implement file I/O for save systems
- Create multiple dungeon levels
- Add a shop/economy system

### GUI Version (Later Semester)
- Introduce SDL or SFML library
- Convert text menu to buttons
- Add sprite graphics
- Play sound effects
- Mouse input for combat

### Multiplayer (Advanced)
- Turn-based network play
- Shared world state
- Chat system
- Trading between players

---

## ✨ Success Metrics

Students successfully completed this project when they can:
- ✅ Compile and run a multi-file C++ program
- ✅ Explain the purpose of each class in their game
- ✅ Demonstrate proper use of header and implementation files
- ✅ Show working game with all core features
- ✅ Debug their own code when errors occur
- ✅ Explain how OOP made their code more organized
- ✅ Suggest improvements to their own code
- ✅ Have fun and be proud of what they created! 🎉

---

## 📅 Suggested Timeline

**Week-by-Week Breakdown:**
- **Week 1:** Sessions 1-2 (Planning + Character class)
- **Week 2:** Sessions 3-4 (Combat + Items)
- **Week 3:** Sessions 5-6 (Game manager + Polish)
- **Week 4:** Session 7 (Presentations)

**Flexible Schedule:**
- Can be condensed to 2 weeks for faster-paced classes
- Can be extended to 5-6 weeks with more features
- Works well as a culminating project for the first month

---

## 🎮 Let's Build Something Awesome!

This project bridges the gap between learning syntax and building real applications. By the end, students will have a playable game they can show friends and family - and more importantly, they'll understand how to structure a C++ program from scratch!

**Remember:** The goal isn't to build the next AAA game. The goal is to have fun, learn C++, and see how code comes to life in an interactive program. Every bug fixed is a learning opportunity, and every feature added is a victory! 🌟

---

*This lesson plan is designed to be flexible. Adapt it to your class pace, student needs, and available time. The most important thing is that students are engaged, learning, and having fun with C++!*
