#pragma once
#include "Character.h"
#include <string>

namespace dungeongame {

class Player : public Character {
private:
    int level{1};
    int gold{0};
    int experience{0};
public:
    Player(const std::string& name = "Player");
    void move(int dx, int dy);
    void displayStats() const;
    void gainExperience(int exp);
    void levelUp();
    void addGold(int amount);
};

} // namespace dungeongame
