#pragma once

#include <deque>
#include <string>
#include <vector>
#include "Enemy.h"

namespace dungeongame {

// Small spawn-queue manager used by the game and Week 04 lab demo.
// Internally uses std::deque but exposes the `skipEnemies(int)` API
// (semantics: discard first n enemies; n <= 0 no-op; n >= size -> empty).
class EnemySpawner {
public:
    EnemySpawner();

    void addEnemy(const Enemy& e);
    bool hasEnemies() const;
    Enemy nextEnemy(); // pop and return front enemy (throws if empty)

    // LAB / Week-04 feature: remove and discard the first n enemies
    void skipEnemies(int n);

    // Debug / UI helpers
    void showQueue() const;

private:
    std::deque<Enemy> spawnQueue;
};

} // namespace dungeongame
