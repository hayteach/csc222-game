#include "dungeongame/Game.h"
#include "dungeongame/SortingStudent.h"
#include <chrono>
#include <iostream>

namespace dungeongame {

void Game::runStudentSortTests() {
    using namespace std::chrono;
    std::cout << "\n=== Student Sort Tests ===\n";

    // Small integer test
    std::vector<int> small = {5,2,9,1,6,3,8,4};
    std::cout << "Input: ";
    for (int x : small) std::cout << x << " ";
    std::cout << "\n";

    auto arr1 = small;
    auto t0 = steady_clock::now();
    size_t compsM = mergeSortArray(arr1);
    auto t1 = steady_clock::now();
    auto usM = duration_cast<microseconds>(t1 - t0).count();
    std::cout << "MergeSort result: ";
    for (int x : arr1) std::cout << x << " ";
    std::cout << "\n  comps=" << compsM << " time_us=" << usM << "\n";

    auto arr2 = small;
    t0 = steady_clock::now();
    size_t compsQ = quickSortArray(arr2);
    t1 = steady_clock::now();
    auto usQ = duration_cast<microseconds>(t1 - t0).count();
    std::cout << "QuickSort result: ";
    for (int x : arr2) std::cout << x << " ";
    std::cout << "\n  comps=" << compsQ << " time_us=" << usQ << "\n";

    // Small inventory test
    if (player.inventorySize() == 0) {
        player.addItem(Item("Potion", 10));
        player.addItem(Item("Sword", 50));
        player.addItem(Item("Bow", 45));
    }
    std::vector<Item> items;
    for (size_t i = 0; i < player.inventorySize(); ++i) items.push_back(player[i]);

    auto im = items;
    auto pairM = mergeItems(im);
    std::cout << "\nMergeItems sorted names: ";
    for (auto &it : pairM.first) std::cout << it.name << " ";
    std::cout << "\n  comps=" << pairM.second << "\n";

    im = items;
    auto pairQ = quickItems(im);
    std::cout << "QuickItems sorted names: ";
    for (auto &it : pairQ.first) std::cout << it.name << " ";
    std::cout << "\n  comps=" << pairQ.second << "\n";

}

} // namespace dungeongame
