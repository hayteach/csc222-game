#pragma once

#include <vector>
#include <utility>
#include "Inventory.h"

// Starter skeleton for students to implement Merge Sort and Quick Sort
// Instructions: implement the functions below in SortingStudent.cpp.
// The functions return the number of element comparisons performed during the sort.
// For the item-based versions, return a pair (sorted_vector, comparisons).

namespace dungeongame {

size_t mergeSortArray(std::vector<int>& arr);
size_t quickSortArray(std::vector<int>& arr);

std::pair<std::vector<Item>, size_t> mergeItems(std::vector<Item> v);
std::pair<std::vector<Item>, size_t> quickItems(std::vector<Item> v);

} // namespace dungeongame
