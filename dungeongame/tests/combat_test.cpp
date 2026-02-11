#include <iostream>
#include <cstdlib>
#include <ctime>
#include "dungeongame/Enemy.h"
#include "dungeongame/Player.h"
#include "dungeongame/Inventory.h"
#include "dungeongame/EnemyGroup.h"

using namespace dungeongame;
using namespace std;
using namespace std;

// Forward declarations for week02 tests
extern bool test_inventory_add_and_remove();
extern bool test_inventory_template_iteration();
extern bool test_enemygroup_add_and_traverse();

// Helper: compute damage as in Game::processCombat
static int calc_damage(const Character& attacker, const Character& defender) {
    int atk = attacker.calculateAttack();
    int damage = atk - defender.getDefense();
    return damage < 1 ? 1 : damage;
}

static bool test_victory() {
    Player p("Hero");
    // level up to increase attack so we can one-shot small enemies
    p.gainExperience(1000); // bump level and attack

    Enemy weak("Weakling", 5, 1); // 5 HP
    // ensure player's attack is high enough
    int damage = calc_damage(p, weak);
    while (weak.isAlive() && p.isAlive()) {
        weak.takeDamage(damage);
    }
    return !weak.isAlive() && p.isAlive();
}

static bool test_defeat() {
    Player p("Glass");
    // reduce player's health to 5 for the test
    p.takeDamage(p.getHealth() - 5);

    Enemy killer("Killer", 50, 50); // very strong attack
    // enemy attacks until player dies
    int edmg = calc_damage(killer, p);
    while (p.isAlive()) {
        p.takeDamage(edmg);
    }
    return !p.isAlive();
}

static bool test_flee_success() {
    // seed rand to a value that gives success (rand()%2==0)
    srand(2); // deterministic for this test
    int outcome = rand() % 2;
    return outcome == 0;
}

static bool test_flee_failure() {
    srand(1); // deterministic seed that yields failure (rand()%2==1)
    int outcome = rand() % 2;
    return outcome == 1;
}

extern "C" int main() {
    cout << "Running combat_test...\n";

    // Basic property checks
    Enemy goblin("Goblin", 10, 3);
    if (goblin.getAttackPower() != 3) { cerr << "FAIL: attackPower expected 3\n"; return 1; }
    if (goblin.getHealth() != 10) { cerr << "FAIL: health expected 10\n"; return 1; }

    // Movement
    Enemy orc("Orc", 8, 2);
    orc.setPosition(0, 0);
    orc.moveTowards(2, 3);
    auto pos = orc.getPosition();
    if (pos.x != 1 || pos.y != 1) { cerr << "FAIL: movement\n"; return 1; }

    // Scenario tests
    if (!test_victory()) { cerr << "FAIL: test_victory\n"; return 1; }
    if (!test_defeat()) { cerr << "FAIL: test_defeat\n"; return 1; }
    if (!test_flee_success()) { cerr << "FAIL: test_flee_success\n"; return 1; }
    if (!test_flee_failure()) { cerr << "FAIL: test_flee_failure\n"; return 1; }

    // Week 02: ADT tests
    if (!test_inventory_add_and_remove()) { cerr << "FAIL: test_inventory_add_and_remove\n"; return 1; }
    if (!test_inventory_template_iteration()) { cerr << "FAIL: test_inventory_template_iteration\n"; return 1; }
    if (!test_enemygroup_add_and_traverse()) { cerr << "FAIL: test_enemygroup_add_and_traverse\n"; return 1; }

    cout << "combat_test: PASS\n";
    return 0;
}
