#pragma once

#include <deque>
#include <string>
#include <iostream>
#include "NPC.h"

namespace dungeongame {

// Spawn-queue manager using pointers
class NPCSpawner {
public:
    NPCSpawner(); // default constructor (implemented in .cpp)

    void addEnemy(NPC* e) {
        spawnQueue.push_back(e);
        std::cout << "Queued NPC at " << static_cast<void*>(e) << "\n";
    }

    bool hasEnemies() const { return !spawnQueue.empty(); }
    NPC* nextEnemy() { // pop and return front enemy (throws if empty)
        if (spawnQueue.empty()) throw std::runtime_error("empty");
        NPC* e = spawnQueue.front();
        spawnQueue.pop_front();
        std::cout << "Dequeued NPC at " << static_cast<void*>(e) << "\n";
        return e;
    }

    // LAB / Week-04 feature: remove and discard the first n enemies
    void skipEnemies(int n) {
        while (n-- > 0 && !spawnQueue.empty()) {
            NPC* e = spawnQueue.front();
            spawnQueue.pop_front();
            delete e;
        }
    }

    // Debug / UI helpers
    void showQueue() const {
        std::cout << "NPC spawn queue addresses:\n";
        for (auto e : spawnQueue) std::cout << "  " << static_cast<void*>(e) << "\n";
    }

    size_t size() const { return spawnQueue.size(); }

private:
    std::deque<NPC*> spawnQueue;
};

} // namespace dungeongame
