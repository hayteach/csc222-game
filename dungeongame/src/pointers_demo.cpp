#include <iostream>
#include <iomanip>

// Simple game-themed pointers demo for Week 02: Pointers & Dynamic Memory
// - Follow exercise variable names: myVar, iptr, myArray, ptrToMyArray
// - myVar is interpreted as a game quantity (e.g., number of potions to prepare)

class IntArray {
private:
    int *data;
    int size;
public:
    IntArray(int n) : data(n > 0 ? new int[n] : nullptr), size(n) {}
    ~IntArray() { delete[] data; }
    int &operator[](int i) { return data[i]; }
    int *rawData() const { return data; }
    int getSize() const { return size; }
};

int main() {
    std::cout << "Enter an integer (e.g., number of potions to prepare): ";
    int myVar;
    if (!(std::cin >> myVar) || myVar <= 0) {
        std::cerr << "Invalid input; defaulting to 5.\n";
        myVar = 5;
    }

    // Pointer to an automatic variable
    int *iptr = &myVar;

    std::cout << "myVar value: " << myVar << "\n";
    std::cout << "iptr address: " << static_cast<const void*>(iptr) << "\n";
    std::cout << "*iptr value: " << *iptr << "\n\n";

    // Dynamic array allocation
    int *myArray = new int[myVar];
    for (int i = 0; i < myVar; ++i) {
        myArray[i] = i + 1; // fill with values 1..myVar (potion IDs)
    }

    std::cout << "Array values (direct indexing): ";
    for (int i = 0; i < myVar; ++i) {
        std::cout << myArray[i] << (i + 1 == myVar ? '\n' : ' ');
    }

    int *ptrToMyArray = myArray; // pointer to first element
    std::cout << "Array values (via pointer ptrToMyArray): ";
    for (int i = 0; i < myVar; ++i) {
        std::cout << *(ptrToMyArray + i) << (i + 1 == myVar ? '\n' : ' ');
    }

    std::cout << "\nUsing RAII wrapper (IntArray) to manage memory: \n";
    {
        IntArray arr(myVar);
        for (int i = 0; i < arr.getSize(); ++i) arr[i] = i + 1;
        std::cout << "RAII array values: ";
        for (int i = 0; i < arr.getSize(); ++i) std::cout << arr[i] << (i + 1 == arr.getSize() ? '\n' : ' ');
        std::cout << "RAII raw address: " << static_cast<const void*>(arr.rawData()) << "\n";
    } // destructor called here; memory freed

    // Free manual allocation
    delete[] myArray;
    std::cout << "Manual delete[] called. Program complete.\n";

    return 0;
}
