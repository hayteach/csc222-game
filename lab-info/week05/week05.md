# Week 05 – Queue ADT Overview

This week’s material introduces the **Queue** abstract data type, a FIFO (First‑In‑First‑Out) structure similar to a line at the DMV or bank.  Before diving into coding, make sure to review all of the tabs on the Canvas page:

https://hayteach.github.io/csc222/week05/index.html

---

## What is a Queue?

A queue models a holding area where items are inserted at one end (the rear) and removed from the other (the front).  The first item added is the first item removed – hence the name FIFO.

> **Real‑world analogy:**  the first person in line is the first person to get service.


## Queue Interface (queueADT)

To allow interchangeable implementations, we define a common interface with the following methods (all pure virtual):

- `initializeQueue()`
- `bool isEmptyQueue() const`
- `bool isFullQueue() const` (array version only)
- `ItemType front() const`  – access front element
- `ItemType rear() const`   – access rear element
- `void addQueue(const ItemType& item)` – enqueue
- `void deleteQueue()` – dequeue

Because the interface is abstract, there is no `queueADT.cpp` file; concrete classes provide the implementations.


## Array‑based Implementation

The first concrete queue uses a circular array.  In addition to the interface methods, the class maintains:

- `int maxQueueSize` – capacity of the array
- `int count` – current number of elements
- `int queueFront` – index of front element
- `int queueRear` – index of rear element
- `ItemType *list` – pointer to dynamically‑allocated array

Constructors / destructor / assignment operator are provided:

- `arrayQueue(int size = 100)`
- `arrayQueue(const arrayQueue &other)`
- `~arrayQueue()`
- `operator=(const arrayQueue &other)`

See `arrayQueue.h`/`arrayQueue.cpp` for details.


## Linked‑List Implementation

An alternate implementation uses a linked list.  A `nodeType` struct holds an `ItemType` and a pointer to the next node.  The `linkedQueue` class keeps two pointers:

- `nodeType *front` – first node in the chain
- `nodeType *rear` – last node in the chain

All interface methods are implemented using pointer manipulation instead of array indices.  The same constructors, destructor, and assignment operator are provided.  See `linkedQueue.h` and `linkedQueue.cpp` for the source code.


## Testing

Two example test programs demonstrate usage of each implementation:

- `testProgQueueArray.cpp` – exercises the array‑based queue
- `testProgLinkedQueue.cpp` – exercises the linked‑list queue

Both programs perform a sequence of enqueues, dequeues, and queries to validate correctness.


---

**Reference:** Malik, D. (2018). *C++ Programming: Program Design Including Data Structures* (5th ed.), ch. 17.

Review the provided source files and experiment with your own queues when you start coding.

**Additional reading:**
- Saylor Academy, Unit 4 "Dynamic Memory Allocation" and Unit 6 "Linked Stacks, Queues, and Lists" – see https://learn.saylor.org/mod/page/view.php?id=96736 and https://learn.saylor.org/course/view.php?id=1307#section-25
