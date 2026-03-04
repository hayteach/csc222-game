#include "NPCSpawner.h"
#include <iostream>
#include <stdexcept>

namespace dungeongame {

NPCSpawner::NPCSpawner()
{
    // optional default population
    addEnemy(new NPC("Goblin", 8, 3, 0, 10, 5));
    addEnemy(new NPC("Skeleton", 12, 4, 1, 15, 8));
    addEnemy(new NPC("Orc", 18, 6, 2, 25, 12));
    addEnemy(new NPC("Bandit", 14, 5, 1, 18, 9));
}

// other methods implemented inline in header; if you prefer you can leave
// implementations here, but header already contains everything.

} // namespace dungeongame
