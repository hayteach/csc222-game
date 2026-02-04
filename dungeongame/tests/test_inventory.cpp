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

bool test_inventory_pointer_traversal() {
    Inventory inv;
    inv.add(Item("A", 1));
    inv.add(Item("B", 2));
    inv.add(Item("C", 3));
    // rawData() exposes the Inventory's contiguous storage (an array owned by
    // the Inventory). The pointer `p` points to the first element and pointer
    // arithmetic like `(p + 1)` advances to the next `Item` in memory. This
    // is a hands-on demonstration of contiguous ADTs and pointer traversal.
    // IMPORTANT: students should be aware of bounds and lifetime (don't use
    // the pointer after the Inventory is modified or destroyed).
    const Item* p = inv.rawData();
    if (p == nullptr) return false;
    if ((p+1)->name != "B") return false;
    if ((p+2)->value != 3) return false;
    return true;
}

