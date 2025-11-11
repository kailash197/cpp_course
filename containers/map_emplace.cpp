#include <iostream>
#include <map>

class Data {
public:
    Data(int x) {
        std::cout << "Data constructor called with " << x << "\n";
    }
};

int main() {
    std::map<int, Data> myMap;

    // First emplace: key doesn't exist
    auto [it1, inserted1] = myMap.emplace(1, 10);
    std::cout << "Inserted1: " << inserted1 << "\n";

    // Second emplace: key exists, but constructor still called
    auto [it2, inserted2] = myMap.emplace(1, 99);
    std::cout << "Inserted2: " << inserted2 << "\n";


    // First try_emplace: key doesn't exist
    auto [it3, inserted3] = myMap.try_emplace(2, 10);
    std::cout << "Inserted1: " << inserted3 << "\n";

    // Second try_emplace: key exists, constructor NOT called
    auto [it4, inserted4] = myMap.try_emplace(2, 99);
    std::cout << "Inserted2: " << inserted4 << "\n";


    return 0;
}
/*
Data constructor called with 10
Inserted1: 1
Data constructor called with 99
Inserted2: 0
Data constructor called with 10
Inserted1: 1
Inserted2: 0
*/
