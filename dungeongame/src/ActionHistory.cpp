#include "dungeongame/ActionHistory.h"
#include <iostream>

namespace dungeongame {

void ActionHistory::pushMove(const Position& prev)
{
    if (actions.size() >= DEFAULT_MAX) {
        // drop oldest to keep a bounded history
        actions.erase(actions.begin());
    }
    actions.emplace_back(Action::Type::Move, prev);
}

void ActionHistory::pushPick(const Item& item, size_t index)
{
    if (actions.size() >= DEFAULT_MAX) actions.erase(actions.begin());
    actions.emplace_back(Action::Type::Pick, item, index);
}

void ActionHistory::pushDrop(const Item& item, size_t index)
{
    if (actions.size() >= DEFAULT_MAX) actions.erase(actions.begin());
    actions.emplace_back(Action::Type::Drop, item, index);
}

void ActionHistory::pushUsePotion(const Item& item, int prevHealth)
{
    if (actions.size() >= DEFAULT_MAX) actions.erase(actions.begin());
    actions.emplace_back(Action::Type::UsePotion, item, prevHealth);
}

bool ActionHistory::undoLast(Player& player)
{
    if (actions.empty()) return false;
    Action last = actions.back();
    actions.pop_back();

    switch (last.type) {
        case Action::Type::Move:
            player.setPosition(last.prevPos.x, last.prevPos.y);
            return true;

        case Action::Type::Pick: {
            // undo picking an item => remove that item from inventory
            for (size_t i = 0; i < player.inventorySize(); ++i) {
                const Item& it = player[i];
                if (it.name == last.item.name && it.value == last.item.value) {
                    player.removeItemAt(i);
                    return true;
                }
            }
            return false;
        }

        case Action::Type::Drop: {
            // undo dropping an item => insert back at original index (or append if out of range)
            size_t idx = last.index;
            if (idx > player.inventorySize()) idx = player.inventorySize();
            player.addItemAt(idx, last.item);
            return true;
        }

        case Action::Type::UsePotion: {
            // restore player's health and re-add the potion to inventory
            player.setHealth(last.prevHealth);
            player.addItem(last.item);
            return true;
        }

        default:
            return false;
    }
}

int ActionHistory::undoLast(int k, Player& player)
{
    int undone = 0;
    for (int i = 0; i < k; ++i) {
        if (!undoLast(player)) break;
        ++undone;
    }
    return undone;
}

void ActionHistory::showHistory() const
{
    std::cout << "Action history (most recent last, size=" << actions.size() << "):\n";
    int idx = 0;
    for (const auto& a : actions) {
        std::cout << "  " << idx++ << ") ";
        switch (a.type) {
            case Action::Type::Move:
                std::cout << "Move -> prevPos=(" << a.prevPos.x << "," << a.prevPos.y << ")\n";
                break;
            case Action::Type::Pick:
                std::cout << "Pick -> item=" << a.item.name << " idx=" << a.index << "\n";
                break;
            case Action::Type::Drop:
                std::cout << "Drop -> item=" << a.item.name << " idx=" << a.index << "\n";
                break;
            case Action::Type::UsePotion:
                std::cout << "UsePotion -> item=" << a.item.name << " prevHealth=" << a.prevHealth << "\n";
                break;
            default:
                std::cout << "Unknown\n";
                break;
        }
    }
}

} // namespace dungeongame
