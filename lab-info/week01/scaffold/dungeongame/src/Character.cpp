#include "Character.h"
#include <algorithm>
#include <iostream>

namespace dungeongame {

Character::Character(const std::string& name, int hp) : name(name), health(hp), maxHealth(hp), attack(1), defense(0), pos{0,0} {}

const Position& Character::getPosition() const { return pos; }
void Character::setPosition(int x, int y) { pos.x = x; pos.y = y; }
const std::string& Character::getName() const { return name; }
int Character::getHealth() const { return health; }
int Character::getMaxHealth() const { return maxHealth; }
int Character::getAttack() const { return attack; }
int Character::getDefense() const { return defense; }

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

void Character::heal(int amount) {
    if (amount <= 0) return;
    health = std::min(maxHealth, health + amount);
}

bool Character::isAlive() const { return health > 0; }

} // namespace dungeongame
