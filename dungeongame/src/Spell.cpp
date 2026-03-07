#include "Spell.h"

namespace dungeongame {

Spell::Spell() : name(""), manaCost(0), damage(0), effect("") {}

Spell::Spell(const std::string& spellName, int mana, int dmg, const std::string& eff)
    : name(spellName), manaCost(mana), damage(dmg), effect(eff) {}

bool Spell::operator==(const Spell& other) const {
    return name.equals(other.name);
}

} // namespace dungeongame
