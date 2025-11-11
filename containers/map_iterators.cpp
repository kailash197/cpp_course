#include <iostream>
#include <map>

class Data {
private:
    int data;
public:
    Data(int x): data(x) {
        std::cout << "Data constructor called with " << x << "\n";
    }
    int getData() const {
        return data;
    }
};

int main() {
    std::map<int, Data> myMap;

    // First emplace: key doesn't exist
    auto [it1, inserted1] = myMap.emplace(1, 10);
    auto [it3, inserted3] = myMap.try_emplace(2, 10);
    auto [it4, inserted4] = myMap.try_emplace(3, 99);

    //using iterators 
    for (auto itr = myMap.cbegin(); itr != myMap.cend(); ++itr){
        std::cout << "Key: " << itr->first <<", Value: " << itr->second.getData() << std::endl;
    }

    //using range based for loop
    for (const auto& pair: myMap){
        std::cout << "Key: " << pair.first <<", Value: " << pair.second.getData() << std::endl;
    }

    //using range based for loop with structured binding C++17
    for (const auto& [first, second] : myMap ){
        std::cout << "Key: " << first <<", Value: " << second.getData() << std::endl;
    }


    return 0;
}
/*
Data constructor called with 10
Data constructor called with 10
Data constructor called with 99
Key: 1, Value: 10
Key: 2, Value: 10
Key: 3, Value: 99
Key: 1, Value: 10
Key: 2, Value: 10
Key: 3, Value: 99
Key: 1, Value: 10
Key: 2, Value: 10
Key: 3, Value: 99
*/
