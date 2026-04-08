#include "Menu.h"
#include <iostream>

namespace dungeongame {

void displayMenu(const MenuScreen& menu) {
    std::cout << "\n=== " << menu.title << " ===\n";
    for (const auto& option : menu.options) {
        std::cout << option.id << ") " << option.label << "\n";
    }
    std::cout << "Choose an action: ";
}

int promptMenuChoice() {
    int choice = -1;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return -1;
    }
    return choice;
}

bool dispatchMenuChoice(const MenuScreen& menu, int choice) {
    for (const auto& option : menu.options) {
        if (option.id == choice) {
            option.action();
            return true;
        }
    }
    std::cout << "Invalid choice." << std::endl;
    return false;
}

} // namespace dungeongame
