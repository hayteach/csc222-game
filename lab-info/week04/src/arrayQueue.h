#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

#include <stdexcept>
#include "queueADT.h"

/**
 * arrayQueue.h
 * Simple circular-array implementation of queueADT (template).
 * Implements the additional `remove(int n)` method required for Week 04 lab.
 *
 * Implementation notes:
 * - Uses circular indexing with `queueFront` pointing at the front element and
 *   `queueRear` pointing at the rear element.
 * - `queueRear` is initialized to maxQueueSize - 1 so the first addQueue() sets
 *   it to 0.
 */

template <class ItemType>
class arrayQueue : public queueADT<ItemType>
{
public:
    explicit arrayQueue(int queueSize = 100);
    arrayQueue(const arrayQueue<ItemType>& otherQueue);
    ~arrayQueue();

    void initializeQueue() override;
    bool isEmptyQueue() const override;
    bool isFullQueue() const override;
    void addQueue(const ItemType& queueElement) override;
    void deleteQueue() override;
    ItemType front() const override;
    ItemType rear() const override;

    // New lab method
    void remove(int n) override;

    // assignment
    arrayQueue<ItemType>& operator=(const arrayQueue<ItemType>& otherQueue);

    // helper for tests / convenience (not part of queueADT)
    int size() const { return count; }

private:
    void copyQueue(const arrayQueue<ItemType>& otherQueue);

    ItemType* list;
    int maxQueueSize;
    int queueFront;
    int queueRear;
    int count;
};

// ---------------- implementation ----------------

template <class ItemType>
arrayQueue<ItemType>::arrayQueue(int queueSize)
{
    if (queueSize <= 0)
        queueSize = 100;

    maxQueueSize = queueSize;
    list = new ItemType[maxQueueSize];
    initializeQueue();
}

template <class ItemType>
arrayQueue<ItemType>::arrayQueue(const arrayQueue<ItemType>& otherQueue)
{
    list = nullptr;
    copyQueue(otherQueue);
}

template <class ItemType>
arrayQueue<ItemType>::~arrayQueue()
{
    delete [] list;
}

template <class ItemType>
void arrayQueue<ItemType>::initializeQueue()
{
    queueFront = 0;
    queueRear = maxQueueSize - 1;
    count = 0;
}

template <class ItemType>
bool arrayQueue<ItemType>::isEmptyQueue() const
{
    return (count == 0);
}

template <class ItemType>
bool arrayQueue<ItemType>::isFullQueue() const
{
    return (count == maxQueueSize);
}

template <class ItemType>
void arrayQueue<ItemType>::addQueue(const ItemType& queueElement)
{
    if (isFullQueue())
        throw std::overflow_error("arrayQueue: add to full queue");

    queueRear = (queueRear + 1) % maxQueueSize;
    list[queueRear] = queueElement;
    ++count;
}

template <class ItemType>
void arrayQueue<ItemType>::deleteQueue()
{
    if (isEmptyQueue())
        throw std::underflow_error("arrayQueue: delete from empty queue");

    queueFront = (queueFront + 1) % maxQueueSize;
    --count;
}

template <class ItemType>
ItemType arrayQueue<ItemType>::front() const
{
    if (isEmptyQueue())
        throw std::underflow_error("arrayQueue: front on empty queue");

    return list[queueFront];
}

template <class ItemType>
ItemType arrayQueue<ItemType>::rear() const
{
    if (isEmptyQueue())
        throw std::underflow_error("arrayQueue: rear on empty queue");

    return list[queueRear];
}

template <class ItemType>
void arrayQueue<ItemType>::remove(int n)
{
    // No-op for non-positive n
    if (n <= 0 || isEmptyQueue())
        return;

    if (n >= count) {
        // remove all
        initializeQueue();
        return;
    }

    // advance front index by n positions (modular) and reduce count
    queueFront = (queueFront + n) % maxQueueSize;
    count -= n;
}

template <class ItemType>
arrayQueue<ItemType>& arrayQueue<ItemType>::operator=(const arrayQueue<ItemType>& otherQueue)
{
    if (this != &otherQueue) {
        delete [] list;
        copyQueue(otherQueue);
    }
    return *this;
}

template <class ItemType>
void arrayQueue<ItemType>::copyQueue(const arrayQueue<ItemType>& otherQueue)
{
    maxQueueSize = otherQueue.maxQueueSize;
    list = new ItemType[maxQueueSize];

    count = otherQueue.count;
    queueFront = otherQueue.queueFront;
    queueRear = otherQueue.queueRear;

    // copy elements in underlying array order (preserve indices)
    for (int i = 0; i < maxQueueSize; ++i)
        list[i] = otherQueue.list[i];
}

#endif // ARRAYQUEUE_H
