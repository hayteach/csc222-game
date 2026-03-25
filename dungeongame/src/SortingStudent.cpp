#include "dungeongame/SortingStudent.h"
#include <vector>
#include <utility>

namespace dungeongame {

// Student skeletons — these intentionally contain minimal implementations.
// Students should replace the bodies with correct recursive algorithms and
// comparison counting as described in the lab handout.

size_t mergeSortArray(std::vector<int>& arr) {
    // TODO: implement merge sort and return comparison count
    (void)arr;
    return 0;
}

size_t quickSortArray(std::vector<int>& arr) {
    // TODO: implement quick sort and return comparison count
    (void)arr;
    return 0;
}

std::pair<std::vector<Item>, size_t> mergeItems(std::vector<Item> v) {
    // TODO: implement merge sort for Items (compare by name)
    return std::make_pair(v, 0u);
}

std::pair<std::vector<Item>, size_t> quickItems(std::vector<Item> v) {
    // TODO: implement quick sort for Items (compare by name)
    return std::make_pair(v, 0u);
}

} // namespace dungeongame
