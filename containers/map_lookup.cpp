#include <iostream>
#include <map>

class Data {
private:
    int data;
public:
    Data(): data(0){
        std::cout << "DC called" <<std::endl;
    }
    Data(int x) : data(x) {
        std::cout << "PC called" <<std::endl;
    }
    int getData() const {
        return data;
    }
    void setData(int x) {
        data = x;
    }
};

int main() {
    std::map<int, Data> myMap;

    // Insert elements using operator[]
    myMap[1] = Data(10);
    myMap[2] = Data(20);
    myMap[3] = Data(90);

    // Lookup using operator[]
    std::cout << "Key: 1, Value: " << myMap[1].getData() << "\n";
    std::cout << "Key: 2, Value: " << myMap[2].getData() << "\n";

    // Demonstrate that operator[] creates a default object if key doesn't exist
    std::cout << "Key: 4 (not inserted yet), Value: " << myMap[4].getData() << "\n";

    // Print all elements using structured binding (C++17)
    std::cout << "\n--- Map Contents ---\n";
    for (const auto& [key, value] : myMap) {
        std::cout << "Key: " << key << ", Value: " << value.getData() << "\n";
    }

    return 0;
}