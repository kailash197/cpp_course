#include <iostream>
#include <vector>

class Buffer {
private:
    std::vector<int> data;

public:
    Buffer(std::initializer_list<int> initList) : data(initList) {}

    // Const version, returns copy
    int getElement(size_t index) const {
        return data[index];
    }

    // Non-const version, returns reference
    int& getElement(size_t index) {
        return data[index];
    }
};

int main() {
    Buffer buffer = {1, 2, 3, 4, 5};

    // Accessing element (const version)
    std::cout << "Element at index 2 (const): " << buffer.getElement(2) << std::endl;

    // Modifying element (non-const version)
    buffer.getElement(2) = 10;

    // Verifying modification
    std::cout << "Element at index 2 (modified): " << buffer.getElement(2) << std::endl;

    return 0;
}
/*
Element at index 2 (const): 3
Element at index 2 (modified): 10
*/
