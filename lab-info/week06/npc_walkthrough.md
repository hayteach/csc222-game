# NPC Refactor & Pointer Lab Walkthrough

This walkthrough corresponds to the refactor plan (`refactor_npc_plan.md`) and the lab activity (`game_lab_activity.md`).  It provides detailed, chronological steps to convert the existing `Enemy` class into a generic `NPC` hierarchy and to implement the pointer-based exercises required by the Week 06 assignment.

Follow each numbered section in order; the commands and code snippets can be copy/pasted into your repository.

---

## 1. Rename `Enemy` to `NPC`

1. In the `dungeongame/include/dungeongame` directory, rename the header:
   ```bash
   mv Enemy.h NPC.h
   ```

2. Update the class declaration inside the new `NPC.h`:
   ```diff
   -class Enemy : public Character {
   +class NPC : public Character {
   ```
   Change constructor name and any comments referencing `Enemy`.

3. Rename the source file and modify its contents:
   ```bash
   mv src/Enemy.cpp src/NPC.cpp
   ```
   Inside `NPC.cpp`:
   ```diff
   -#include "Enemy.h"
   +#include "NPC.h"
   
   namespace dungeongame {
-    Enemy::Enemy(const string& name, int hp, int attack, int def, int exp, int gold)
+    NPC::NPC(const string& name, int hp, int attack, int def, int exp, int gold)
   ```
   Change return types, comments, and method definitions accordingly.

4. Update all references to `Enemy` across the project (search/replace). Key files include:
   - `Game.h`/`.cpp`
   - `EnemyGroup.h`/`.cpp` (soon to be `NPCGroup`)
   - `EnemySpawner.h`/`.cpp` (soon to be `NPCSpawner`)
   - `tests/combat_test.cpp`

   For example, in `Game.h`:
   ```diff
   -#include "Enemy.h"
   +#include "NPC.h"
   
   -EnemySpawner spawner;
   +NPCSpawner spawner;
   ```


## 2. Update containers to use pointers and rename classes

This section shows exactly how pointer-based storage behaves in practice.  You'll
modify the existing `EnemyGroup` container to hold `NPC*` rather than object
values, then add print statements so that running the program clearly outputs
pointer addresses.  Later we contrast that output with a raw array to discuss
contiguous vs. scattered memory.  As you edit the code, compile and run the
game or pointer lab menu option to observe the diagnostic output.

1. Rename `EnemyGroup.h`/`.cpp` to `NPCGroup.h`/`.cpp` and change the class name accordingly.  The goal is to move from storing objects by value to storing pointers, which allows demonstration of pointer arithmetic and memory layout during the lab.
   ```cpp
   class NPCGroup {
   private:
       std::vector<NPC*> npcs; // pointers rather than objects
   public:
       void add(NPC* p) { 
           npcs.push_back(p);
           std::cout << "Added NPC at " << static_cast<void*>(p) << "\n";
       }
       
       NPC* operator[](size_t idx) { return npcs[idx]; }
       
       void printAddresses() const {
           std::cout << "NPC addresses (vector order):\n";
           for (auto p : npcs) {
               std::cout << "  " << static_cast<void*>(p) << "\n";
           }
       }
   };
   ```
   **Explanation for students:** after adding a few NPCs, call `printAddresses()` to observe whether the pointers are contiguous (they will not be when using `new` per element).  You can then allocate a raw array (`NPC* arr = new NPC[n]`) and compare the printed addresses to see the difference between contiguous and scattered allocations.
   This class and its print helper form the core of the pointer‑container exercise.

   _Where to add NPCs in the game?_  A convenient spot is in `Game.cpp` during the spawn/init phase or inside the menu options that create enemies for combat.  For example, in the `Game::setup()` or constructor you might write:
   ```cpp
   NPCGroup group;
   group.add(new NPC("goblin",8,2,0,10,3));
   group.add(new Boss("ogre",30));
   group.printAddresses();
   ```
   or inside the menu handler when option 7 (Encounter Enemy) is selected, create and store the pointer there.  This ensures the output appears during normal gameplay, letting students see the debug prints as part of running the CAM.

2. Similarly rename `EnemySpawner` to `NPCSpawner`.  Update its internal queue to hold `NPC*` instead of `Enemy` objects.  For example:
   ```cpp
   class NPCSpawner {
       std::deque<NPC*> spawnQueue;
   public:
       void addEnemy(NPC* e) { spawnQueue.push_back(e); }
       NPC* nextEnemy() {
           if (spawnQueue.empty()) throw std::runtime_error("empty");
           NPC* e = spawnQueue.front();
           spawnQueue.pop_front();
           return e;
       }
       size_t size() const { return spawnQueue.size(); }
   };
   ```
   Add debug output when pushing/popping to show the pointers being enqueued/dequeued; this reinforces the pointer semantics in a FIFO container.  If you keep the old value-based interface, you can still convert by creating a heap-allocated object when the caller passes by value.

   You might also modify `Game::processCombat(NPC& enemy)` to accept a reference so that the caller using `NPCSpawner` can simply write:
   ```cpp
   NPC* e = spawner.nextEnemy();
   processCombat(*e);
   delete e; // if ownership passes back
   ```
   The important thing is that the spawner no longer copies entire objects but moves pointers around.

3. Modify client code (in `Game.cpp`, tests) to allocate new NPCs dynamically:
   ```cpp
   npcGroup.add(new NPC("goblin", 8, 2, 0, 10, 3));
   
   // later delete them or implement a cleanup method
   for (auto p : npcGroup.getAll()) delete p;
   ```

4. Add pointer arithmetic demonstration in one of the container classes or in a new utility.  For example, after you've created an array of NPC pointers you can traverse it manually:
   ```cpp
   NPC* npcArray[3] = { new NPC("goblin",8,2,0,10,3), new Boss("ogre",30), new Merchant("trader",20) };
   std::cout << "Traversing npcArray using pointer arithmetic:\n";
   NPC** base = npcArray; // pointer to first element
   for (size_t i = 0; i < 3; ++i) {
       NPC* cur = *(base + i); // move by one element each time
       std::cout << " element " << i << " at " << static_cast<void*>(cur)
                 << " name=" << cur->getName() << '\n';
   }
   // clean up
   for (auto p : npcArray) delete p;
   ```
   > **Discussion point:** the addresses printed above are contiguous because
   > the array is a single block. Compare this output to the non‑contiguous
   > addresses from `NPCGroup::printAddresses()` to reinforce the difference
   > between arrays and vectors of separately‑allocated objects.


## 3. Create new NPC subclasses

1. Add `Boss.h`/`.cpp`:
   ```cpp
   class Boss : public NPC {
   public:
       Boss(const std::string& name, int hp) : NPC(name, hp, 5, 2, 100, 50) {}
       int calculateAttack() const override { return attack * 2; }
   };
   ```

2. Add `Merchant.h`/`.cpp` with custom behaviour—illustrate methods that only make sense for shopkeepers. To make the lab more interactive, add `tradeWithPlayer` directly in the `Merchant` class and have it call the simpler sell/purchase methods internally.  For example:
   ```cpp
   class Merchant : public NPC {
   private:
       int goldOnHand;
   public:
       Merchant(const std::string& name, int hp, int gold = 50)
           : NPC(name, hp, 0, 0, 0, 0), goldOnHand(gold) {}

       int calculateAttack() const override { return 0; }

       // merchant sells an item to someone (reduces own gold)
       void sellItem(int cost) {
           if (goldOnHand >= cost) {
               goldOnHand -= cost;
               std::cout << name << " netted " << cost << " gold from the sale.\n";
           } else {
               std::cout << name << " is out of gold to give change!\n";
           }
       }

       // merchant purchases an item (gains gold)
       void purchaseItem(int cost) {
           goldOnHand += cost;
           std::cout << name << " paid " << cost << " gold for an item.\n";
       }

       // handle a full transaction between merchant and player
       void tradeWithPlayer(Player& p, int cost, const std::string& item, bool playerBuying) {
           if (playerBuying) {
               // player wants to buy from merchant
               if (p.getGold() >= cost) {
                   p.loseGold(cost);
                   p.addItemToInventory(item);
                   purchaseItem(cost);            // merchant takes the money
                   std::cout << p.getName() << " bought " << item << " for " << cost << " gold.\n";
               } else {
                   std::cout << p.getName() << " can't afford " << item << "!\n";
               }
           } else {
               // player is selling to merchant
               if (p.hasItem(item)) {
                   p.removeItemFromInventory(item);
                   p.gainGold(cost);
                   sellItem(cost);                // merchant gives the money
                   std::cout << p.getName() << " sold " << item << " for " << cost << " gold.\n";
               } else {
                   std::cout << p.getName() << " doesn't have " << item << " to sell!\n";
               }
           }
       }

       int getGold() const { return goldOnHand; }
   };
   ```
   In the menu exercise (see step 4), display the player's inventory along with options to buy or sell. Call `merchant.tradeWithPlayer(player, price, chosenItem, true)` when buying, and pass `false` when selling.  This clearly differentiates internal merchant actions from the full transaction logic.

3. Use the subclasses in the tests and game logic to show polymorphism.
   - **Example in test/menu code:** create a `std::vector<NPC*>` containing a plain `NPC`, a `Boss`, and a `Merchant` and iterate over it, calling `calculateAttack()` or other virtual methods.  For instance:
     ```cpp
     std::vector<NPC*> roster;
     roster.push_back(new NPC("grunt", 10, 1, 0, 5, 2));
     roster.push_back(new Boss("ogre", 30));
     roster.push_back(new Merchant("trader", 20));

     for (NPC* n : roster) {
         std::cout << "Name: " << n->getName()
                   << " attack=" << n->calculateAttack()
                   << " health=" << n->getHealth() << '\n';
     }

     // cleanup
     for (NPC* n : roster) delete n;
     ```
   - **In game logic:** when spawning enemies or NPCs, store pointers to the base type and treat them uniformly.  For example, modify the combat loop to accept `NPC&` so a `Boss` can be passed in just like a regular `NPC`.
   - This shows that the runtime behaviour depends on the actual derived class, fulfilling the polymorphism requirement.


## 4. Extend tests with pointer/reference exercises

1. **Integrate the pointer tests into the game menu**
   - Instead of creating a separate test file, add a new menu option (e.g. "Run pointer exercises") in `Game.cpp` within the main game loop.
   - Implement a function such as `void runPointerLab()` in `Game.cpp` that contains the following logic:
     ```cpp
     #include "NPC.h"
     #include "Boss.h"
     #include "Merchant.h"
     #include <limits>

     void runPointerLab() {
         NPC* arr[3];
         arr[0] = new NPC("orc", 12, 2, 1, 20, 5);
         arr[1] = new Boss("dragon", 50);
         arr[2] = new Merchant("shopkeep", 20);

         std::cout << "-- Polymorphic attack values --\n";
         for (int i = 0; i < 3; ++i) {
             std::cout << arr[i]->getName() << " attack=" << arr[i]->calculateAttack() << '\n';
         }

         std::cout << "-- Pointer arithmetic addresses --\n";
         NPC** p = arr;
         for (int i = 0; i < 3; ++i) {
             std::cout << "address: " << p << " value: " << (*p)->getName() << '\n';
             ++p;
         }

         // reference demo
         auto buff = [](NPC& n) { n.takeDamage(-5); };
         buff(*arr[0]); // apply buff to first element
         std::cout << "Buffed " << arr[0]->getName() << " health=" << arr[0]->getHealth() << '\n';

         // numeric limits
         std::cout << "int range: " << std::numeric_limits<int>::min() << ".." << std::numeric_limits<int>::max() << '\n';
         std::cout << "long long big: " << (unsigned long long)0xFFFFFFFFFFFFFFFFULL << '\n';

         for (auto ptr : arr) delete ptr;
         std::cout << "Pointer lab complete.\n";
     }
     ```
   - Modify the menu handling code to call `runPointerLab()` when the user selects the new option.
   - This keeps tests visible within the interactive game and gives students a concrete way to trigger the exercises.


## 5. Document learning outcomes in Markdown

- At the end of `lesson_pointers.md` or in a new section of `lab06.md`, describe where each bullet point from the learning outcomes appears in the code produced above. Include annotated code snippets and sample output.

## 6. Build and verify

1. Run:
   ```bash
   cd /Users/heidiahders/Projects/Mendocino\ College/CSC222/game
   make   # or ./scripts/run_build.sh
   dungeongame/bin/combat_test
   dungeongame/bin/npc_test  # if built separately
   ```
2. Confirm tests pass and the new NPC container prints addresses correctly.
3. Use `gdb` to inspect pointer values and `valgrind` to ensure no leaks.

---

> This walkthrough may be distributed to students alongside the lab activity, giving them a concrete example of how to apply the concepts step by step.