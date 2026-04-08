# Hashing Overview

## Key Concepts

- **Hash function**: a function that maps data of arbitrary size to a fixed-size value.
- **Hash table**: a data structure that maps keys to values using a hash function to compute an index into an array of buckets or slots.
- **Collision**: when two input values map to the same bucket.
- **Perfect hash**: an ideal hash where each bucket contains at most one item.
- **Chaining**: a collision-handling design where each bucket holds a linked list of entries.
- **Open addressing**: a collision-handling design where all items are stored within the table itself and collisions are resolved by probing other slots.

## Useful Links

- Introduction to Hashing and Hash Tables: https://thispointer.com/what-is-hashing-and-hash-table/
- Hash function definition: https://en.wikipedia.org/wiki/Hash_function
- Hash table definition: https://en.wikipedia.org/wiki/Hash_table
- C++ Tutorial: Intro to Hash Tables: https://www.youtube.com/watch?v=dsuxijrK-EQ
- Hash table project in C++: https://www.youtube.com/watch?v=m6n_rozU8dA
- SHA-256 Algorithm Explained: https://www.simplilearn.com/tutorials/cyber-security-tutorial/sha-256-algorithm#what_is_the_sha256_algorithm
- SHA-256 Algorithm in Action: https://sha256algorithm.com/
- Hashing Algorithms and Security (Computerphile): https://www.youtube.com/watch?v=b4b8ktEV4Bg
- MIT Lecture 8: Hashing with Chaining: https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/resources/lecture-8-hashing-with-chaining/
- MIT Lecture 9: Table Doubling and Karp-Rabin: https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/resources/lecture-9-table-doubling-karp-rabin/

## Hash Table Basics

- A hash table uses a hash function to compute an index into an array of buckets.
- When a bucket contains multiple values, this is a collision.
- The simplest collision strategy is chaining: each bucket contains a linked list of entries.
- A hash table with chaining can hold an unlimited number of items in each bucket, but search cost depends on bucket size.

### Chaining Example

- Use an array of buckets.
- Each bucket stores values in a linked list.
- To insert, compute the hash and append to the bucket’s list.
- To search, compute the hash and scan only that bucket.

## Open Addressing

- Open addressing stores all items directly in the table.
- Table size must satisfy `m ≥ n`, where `m` is number of slots and `n` is number of items.
- The hash function produces a probe sequence `h(k, 0), h(k, 1), ..., h(k, m-1)`.
- A good probe sequence is a permutation of all table slots, so every slot can be visited.

### Probing Example

- `Insert(k, v)`:
  - For `i` from `0` to `m - 1`:
    - If `T[h(k, i)]` is empty, store `(k, v)` there and return.
  - If no empty slot exists, the table is full.

- `Search(k)`:
  - For `i` from `0` to `m - 1`:
    - If `T[h(k, i)]` is empty, return not found.
    - If the key matches, return the item.
  - If the table is exhausted, return not found.

### Deletion in Open Addressing

- You cannot simply clear a slot on delete.
- If a deleted slot becomes empty, later searches may stop too early.
- Use a special tombstone marker like `DeleteMe`.
- Insertion can reuse tombstones, but search must treat them as occupied.

## Probing Strategies

### Linear Probing

- `h(k, i) = (h'(k) + i) mod m`
- This probes the next slot in order until an open slot is found.
- Linear probing is like street parking: nearby slots are tried first.
- A downside is clustering: consecutive occupied slots form clusters that grow longer over time.
- When `0.01 < α < 0.99`, cluster sizes can grow to `Θ(log n)`.

## Lab Assignment

### Guessing Game Lab

Modify the provided game program to use the defined hashing function:

- Hash the user's guess and compare it to the target value.
- When the value is found, report:
  - Original value to be guessed
  - Hashed value to be guessed
  - Final guess
  - Hashed value of the final guess
  - How many tries it took to guess the value

**Guessing Game Code:** `guess.cpp`

#### Hashing Function

```
h(k) = floor(M * (F * k * A mod 1))
```

where:

- `M = 9.9`
- `F = 12345`
- `k = guess or value`
- `A = 0.323323`
- `h(k) = hashed value`

### Color Hash Table Program

Write a program that builds a hash table from `ColorList.txt`:

- Create a hash table with 15 bins.
- Use a hashing algorithm that adds the ASCII values of each letter in the color name and then takes `mod 15`.
- Store each color in the appropriate bin using a linked list.

After building the table, do the following:

- Report the average number of colors per non-empty bin.
- Report the maximum number of colors in any bin.

Then implement a loop that repeats until the user says stop:

- Ask the user to search for a color.
- If the color is found (case-insensitive), report which bin it is in.
  - Only search the appropriate bin for the color.
- If the color is not found, add it to the hash table.

Submit all code files plus `ColorList.txt` in a `.zip` archive for grading.
