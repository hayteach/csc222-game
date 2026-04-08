#pragma once

#include <functional>
#include <string>
#include <vector>

namespace dungeongame {

struct MenuOption {
    int id;
    std::string label;
    std::function<void()> action;
};

struct MenuScreen {
    std::string title;
    std::vector<MenuOption> options;
};

void displayMenu(const MenuScreen& menu);
int promptMenuChoice();
bool dispatchMenuChoice(const MenuScreen& menu, int choice);

} // namespace dungeongame
