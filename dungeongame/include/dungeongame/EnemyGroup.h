#pragma once

#include <vector>
#include <string>
#include "Enemy.h"
#include "LinkedList.h"

// Instructor note (Week 03 - Templates & Linked Lists):
// - EnemyGroup now uses our custom LinkedList template instead of std::vector
// - This demonstrates how to replace standard library containers with custom templates
// - Students learn about the trade-offs between different container implementations

namespace dungeongame {

class EnemyGroup {
private:
    // Using LinkedList instead of std::vector to demonstrate templates
    LinkedList<Enemy> enemies;
public:
    void add(const Enemy& e) { enemies.append(e); }
    size_t size() const { return enemies.size(); }
    
    // Provide access to the linked list for iteration
    const LinkedList<Enemy>& getEnemies() const { return enemies; }
    LinkedList<Enemy>& getEnemies() { return enemies; }
    
    // For backward compatibility, provide indexing
    Enemy& operator[](size_t idx) { return enemies.get(idx); }
    const Enemy& operator[](size_t idx) const { return enemies.get(idx); }
};

} // namespace dungeongame
