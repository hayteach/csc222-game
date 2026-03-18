#pragma once

#include <vector>
#include <iostream>
#include <algorithm>  // std::swap
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
       }
    void printAddresses() const {
        std::cout << "NPC addresses (vector order):\n";
        for (auto p : npcs) {
            std::cout << "  " << static_cast<void*>(p) << "\n";
     
    }
    
    size_t size() const { return npcs.size(); }
    
    std::vector<NPC*>& getAll() { return npcs; }

    // ---------------------------------------------------------------
    // Week 08 — Sorting (Algorithm Efficiency)
    // ---------------------------------------------------------------

    // Sort NPCs in ascending order by current health — O(n²) selection sort
    // Selection sort finds the minimum of the unsorted portion each pass
    // and swaps it into its final position (fewer swaps than bubble sort).
    void sortByHealth() {
        size_t n = npcs.size();
        for (size_t i = 0; i < n; i++) {
            size_t minIdx = i;
            for (size_t j = i + 1; j < n; j++) {
                if (npcs[j]->getHealth() < npcs[minIdx]->getHealth())
                    minIdx = j;
            }
            if (minIdx != i)
                std::swap(npcs[i], npcs[minIdx]);
        }
    }

    // Sort NPCs in descending order by attack power — O(n²) selection sort
    // After this call, npcs[0] is the most dangerous enemy.
    void sortByAttack() {
        size_t n = npcs.size();
        for (size_t i = 0; i < n; i++) {
            size_t maxIdx = i;
            for (size_t j = i + 1; j < n; j++) {
                if (npcs[j]->getAttackPower() > npcs[maxIdx]->getAttackPower())
                    maxIdx = j;
            }
            if (maxIdx != i)
                std::swap(npcs[i], npcs[maxIdx]);
        }
    }
};

} // namespace dungeongame
