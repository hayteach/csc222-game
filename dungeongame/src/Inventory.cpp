#include "dungeongame/Inventory.h"
#include <stdexcept>
#include <algorithm>

// Implementation notes (for Week 02 - ADTs & Pointers):
// - This translation unit implements the Inventory ADT defined in the header.
// - Memory management: Inventory manually allocates a contiguous block of
//   storage on the heap and manages its lifetime. The destructor cleans up
//   owned memory to avoid leaks — ownership responsibilities are explicit.
// - Growth policy: capacity doubles when needed (amortized cost analysis),
//   which teaches students about time/space trade-offs of ADT implementations.
// - Pointer exposure: `rawData()` allows pointer-based traversal. Use this to
//   demonstrate pointer arithmetic while emphasizing bounds checks and safety.

using namespace std; // Standard namespace

namespace dungeongame {

static size_t nextCap(size_t cur) { return cur == 0 ? 1 : cur * 2; }

Inventory::Inventory(size_t initial) : data(nullptr), sz(0), cap(0) {
    if (initial > 0) {
        cap = initial;
        data = new Item[cap];
    }
}

Inventory::~Inventory() {
    delete[] data;
}

void Inventory::resize(size_t newCap) {
    Item* newData = new Item[newCap];
    for (size_t i = 0; i < sz; ++i) newData[i] = move(data[i]);
    delete[] data;
    data = newData;
    cap = newCap;
}

void Inventory::add(const Item& item) {
    if (sz >= cap) {
        size_t newCap = nextCap(cap);
        if (newCap <= cap) newCap = cap + 1;
        resize(newCap);
    }
    data[sz++] = item;
}

Item Inventory::removeAt(size_t idx) {
    if (idx >= sz) throw out_of_range("Inventory::removeAt index");
    Item removed = data[idx];
    for (size_t i = idx; i + 1 < sz; ++i) data[i] = move(data[i+1]);
    --sz;
    return removed;
}

Item& Inventory::operator[](size_t idx) {
    if (idx >= sz) throw out_of_range("Inventory::operator[]");
    return data[idx];
}

const Item& Inventory::operator[](size_t idx) const {
    if (idx >= sz) throw out_of_range("Inventory::operator[] const");
    return data[idx];
}

} // namespace dungeongame
