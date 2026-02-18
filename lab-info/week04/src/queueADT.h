#ifndef QUEUEADT_H
#define QUEUEADT_H

/**
 * queueADT.h
 * Abstract interface for a Queue ADT (FIFO).
 *
 * This header is intentionally minimal — concrete implementations (arrayQueue,
 * linkedQueue) must implement all pure-virtual methods below.  The new
 * `remove(int n)` method (added for Week 04 lab) removes and discards the
 * first n items from the queue (front-most items).
 *
 * Usage: implementers should ensure remove(n) updates internal counters and
 * indices correctly and does not leak memory.
 */

template <class ItemType>
class queueADT
{
public:
    // Initialize the queue to an empty state
    virtual void initializeQueue() = 0;

    // Return true if the queue is empty
    virtual bool isEmptyQueue() const = 0;

    // Return true if the queue is full (only meaningful for array-based queues)
    virtual bool isFullQueue() const = 0;

    // Add an item to the rear of the queue
    virtual void addQueue(const ItemType& queueElement) = 0;

    // Remove the item at the front of the queue
    virtual void deleteQueue() = 0;

    // Return (a copy of) the front element
    virtual ItemType front() const = 0;

    // Return (a copy of) the rear element
    virtual ItemType rear() const = 0;

    // LAB: remove and discard the first n entries from the queue.
    // - If n <= 0: no-op
    // - If 0 < n < size(): remove exactly n items (FIFO order)
    // - If n >= size(): the queue becomes empty
    virtual void remove(int n) = 0;

    // Virtual destructor for interface
    virtual ~queueADT() {}
};

#endif // QUEUEADT_H
