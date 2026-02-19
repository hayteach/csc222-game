#pragma once

#include <vector>
#include <string>
#include "Character.h"
#include "Inventory.h"

namespace dungeongame {

class Player; // forward declaration (header-only dependency)

// Lightweight Action + history for undoing simple player actions.
// Supports Move, Pick, Drop, and UsePotion actions.
class ActionHistory {
public:
    struct Action {
        enum class Type { Move, Pick, Drop, UsePotion };
        Type type;
        Position prevPos;    // Move: previous player position
        Item item;           // Pick/Drop/UsePotion: the item involved
        size_t index{0};     // Pick/Drop: inventory index
        int prevHealth{0};   // UsePotion: player's health before using

        Action(Type t, const Position& p) : type(t), prevPos(p) {}
        Action(Type t, const Item& it, size_t idx) : type(t), item(it), index(idx) {}
        Action(Type t, const Item& it, int prevH) : type(t), item(it), prevHealth(prevH) {}
    };

    ActionHistory() = default;

    // existing: push a Move action
    void pushMove(const Position& prev);

    // new pushes for lab: pick/drop/use-potion
    void pushPick(const Item& item, size_t index);
    void pushDrop(const Item& item, size_t index);
    void pushUsePotion(const Item& item, int prevHealth);

    // Undo the last action; returns true if an action was undone.
    bool undoLast(Player& player);

    // Undo up to k actions; returns number of actions actually undone.
    int undoLast(int k, Player& player);

    bool isEmpty() const { return actions.empty(); }
    void clear() { actions.clear(); }

    // Debug helper
    void showHistory() const;

private:
    std::vector<Action> actions;
    static constexpr size_t DEFAULT_MAX = 100;
};

} // namespace dungeongame
