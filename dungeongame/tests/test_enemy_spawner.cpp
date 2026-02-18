#include "dungeongame/EnemySpawner.h"
#include <cassert>
#include <iostream>

using namespace dungeongame;

int main() {
    EnemySpawner s;
    s.addEnemy(Enemy("TestA", 1, 1, 0, 1, 1));
    s.addEnemy(Enemy("TestB", 1, 1, 0, 1, 1));
    s.addEnemy(Enemy("TestC", 1, 1, 0, 1, 1));

    // initial size >= 3 (constructor adds default enemies)
    s.showQueue();
    s.skipEnemies(2);
    // after skipping 2, queue still may have elements
    std::cout << "After skip(2):\n";
    s.showQueue();

    // skip large number -> empty
    s.skipEnemies(1000);
    assert(!s.hasEnemies() && "Spawner should be empty after large skip");
    std::cout << "test_enemy_spawner: PASS\n";
    return 0;
}
