#pragma once

#include <vector>
#include <iostream>
#include "NPC.h"

namespace dungeongame {

class NPCGroup {
private:
    std::vector<NPC*> npcs; // pointers rather than objects
public:
    void add(NPC* p) { 
        npcs.push_back(p);
        std::cout << "Added NPC at " << static_cast<void*>(p) << "\n";
    }
    
    NPC* operator[](size_t idx) { return npcs[idx]; }
    
    void printAddresses() const {
        std::cout << "NPC addresses (vector order):\n";
        for (auto p : npcs) {
            std::cout << "  " << static_cast<void*>(p) << "\n";
        }
    }
    
    size_t size() const { return npcs.size(); }
    
    std::vector<NPC*>& getAll() { return npcs; }
};

} // namespace dungeongame
