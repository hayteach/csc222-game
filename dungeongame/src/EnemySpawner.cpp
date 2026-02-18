#include "dungeongame/EnemySpawner.h"
#include <iostream>
#include <stdexcept>

namespace dungeongame {

EnemySpawner::EnemySpawner()
{
    // default population (demo-friendly)
    spawnQueue.push_back(Enemy("Goblin", 8, 3, 0, 10, 5));
    spawnQueue.push_back(Enemy("Skeleton", 12, 4, 1, 15, 8));
    spawnQueue.push_back(Enemy("Orc", 18, 6, 2, 25, 12));
    spawnQueue.push_back(Enemy("Bandit", 14, 5, 1, 18, 9));
}

void EnemySpawner::addEnemy(const Enemy& e)
{
    spawnQueue.push_back(e);
}

bool EnemySpawner::hasEnemies() const
{
    return !spawnQueue.empty();
}

Enemy EnemySpawner::nextEnemy()
{
    if (spawnQueue.empty())
        throw std::underflow_error("EnemySpawner: no enemies available");
    Enemy e = spawnQueue.front();
    spawnQueue.pop_front();
    return e;
}

void EnemySpawner::skipEnemies(int n)
{
    if (n <= 0 || spawnQueue.empty()) return;
    if (n >= static_cast<int>(spawnQueue.size())) {
        spawnQueue.clear();
        return;
    }
    for (int i = 0; i < n; ++i) spawnQueue.pop_front();
}

void EnemySpawner::showQueue() const
{
    std::cout << "Spawn queue (size=" << spawnQueue.size() << "):\n";
    int idx = 0;
    for (const auto& e : spawnQueue) {
        std::cout << "  " << idx++ << ") " << e.getName() << " (hp=" << e.getHealth() << ")\n";
    }
}

} // namespace dungeongame
