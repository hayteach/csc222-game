#pragma once
#include <string>

namespace dungeongame {

struct Position { int x{0}; int y{0}; };

class Character {
protected:
    std::string name;
    int health;
    int maxHealth{10};
    int attack{1};
    int defense{0};
    Position pos;
public:
    Character(const std::string& name = "Nameless", int hp = 10);
    const Position& getPosition() const;
    void setPosition(int x, int y);
    const std::string& getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getAttack() const;
    int getDefense() const;
    void takeDamage(int damage);
    void heal(int amount);
    bool isAlive() const;
};

} // namespace dungeongame
