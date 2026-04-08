# Week 12 Lesson Plan: Hash Tables and Hashing

## Topic
Hash Tables, Hash Functions, Collision Handling, and a Game-Based Hashing Lab.

## Learning Objectives
- Explain what a hash function and hash table are.
- Identify collisions and describe how chaining resolves them.
- Calculate a simple hash value using a formula.
- Build and inspect a hash table with string keys.
- Apply hashing in a game context using the Dungeon Game.

## Materials
- `game/dungeongame` project files
- `game/lab-info/week12/week12.md`
- `game/lab-info/week12/hashing.md`
- `game/lab-info/week12/lesson-plan.md`
- `game/lab-info/week12/game-lab-activity.md`
- `game/dungeongame/data/ColorList.txt`

## Preparation
1. Open the `game/dungeongame` project in the editor.
2. Confirm the new `Game` menu option is available:
   - `30) Hashing Challenge (Week 12 lab)`.
3. Build the game using the existing build workflow (`cmake`, `make`, or `build.py`).
4. Review the hashing formula and color hash table instructions in `week12.md` and `hashing.md`.

## Agenda
1. Warm-up and definitions (10 minutes)
2. Instructor demo of the Hashing Challenge (10 minutes)
3. Student work on the game lab activity (25 minutes)
4. Class discussion and reflection (10 minutes)
5. Optional extension or homework (5 minutes)

## Lesson Flow

### 1. Warm-up and Definitions
- Review the key terms:
  - hash function
  - hash table
  - bucket/bin
  - collision
  - chaining
  - open addressing
- Use the links in `hashing.md` and the MIT lecture references to reinforce the terminology.

### 2. Instructor Demo
- Run the Dungeon Game and choose option `30`: Hashing Challenge.
- Show both parts of the challenge:
  1. Number hashing guess game
  2. Color hash table demo
- Explain how the game uses the hash formula:
  - `h(k) = floor(M * (F * k * A mod 1))`
- Highlight how collisions can happen in the guessing game.
- Explain how the color hash table stores colors in 15 bins with chaining.

### Hashing in games
- Hashing is useful in games because it makes lookups fast and predictable.
- In this Dungeon Game demo, hashing is used in two ways:
  1. A number-hashing game that demonstrates how different inputs can map to the same hash value.
  2. A color hash table that demonstrates how string keys can be placed into buckets and searched efficiently.
- Other game examples:
  - Inventory lookups by item name without scanning the whole list.
  - Resource or asset caching using hashed keys like texture or sound names.
  - Grouping game entities by type so only one bucket needs to be searched.
  - Procedural generation using hash-based seeds for consistent world data.
- This section helps students connect the abstract concept of hashing to real game systems.

### 3. Student Lab Activity
- Have students follow `game-lab-activity.md`.
- Students should run the game and complete both sections.
- Encourage students to answer the reflection questions in the activity document.
- Walk around and support students as they test hash values and search the hash table.

### 4. Discussion and Reflection
Ask students:
- What happened when two values produced the same hash?
- Why does the color hash table use `mod 15` for bucket selection?
- How does chaining make it possible to store multiple items in the same bucket?
- What is a load factor, and how does it affect performance?

### 5. Extension / Homework
- Have students implement a second probing strategy outside the game:
  - linear probing
  - quadratic probing
  - double hashing
- Or ask students to modify the color hash table to use a larger number of bins and compare average bin size.

## Assessment
- Check each student’s ability to explain collisions.
- Confirm students can describe how the hash table was built.
- Observe whether students can use the game to perform hash-based searches and insertions.

## Notes for the Instructor
- The game-based lab brings hashing into a familiar setting.
- The color hash table demo uses a linked-list-style bucket representation.
- This lesson is a good transition from sorting/searching to hashing and table-based data structures.
