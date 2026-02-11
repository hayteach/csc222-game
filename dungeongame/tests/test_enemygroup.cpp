#include "dungeongame/EnemyGroup.h"
#include "dungeongame/Enemy.h"
#include <iostream>

using namespace dungeongame;

bool test_enemygroup_add_and_traverse() {
    EnemyGroup g;
    g.add(Enemy("Goblin", 5, 1));
    g.add(Enemy("Orc", 12, 3));
    if (g.size() != 2) return false;
    
    // Demonstrate template-based iteration using range-based for loop
    // This shows how templates enable modern C++ iteration patterns with linked structures
    int count = 0;
    for (const Enemy& enemy : g.getEnemies()) {
        if (count == 0 && enemy.getName() != "Goblin") return false;
        if (count == 1 && enemy.getAttackPower() != 3) return false;
        count++;
    }
    return count == 2;
}

