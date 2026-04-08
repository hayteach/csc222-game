# Week 12

## Hash Tables

For an introduction to Hashing and Hash Tables:
https://thispointer.com/what-is-hashing-and-hash-table/

A **hash function** is "*any function that can be used to map data of arbitrary size onto data of a fixed size.*" (https://en.wikipedia.org/wiki/Hash_function)

Our main interest in hashing is the creation and use of hash tables.

"*A **hash table** (**hash map**) is a data structure that implements an associative array abstract data type, a structure that can map keys to values. A hash table uses a hash function to compute an index into an array of buckets or slots, from which the desired value can be found.*" (https://en.wikipedia.org/wiki/Hash_table)

In the example provided in the introduction link above, all numbers were split and placed into one of 10 bins. Anytime a bin has more than 1 element in it, that is called a collision. To search and see if a number is already stored in your hash table, you would first hash the number you are looking for, then go to the bin where that number would be stored and search through what is stored in that bin. For a set of random numbers, this means that, on average, you would search through 1/2 of 1/10 of the total number of things stored in that hash table.

In an ideal world, every bin would only have 1 item in it - this is called a "Perfect Hash". In reality, this isn't possible so you will always have collisions to deal with. The basic structure of a hash table is an Array of Linked-Lists where the Array Indices are the "Bins" and the values stored in each Bin are stored in a Linked-List (essentially this is the same as a Graph except coded to store and retrieve data).

This video provides a nice overview/introduction into how hash tables work and how you can implement them.

C++ Tutorial: Intro to Hash Tables
https://www.youtube.com/watch?v=dsuxijrK-EQ


## What's a Hash Table

Simple overview of Hash Table and Hashing:
https://thispointer.com/what-is-hashing-and-hash-table/

Tutorial on creating a hash table in C++ (needs to be reworked because some issues with structure):
https://www.youtube.com/watch?v=m6n_rozU8dA

Most secure Cryptographic Hash as of 4/7/2022 is: SHA-256

The SHA-256 Algorithm Explained
https://www.simplilearn.com/tutorials/cyber-security-tutorial/sha-256-algorithm#what_is_the_sha256_algorithm

SHA-256 Algorithm in Action
https://sha256algorithm.com/

Good video on How/Why we use Hashing Algorithms:
https://www.youtube.com/watch?v=b4b8ktEV4Bg


## Lab Assignment

Modify the included game program using the defined hashing function to:

- Hash the user's guess and compare it to the value to be found.
- When found, report out the following:
  - Original value to be guessed
  - Hashed value to be guessed
  - Final Guess
  - Hashed value of final guess
  - How many tries it took to guess the value

Guessing Game Code: guess.cpp

### Hashing Function

h(k) = floor (M (F k A mod 1))

where:

- M = 9.9
- F = 12345
- k = guess or value
- A = 0.323323
- h(k) = hashed value


## Color Hash Table Program

Write a program that creates a Hash Table to store the data in the provided file which is a list of colors, ColorList.txt, as defined below:

- Create a Hash table with 15 bins
- Use a basic hashing algorithm that adds the ASCII values of each letter in the color name and then mods by your chosen number of bins.
- Place the color in the appropriate bin where the contents of each bin is a linked list (so you can hold any number of items in any one bin)

Once you've created the Hash table of colors, have your program do the following:

- Report out the:
  - Average number of colors stored in each bin ignoring any bins that have 0 entries
  - Maximum number of colors in any one bin
- Write a loop that continues until the user says stop that:
  - Asks the user to search for a color
    - If found, ignoring the case, report which bin it was found in (Make sure your code ONLY searches the appropriate bin)
    - If not found, add the color to the Hash Table

Submit all of your code files for review including the provided ColorList.txt file in a .zip archive and then upload that .zip archive for grading.
