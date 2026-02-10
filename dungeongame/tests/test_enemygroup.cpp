#include "dungeongame/EnemyGroup.h"
#include "dungeongame/Enemy.h"
#include <iostream>

using namespace dungeongame;

bool test_enemygroup_add_and_traverse() {
    EnemyGroup g;
    g.add(Enemy("Goblin", 5, 1));
    g.add(Enemy("Orc", 12, 3));
    if (g.size() != 2) return false;
    // rawData() returns a pointer to the `vector`'s contiguous storage.
    // Accessing elements via a raw pointer and using pointer arithmetic
    // demonstrates how `vector` provides contiguous memory suitable for
    // pointer-based traversal. Discuss that `vector::data()` is safe while
    // the vector is unchanged (no reallocation or destruction occurs).
    Enemy* p = g.rawData();
    if (p == nullptr) return false;
    if (p->getName() != "Goblin") return false;
    if ((p+1)->getAttackPower() != 3) return false;
    return true;
}

