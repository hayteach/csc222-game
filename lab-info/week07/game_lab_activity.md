# Game Lab Activity: Linked String & Bag Integration

## Overview

This guide documents the integration of **Lab 07 (Linked String ADT)** and **Homework 05 (Linked Bag Template)** into the existing dungeongame project.  Rather than submitting separate standalone programs, students will implement both ADTs directly in the game codebase and interact with them via an in-game menu.

This approach provides an engaging, practical context for using linked-list data structures while reinforcing the concepts students are learning.

---

## Files Added

### 1. `dungeongame/include/dungeongame/LinkedString.h`

**Purpose:**  Header file for the linked-list based string ADT (Lab 07).

**Key components:**
- `LinkedString` class with a private `Node` struct (holds a single `char` and a pointer to the next node).
- **Constructors:**  default, copy constructor, assignment operator.
- **Destructor:**  must clean up all allocated nodes.
- **Core methods:**
  - `int length() const` – count and return node count.
  - `bool equals(const LinkedString& other) const` – compare character sequence.
  - `char get(int index) const` – retrieve character at index (throw if out of range).
  - `void set(int index, char c)` – modify character at index.
  - `std::string toStdString() const` – convert to standard string for display.

### 2. `dungeongame/src/LinkedString.cpp`

**Purpose:**  Implementation file for LinkedString.

**Implementation notes:**
- Constructor from `std::string` iterates and appends each character.
- Copy constructor and assignment operator use a `copyFrom()` helper.
- `length()` traverses the list counting nodes.
- `equals()` compares two lists node-by-node and checks both reach null simultaneously.
- `get()` and `set()` traverse to the requested index; throw `std::out_of_range` on invalid access.
- Destructor iterates and deallocates all nodes.

### 3. `dungeongame/include/dungeongame/LinkedBag.h`

**Purpose:**  Header file for the linked-list template Bag ADT (Homework 05).

**Key components:**
- `LinkedBag<ItemType>` template class with a private `Node` struct (holds `ItemType` data and a pointer to the next node).
- **Constructors:**  default, copy constructor, assignment operator.
- **Destructor:**  clean up all nodes.
- **Core methods:**
  - `int getCurrentSize() const` – return item count.
  - `bool isEmpty() const` – check if count is zero.
  - `bool add(const ItemType& newEntry)` – prepend new item (always succeeds).
  - `bool remove(const ItemType& anEntry)` – find and remove first matching item; return success status.
  - `void clear()` – delete all nodes and reset.
  - `bool contains(const ItemType& anEntry) const` – linear search.
  - `std::vector<ItemType> toVector() const` – return all items as a vector.

---

## LinkedList vs LinkedBag: Understanding When to Use Each

Before diving into implementation, let's understand the key difference between `LinkedList` (from Week 03) and `LinkedBag` (HW 05). Both use linked nodes, but they serve different purposes:

| Feature | **LinkedList** | **LinkedBag** |
|---------|---|---|
| **Purpose** | General-purpose ordered sequence | Unordered collection (membership-based) |
| **Order** | ✅ Maintains insertion order | ❌ Order not guaranteed |
| **Add** | `append()`, `prepend()`, `insertAt(index)` | `add()` (always efficient, to front) |
| **Remove** | `removeAt(index)` (by position) | `remove(value)` (by value/contents) |
| **Access** | `get(index)` ✅ Random access | ❌ No indexing; use `toVector()` |
| **Search** | ❌ Manual traversal | `contains(value)` ✅ Built-in |
| **Use Case** | *"I need these items in a specific order"* | *"I need to know what items I have"* |

### Real-World Analogy

- **LinkedList** = a **queue at the DMV** – order *matters*; you care who's before/after you.
- **LinkedBag** = a **bag of marbles** – you care *what's in it*, not the order.

### Example: When to Use LinkedList

```cpp
// Use LinkedList when ORDER matters (e.g., task sequence)
LinkedList<std::string> taskList;
taskList.append("Morning combat");   // Add as FIRST task
taskList.append("Visit merchant");   // Add as SECOND task  
taskList.append("Quest reward");     // Add as THIRD task

// Access items by their POSITION
std::string nextTask = taskList.get(0);  // Get first task (index 0)
taskList.removeAt(0);                    // Remove first task after completing
nextTask = taskList.get(0);              // New first task automatically shifts
```

**Why LinkedList?** We care about the *sequence* of tasks. The first task is "Morning combat", not just any task.

### Example: When to Use LinkedBag  

```cpp
// Use LinkedBag when you ONLY care about membership (e.g., loot collection)
LinkedBag<Item> lootBag;                    // Unordered collection
lootBag.add(Item("Sword", 50));            // Add loot (order irrelevant)
lootBag.add(Item("Shield", 40));
lootBag.add(Item("Potion", 25));

// Key question: "Do I have this item?"
if (lootBag.contains(Item("Sword", 50))) {
    std::cout << "Sword is in loot bag!" << std::endl;
    lootBag.remove(Item("Sword", 50));     // Use/remove it
}

// To see all items, convert to vector (order not guaranteed)
auto allLoot = lootBag.toVector();
for (auto& item : allLoot) {
    std::cout << item.name << std::endl;   // Print in unpredictable order
}
```

**Why LinkedBag?** We don't care if the Sword was added first or third. We only ask: "Is this item in my loot bag?"

### Why This Matters for Our Game

- **LinkedList (Menu Option 11)** = Educational demo showing *positional* operations (get by index, insert at position, etc.).
- **LinkedBag (Loot System, Grimoire)** = Practical system: items in a loot bag have *no inherent order*; you just check membership and iterate through all items.

When you defeat an enemy and pick up loot, **do you care if the sword was the 1st or 3rd item in your bag?** No. You only care: "Do I have a sword?" → That's a LinkedBag.

---

## Files Modified

### 4. `dungeongame/include/dungeongame/Game.h`

**Changes:**
- Added `#include "LinkedString.h"` and `#include "LinkedBag.h"` headers.
- Added method declarations:
  - `void runLinkedStringLab();` – demo method for Lab 07 activity.
  - `void runBagDemo();` – demo method for HW 05 activity.
  - `void runNPCGroupDemo();` – stub for earlier content.
  - `void runNPCSpawnerDemo();` – stub for earlier content.

### 5. `dungeongame/src/Game.cpp`

**Changes:**
- Added `#include <vector>` and `#include <limits>` for std::numeric_limits.
- **Menu updates (displayMenu):**
  - Option 21: "Linked String Lab (lab07)"
  - Option 22: "Linked Bag Demo (hw05)"
- **processChoice() switch:**
  - Case 21 calls `runLinkedStringLab()`.
  - Case 22 calls `runBagDemo()`.
  - Cases 19–20 call stub demos.
- **Implementation of runLinkedStringLab():**
  - Prompts user for two strings.
  - Creates `LinkedString` objects from input.
  - Displays length of each string.
  - Checks if strings are equal.
  - Demonstrates modifying the first character to 'X'.
- **Implementation of runBagDemo():**
  - Creates a `LinkedBag<std::string>`.
  - Adds sample fruits ("apple", "banana", "cherry", "date", "banana").
  - Checks `contains()` for "banana".
  - Calls `remove()` to delete one "banana".
  - Uses `toVector()` to display remaining items.
  - Calls `clear()` and verifies `isEmpty()`.
- **Stub implementations:**
  - `runNPCGroupDemo()` and `runNPCSpawnerDemo()` print placeholder messages.

### 6. `dungeongame/include/dungeongame/NPCSpawner.h`

**Changes (fixes):**
- Removed duplicate constructor declaration (`NPCSpawner();` followed by `NPCSpawner() = default;`).
- Changed **all methods** from private to **public** (they were previously inaccessible from `Game.cpp`).
- Kept the definition in `NPCSpawner.cpp` to populate the queue with starter enemies.

---

## Implementation Order for Students

If you are implementing this as a lab activity, follow these steps in order:

### **Step 1: Implement LinkedString.h/cpp (Lab 07)**

1. Copy/create the `LinkedString.h` header with:
   - Private `Node` struct.
   - Public method declarations.
   - Private `copyFrom()` helper.
   - **Add design comments** (see below):
   ```cpp
   class LinkedString {
       // LinkedString uses a linked list of CHARACTERS.
       // Each node holds ONE char, not an arbitrary data type.
       // WHY? Strings have a natural linear order: 'h' then 'e' then 'l'...
       // This is fundamentally different from a Bag, where order is meaningless.
       
       // LinkedString has:
       // - length() – count characters
       // - equals() – compare strings character-by-character
       // - get(index) – access the NTH character (position matters!)
       // - set(index) – modify a character at a position
       // 
       // These operations make sense for a STRING (ordered sequence)
       // but would be wrong for a BAG (unordered collection).
       
   private:
       Node* headPtr;
   };
   ```

2. Implement `LinkedString.cpp`:
   - All constructors, destructor, assignment operator.
   - `length()`, `equals()`, `get()`, `set()`, `toStdString()`.

3. **Test LinkedString independently** before integrating:
   ```cpp
   LinkedString s1("hello");
   LinkedString s2 = s1;
   assert(s1.length() == 5);
   assert(s1.equals(s2));
   s1.set(0, 'H');
   assert(s1.get(0) == 'H');
   ```

### **Step 2: Implement LinkedBag.h (Homework 05)**

1. Create `LinkedBag.h` as a template header with:
   - Private `Node` struct and `itemCount`.
   - All required methods as inline templates.
   - **Design Note:** Unlike LinkedList, LinkedBag has NO `insertAt()` or `removeAt(index)` methods. 
     - WHY? A bag is *unordered*, so position doesn't matter. We add to the front (always efficient) and remove by *value* (by contents).

2. **Add design rationale comments to LinkedBag.h**:
   ```cpp
   template<typename ItemType>
   class LinkedBag {
   private:
       // Unlike LinkedList which provides get(index) and insertAt(index),
       // LinkedBag has NO index-based operations. WHY?
       // A bag is an unordered collection. Position doesn't matter.
       // We only care: "Is this item in the bag?" (membership query)
       Node* headPtr;
       int itemCount;
   
   public:
       // Efficient add: always insert at the front (O(1) time)
       // We DON'T care where items go, so front is fastest
       bool add(const ItemType& newEntry) { ... }
       
       // Remove BY VALUE, not by position
       // This is fundamentally different from LinkedList::removeAt(index)
       // We search through the list to find the matching item
       bool remove(const ItemType& anEntry) { ... }
       
       // contains() does a linear search
       // This is the PRIMARY operation on a bag: check membership
       bool contains(const ItemType& anEntry) const { ... }
   };
   ```

3. **Test LinkedBag independently**:
   ```cpp
   LinkedBag<std::string> bag;        // Create unordered collection
   bag.add("apple");                  // Add items (order irrelevant)
   bag.add("banana");                 // Both items now in the bag
   assert(bag.getCurrentSize() == 2);
   
   // Check membership (not position!)
   assert(bag.contains("apple"));     // Is "apple" in the bag?
   assert(!bag.isEmpty());
   
   // Remove BY VALUE, not by position  
   assert(bag.remove("apple"));       // Remove what we added
   
   // Note: CANNOT do bag.get(0) or bag.removeAt(1)
   // Those don't exist in a bag (unlike LinkedList)
   ```

### **Step 3: Integrate into Game.h/Game.cpp**

1. Update `Game.h`:
   - Add includes for `LinkedString.h`, `LinkedBag.h`, `Spell.h`, `Grimoire.h`.
   - Add private members: `LinkedBag<Item> lootBag;` and `Grimoire grimoire;`.
   - Add method declarations for loot and grimoire systems.

2. Update `Game.cpp` to include design comments:
   ```cpp
   void Game::processCombat(NPC& enemy) {
       // ...
       if (!enemy.isAlive()) {
           // Generate loot and add to the loot bag
           // NOTE: We use LinkedBag<Item> (not LinkedList<Item>) because:
           // 1. Loot order is irrelevant (bag of items on the ground)
           // 2. We only ask: "Do I have a sword?" (membership query)
           // 3. Adding is fast (always to front)
           // 4. Searching for specific loot is easy (contains())
           
           Item loot(enemy.getName() + " Loot", lootValue);
           lootBag.add(loot);  // Order doesn't matter; bag doesn't care
           cout << "Dropped into loot bag!" << endl;
       }
   }
   ```

3. Add Grimoire design comments:
   ```cpp
   class Grimoire {
   private:
       // Spells are stored in a LinkedBag because:
       // - You don't cast the "3rd spell"; you cast "Lightning"
       // - Order of learning spells doesn't affect gameplay
       // - Primary question: "Do I know this spell?" (membership)
       LinkedBag<Spell> spells;
       
   public:
       // "Learn" a spell = add it to the bag
       bool learnSpell(const Spell& spell) { return spells.add(spell); }
       
       // "Know" a spell = check if it's in the bag
       bool knowsSpell(const Spell& spell) const { return spells.contains(spell); }
   };
   ```

4. **Add menu options and implementations:**
   - Option 21: `runLinkedStringLab()` – interactive LinkedString demo.
   - Option 22: `runBagDemo()` – interactive LinkedBag demo.
   - Option 23: `viewGrimoire()` – display all learned spells.
   - Option 24: `handleLootBag()` – view and transfer loot.

5. **Fix NPCSpawner.h** (if not already done):
   - Remove duplicate constructor.
   - Make methods public.

6. **Compile and test:**
   ```bash
   # From project root, compile the dungeongame
   python3 build.py build
   
   # Then run the game
   python3 build.py run
   
   # Or compile and run in one command
   python3 build.py build_run
   ```

7. **Run the game and select:**
   - Option 21 (Linked String Lab) – enter "hello" and "world", then explore.
   - Option 22 (Linked Bag Demo) – watch the bag being populated and queried.
   - Option 23 (View Grimoire) – see your starting spells.
   - Option 24 (Check Loot Bag) – collect and manage defeated enemy drops.

---

## How to Test

### **Standalone Tests** (before full integration)

Create temporary test files like `test_linkedstring.cpp` and `test_linkedbag.cpp` to verify each ADT independently:

```cpp
// test_linkedstring.cpp
#include <cassert>
#include "LinkedString.h"
using namespace dungeongame;

int main() {
    LinkedString a("cat");
    LinkedString b("cat");
    assert(a.equals(b));
    assert(a.length() == 3);
    assert(a.get(0) == 'c');
    a.set(0, 'C');
    assert(a.get(0) == 'C');
    std::cout << "LinkedString tests passed!\n";
    return 0;
}
```

Compile and run:
```bash
g++ -std=c++17 -Iinclude/dungeongame test_linkedstring.cpp src/LinkedString.cpp -o test_linkedstring
./test_linkedstring
```

### **Game Menu Tests** (after integration)

Launch the game and exercise the new menu options:

1. **Option 21 (Linked String Lab):**
   - Enter "hello" for the first string.
   - Enter "world" for the second string.
   - Observe: lengths printed, equality check (should be false).
   - Observe: first character changed to 'X', new string displayed.

2. **Option 22 (Linked Bag Demo):**
   - Observe: fruits being added to the bag.
   - Observe: size and "contains" queries.
   - Observe: removal and final contents.

---

## Memory Management Checklist

Both ADTs use dynamic allocation, so ensure:

- ✓ Every `new` in a constructor is matched by a `delete` in the destructor.
- ✓ Copy constructor performs a **deep copy** (creates new nodes, doesn't share pointers).
- ✓ Assignment operator avoids self-assignment and cleans up old data before copying.
- ✓ All edge cases are handled (empty list, single node, out-of-bounds access).

**Optional:** Use `valgrind` (or `leaks` on macOS) to check for memory leaks:
```bash
leaks -atExit -- ./dungeongame.out
```

---

## Connection to Lab 07 & Homework 05

| Assignment   | File(s) | In-Game Menu | Purpose |
|--------------|---------|---|---------|
| **Lab 07**   | `LinkedString.h`, `LinkedString.cpp` | Option 21 | Demonstrate string ADT with length, equals, get, set. |
| **Homework 05** | `LinkedBag.h` (template) | Option 22 | Demonstrate generic bag container with add, remove, contains, toVector. |

Students can reuse these implementations when submitting their lab/homework archives; the game serves as both a testing ground and a proof of concept.

---

## Optional Enhancement: Deque vs Queue Implementation

As an optional bonus or discussion topic, you may explore replacing certain container types in the loot and spell systems with a **Queue** or **Deque** (Double-Ended Queue). This exercise reinforces understanding of different ADT behaviors.

### When Would You Use Queue vs Deque vs Bag?

| Use Case | Current Choice | Alternative | Why Alternative? |
|----------|---|---|---|
| **Loot collection** | `LinkedBag<Item>` | `Queue<Item>` | Process loot FIFO (first defeated, first looted) |
| **Spell learning** | `LinkedBag<Spell>` | `Deque<Spell>` | Access newest spells first; remove from either end |
| **Enemy spawning** | Random (unordered) | `Queue<NPC>` | Spawn enemies in arrival order |

### Example: Converting Loot System to Queue

**Current implementation (Bag):**
```cpp
LinkedBag<Item> lootBag;
lootBag.add(Item("Sword", 50));      // Add to front (position irrelevant)
lootBag.add(Item("Shield", 30));     // Add to front again
auto allLoot = lootBag.toVector();   // Get all items
```

**To convert to Queue (FIFO):**

Create a simple `Queue.h` header (if not already provided):
```cpp
template<typename ItemType>
class Queue {
private:
    Node* frontPtr;
    Node* backPtr;
    int itemCount;
    
public:
    bool enqueue(const ItemType& newEntry) { /* add to back */ }
    bool dequeue(ItemType& fruitToRemove) { /* remove from front */ }
    bool peekFront(ItemType& fruitToTest) const { /* view front */ }
    int getCurrentSize() const { return itemCount; }
    bool isEmpty() const { return itemCount == 0; }
};
```

**Updated Game.cpp to use Queue:**
```cpp
// Change member variable:
// OLD: LinkedBag<Item> lootBag;
// NEW:
Queue<Item> lootBag;

void Game::processCombat(NPC& enemy) {
    // ...
    if (!enemy.isAlive()) {
        // Now loot is processed FIFO (defeated enemies' loot in order)
        Item loot(enemy.getName() + " Loot", lootValue);
        lootBag.enqueue(loot);  // Enqueue to back of the queue
        cout << "Dropped into loot queue!" << endl;
    }
}

void Game::handleLootBag() {
    Item loot;
    if (lootBag.dequeue(loot)) {  // Remove from front (FIFO)
        cout << "Looted: " << loot.name << " (value: " << loot.value << ")" << endl;
        // Add to inventory
    }
}
```

**Key differences:**
- `add()` → `enqueue()` (add to back)
- `remove()` → `dequeue()` (remove from front)
- **Ordering:** Items are processed in the order they were defeated (FIFO)
- **Use case:** "First enemy defeated, first loot claimed"

### Example: Converting Spell System to Deque

**Current implementation (Bag):**
```cpp
Grimoire grimoire;  // Wraps LinkedBag<Spell>
grimoire.learnSpell(spell1);  // Learn spell 1
grimoire.learnSpell(spell2);  // Learn spell 2
// No particular order maintained
```

**To convert to Deque (more recent spells accessible first):**

Create a simple `Deque.h` header:
```cpp
template<typename ItemType>
class Deque {
private:
    Node* frontPtr;
    Node* backPtr;
    int itemCount;
    
public:
    // Add/remove from EITHER end
    bool addFront(const ItemType& newEntry) { ... }
    bool addBack(const ItemType& newEntry) { ... }
    bool removeFront(ItemType& entryToRemove) { ... }
    bool removeBack(ItemType& entryToRemove) { ... }
    bool peekFront(ItemType& entryToTest) const { ... }
    bool peekBack(ItemType& entryToTest) const { ... }
    int getCurrentSize() const { return itemCount; }
};
```

**Updated Grimoire to use Deque:**
```cpp
class Grimoire {
private:
    Deque<Spell> spells;  // Change from LinkedBag to Deque
    
public:
    // "Learn" a spell – add to FRONT (most recent spell)
    bool learnSpell(const Spell& spell) { 
        return spells.addFront(spell); 
        // Comment: Newest spells are at the front for quick access!
    }
    
    // "Forget" a spell – remove from front (forget most recent)
    bool forgetMostRecentSpell(Spell& spell) { 
        return spells.removeFront(spell); 
    }
};
```

**Key differences:**
- `add()` at front → `addFront()` (newest spells accessible immediately)
- Can `removeFront()` or `removeBack()` (forget newest or oldest spells)
- **Ordering:** Most recently learned spells are at the front
- **Use case:** "When selecting a spell to cast, I might want to access recently learned spells first"

### Discussion Questions for Students

1. **Why would a Queue be better for loot than a Bag?**
   - Answer: Fairness (FIFO); loot from earlier battles is claimed first.

2. **Why would a Deque be better for spells than a Bag?**
   - Answer: Recent spells are accessible first; students can build "recently learned" UI features.

3. **Which ADT is still better for the Grimoire's "knows this spell?" query?**
   - Answer: Still a Bag! Because the primary question is "Do I have Fireball?" (membership), not "Which spell did I learn most recently?"
   - **Key insight:** Different ADTs excel at different questions. Use the right tool for the job.

4. **What are the tradeoffs?**
   - Bag: O(n) search, O(1) add, unordered—best for membership queries.
   - Queue: O(n) search, O(1) enqueue/dequeue, FIFO order—best for task processing.
   - Deque: O(n) search, O(1) add/remove at either end—best for flexible, ordered access.

---

## Bonus Feature: Loot System & Spell Grimoire

Beyond the basic ADT demonstrations, the game now includes two practical systems that showcase real-world use of linked-list based containers:

### **Loot System** (using `LinkedBag<Item>`)

**How it works:**
- When a player defeats an enemy (via menu option 7 or encounters), the enemy drops a **loot item** into a persistent `LinkedBag<Item>` called `lootBag`.
- The loot item is created with the enemy's name and a randomized value (10–40 gold).
- Players can access **menu option 24** to view all collected loot, and transfer it to their main inventory.

**Demonstrates:**
- `LinkedBag::add()` – items are inserted as they are defeated enemies.
- `LinkedBag::toVector()` – display all loot items in a readable list.
- `LinkedBag::clear()` – clear the bag after transferring to inventory.
- Practical use case: managing temporary item collections before permanent storage.

**Code integration:**
```cpp
// In processCombat() after enemy is defeated:
Item loot(enemy.getName() + " Loot", lootValue);
lootBag.add(loot);
cout << "\"" << loot.name << "\" dropped into loot bag!" << endl;
```

### **Spell Grimoire** (using `LinkedBag<Spell>` via `Grimoire` wrapper)

**How it works:**
- The player starts with a few learned spells (Fireball, Ice Storm, Lightning) stored in a `Grimoire` object.
- The `Grimoire` class wraps a `LinkedBag<Spell>` to provide spell-specific operations.
- Players can access **menu option 23** to view all learned spells with mana costs and damage values.
- (Future enhancement) Players can cast spells from their grimoire.

**Demonstrates:**
- `Spell` class – a custom ADT that uses `LinkedString` for spell names (connecting Lab 07).
- `LinkedBag<Spell>::add()` – learn new spells.
- `LinkedBag<Spell>::contains()` – check if a spell is known.
- `LinkedBag<Spell>::toVector()` – retrieve all learned spells for display.
- Wrapper pattern – `Grimoire` provides a clean interface around `LinkedBag<Spell>`.

**Code integration:**
```cpp
// Spell class constructor uses LinkedString:
Spell("Fireball", /*mana*/20, /*damage*/30, "deals 30 fire damage");

// Grimoire uses LinkedBag:
grimoire.learnSpell(spell);
auto spells = grimoire.getAllSpells(); // returns vector<Spell>
```

---

## Files Added for Loot & Grimoire

### `dungeongame/include/dungeongame/Spell.h`
A simple spell ADT that:
- Stores spell name as a `LinkedString` (demonstrating Lab 07 reuse).
- Includes mana cost, damage, and effect description.
- Supports comparison (`operator==`) for use in `LinkedBag<Spell>`.

### `dungeongame/src/Spell.cpp`
Implementation of the `Spell` class, including the equality operator.

### `dungeongame/include/dungeongame/Grimoire.h`
A wrapper class that:
- Encapsulates a `LinkedBag<Spell>` for clean spell management.
- Provides methods: `learnSpell()`, `knowsSpell()`, `forgetSpell()`, `getAllSpells()`, `clear()`.
- Uses no `.cpp` file (all methods are inline in the header).

---

## Updated Files for Loot & Grimoire

### `dungeongame/include/dungeongame/Game.h`
**Additions:**
- `#include "Spell.h"` and `#include "Grimoire.h"`
- Private member: `LinkedBag<Item> lootBag;` – stores defeated enemy drops.
- Private member: `Grimoire grimoire;` – stores player's learned spells.
- Method declarations:
  - `handleLootBag()` – view and manage loot.
  - `transferLootToInventory()` – move loot to inventory.
  - `viewGrimoire()` – display all learned spells.
  - `learnNewSpell()` – add spell to grimoire.
  - `castSpellFromGrimoire()` – cast a known spell.
  - `initializeGrimoire()` – populate with starter spells.

### `dungeongame/src/Game.cpp`
**Modifications:**
- Constructor now calls `initializeGrimoire()` to give player starting spells.
- Menu options expanded:
  - **Option 23:** "View Grimoire (learned spells)" → calls `viewGrimoire()`
  - **Option 24:** "Check Loot Bag" → calls `handleLootBag()`
- `processCombat()` updated: when enemy is defeated, a loot item is created and added to `lootBag`.
- New method implementations for all grimoire and loot operations.

---

## Testing the Loot System & Grimoire

### **Test Loot System:**
1. Launch the game: `./dungeongame.out`
2. Select **Option 7** "Encounter Enemy (demo)" to fight a Goblin.
3. Defeat the Goblin by choosing action 1 (Attack) repeatedly.
4. Observe the message: `*** Goblin Loot (value: XX) dropped into loot bag! ***`
5. Select **Option 24** "Check Loot Bag" to see collected loot.
6. Choose option 1 to transfer loot to your inventory.
7. Verify in **Option 9** (Show Inventory) that the loot item now appears.

### **Test Grimoire:**
1. Launch the game.
2. Select **Option 23** "View Grimoire (learned spells)".
3. Observe your three starter spells:
   - Fireball (20 mana, 30 damage)
   - Ice Storm (25 mana, 35 damage)
   - Lightning (15 mana, 25 damage)
4. (Future) Select a spell to cast and see the effect.

---
## Connection Back to Lab 07 & HW 05

The loot and grimoire systems show **real-world application** of the ADTs:

| ADT | Used In | Purpose |
|-----|---------|----------|
| `LinkedString` (Lab 07) | `Spell` class | Spell names stored as linked lists of characters |
| `LinkedBag<Item>` (HW 05) | Loot system | Temporary container for enemy drops |
| `LinkedBag<Spell>` (HW 05) | Grimoire | Persistent storage of learned spells |

Students see how these component ADTs combine to create higher-level game systems, reinforcing the principle of **composability** in software design.

---


