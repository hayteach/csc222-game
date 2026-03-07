#pragma once

#include "LinkedBag.h"
#include "Spell.h"
#include <vector>

namespace dungeongame {

// Grimoire ADT using LinkedBag for storing spells (HW05)
class Grimoire {
private:
    LinkedBag<Spell> spells;

public:
    // Constructors
    Grimoire() {}
    
    // Accessors
    int getSpellCount() const { return spells.getCurrentSize(); }
    bool isEmpty() const { return spells.isEmpty(); }
    
    // Spellbook operations
    bool learnSpell(const Spell& spell) {
        return spells.add(spell);
    }
    
    bool knowsSpell(const Spell& spell) const {
        return spells.contains(spell);
    }
    
    bool forgetSpell(const Spell& spell) {
        return spells.remove(spell);
    }
    
    void clear() {
        spells.clear();
    }
    
    // Get all spells as vector for display
    std::vector<Spell> getAllSpells() const {
        return spells.toVector();
    }
};

} // namespace dungeongame
