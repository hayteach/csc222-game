#include <iostream>
#include "dungeongame/Enemy.h"

using namespace dungeongame;

int main() {
    std::cout << "Running combat_test...\n";

    Enemy goblin("Goblin", 10, 3);
    if (goblin.getAttackPower() != 3) {
        std::cerr << "FAIL: attackPower expected 3 got " << goblin.getAttackPower() << "\n";
        return 1;
    }

    if (goblin.getHealth() != 10) {
        std::cerr << "FAIL: health expected 10 got " << goblin.getHealth() << "\n";
        return 1;
    }

    goblin.takeDamage(4);
    if (goblin.getHealth() != 6) {
        std::cerr << "FAIL: health after 4 dmg expected 6 got " << goblin.getHealth() << "\n";
        return 1;
    }

    goblin.takeDamage(10);
    if (goblin.getHealth() != 0) {
        std::cerr << "FAIL: health should not drop below 0 got " << goblin.getHealth() << "\n";
        return 1;
    }

    // Test movement
    Enemy orc("Orc", 8, 2);
    orc.setPosition(0, 0);
    orc.moveTowards(2, 3); // should move to (1,1)
    auto pos = orc.getPosition();
    if (pos.x != 1 || pos.y != 1) {
        std::cerr << "FAIL: orc expected pos (1,1) got (" << pos.x << "," << pos.y << ")\n";
        return 1;
    }

    orc.moveTowards(2, 3); // should move to (2,2)
    pos = orc.getPosition();
    if (pos.x != 2 || pos.y != 2) {
        std::cerr << "FAIL: orc expected pos (2,2) got (" << pos.x << "," << pos.y << ")\n";
        return 1;
    }

    std::cout << "combat_test: PASS\n";
    return 0;
}
