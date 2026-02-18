#include "dungeongame/ActionHistory.h"
#include "dungeongame/Player.h"
#include <cassert>
#include <iostream>

using namespace dungeongame;

int main() {
    Player p("Tester");
    ActionHistory h;

    // --- Move undo (existing behavior) ---
    Position start = p.getPosition();
    p.setPosition(2,2);
    h.pushMove(start);

    p.setPosition(3,3);
    h.pushMove({2,2});

    bool undone = h.undoLast(p);
    assert(undone);
    Position pos = p.getPosition();
    assert(pos.x == 2 && pos.y == 2);

    int undoneCount = h.undoLast(5, p);
    assert(undoneCount == 1);
    pos = p.getPosition();
    assert(pos.x == start.x && pos.y == start.y);

    // --- Pick undo ---
    size_t before = p.inventorySize();
    Item gem("Gem", 50);
    p.addItem(gem);
    h.pushPick(gem, p.inventorySize() - 1);
    assert(p.inventorySize() == before + 1);
    bool undonePick = h.undoLast(p);
    assert(undonePick && p.inventorySize() == before);

    // --- Drop undo ---
    p.addItem(Item("Sword", 10));
    p.addItem(Item("Shield", 20));
    size_t sz = p.inventorySize();
    Item removed = p.removeItemAt(0);
    h.pushDrop(removed, 0);
    assert(p.inventorySize() == sz - 1);
    bool undoneDrop = h.undoLast(p);
    assert(undoneDrop && p.inventorySize() == sz && p[0].name == removed.name);

    // --- Use potion undo ---
    p.addItem(Item("Potion", 5));
    int prevH = p.getHealth();
    p.takeDamage(3);
    Item used;
    int healAmt = 0;
    bool usedOk = p.usePotionAndGet(used, healAmt);
    assert(usedOk && p.getHealth() > prevH - 3);
    h.pushUsePotion(used, prevH - 3);
    bool undonePotion = h.undoLast(p);
    assert(undonePotion && p.getHealth() == prevH - 3);
    // potion should be back in inventory
    bool found = false;
    for (size_t i = 0; i < p.inventorySize(); ++i) if (p[i].name == "Potion") { found = true; break; }
    assert(found);

    std::cout << "test_action_undo: PASS\n";
    return 0;
}
