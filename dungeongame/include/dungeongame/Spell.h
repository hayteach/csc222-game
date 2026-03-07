#pragma once

#include "LinkedString.h"
#include <string>

namespace dungeongame {

// Spell ADT using LinkedString for name
class Spell {
private:
    LinkedString name;      // spell name using LinkedString ADT (Lab07)
    int manaCost;
    int damage;
    std::string effect;     // description of spell effect

public:
    // Constructors
    Spell();
    Spell(const std::string& spellName, int mana, int dmg, const std::string& eff);
    
    // Accessors
    LinkedString getName() const { return name; }
    std::string getNameAsString() const { return name.toStdString(); }
    int getManaCost() const { return manaCost; }
    int getDamage() const { return damage; }
    std::string getEffect() const { return effect; }
    
    // comparison for LinkedBag
    bool operator==(const Spell& other) const;
};

} // namespace dungeongame
