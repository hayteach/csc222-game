#include "dungeongame/Inventory.h"
#include <iostream>

using namespace dungeongame;

bool test_inventory_add_and_remove() {
    Inventory inv;
    inv.add(Item("Sword", 10));
    inv.add(Item("Potion", 1));
    if (inv.size() != 2) return false;
    if (inv[0].name != "Sword") return false;
    inv.removeAt(0);
    if (inv.size() != 1) return false;
    if (inv[0].name != "Potion") return false;
    return true;
}

bool test_inventory_template_iteration() {
    Inventory inv;
    inv.add(Item("A", 1));
    inv.add(Item("B", 2));
    inv.add(Item("C", 3));
    
    // Demonstrate template-based iteration using range-based for loop
    // This shows how templates enable modern C++ iteration patterns
    int count = 0;
    for (const Item& item : inv.getItems()) {
        if (count == 0 && item.name != "A") return false;
        if (count == 1 && item.name != "B") return false;
        if (count == 2 && item.name != "C") return false;
        count++;
    }
    return count == 3;
}

