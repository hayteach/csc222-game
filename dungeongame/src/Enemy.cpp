#include "Enemy.h"

namespace dungeongame {

Enemy::Enemy(const std::string& name, int hp, int attack)
    : Character(name, hp), attackPower(attack) {}

int Enemy::getAttackPower() const {
    return attackPower;
}

void Enemy::takeDamage(int d) {
    health -= d;
    if (health < 0) health = 0;
}

void Enemy::moveTowards(int playerX, int playerY) {
    // Very small example implementation: move one step towards player
    if (pos.x < playerX) pos.x += 1;
    else if (pos.x > playerX) pos.x -= 1;

    if (pos.y < playerY) pos.y += 1;
    else if (pos.y > playerY) pos.y -= 1;
}

} // namespace dungeongame
