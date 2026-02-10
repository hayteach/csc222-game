#pragma once

#include <vector>
#include <string>
#include "dungeongame/Enemy.h"

// Instructor note (Week 02 - ADTs & STL):
// - `EnemyGroup` is a small ADT wrapper that uses an STL container (vector)
//   as its implementation. This demonstrates how ADTs can be implemented using
//   standard library containers that provide tested, efficient behavior.
// - By exposing `rawData()` we intentionally give students a safe, controlled
//   place to practice pointer traversal while discussing the responsibilities
//   (ownership and lifetime) of the container.
// - Compare this STL-backed implementation with a custom implementation to
//   highlight trade-offs in complexity, performance, and safety.

namespace dungeongame {

class EnemyGroup {
private:
    std::vector<Enemy> enemies;
public:
    void add(const Enemy& e) { enemies.push_back(e); }
    size_t size() const { return enemies.size(); }
    Enemy* rawData() { return enemies.empty() ? nullptr : enemies.data(); }
    const Enemy* rawData() const { return enemies.empty() ? nullptr : enemies.data(); }
    Enemy& operator[](size_t idx) { return enemies[idx]; }
};

} // namespace dungeongame
