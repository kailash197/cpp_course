#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>

template <typename MapType>
void print_map(const MapType& m) {
    std::cout << "{\n";
    for (const auto& [key, value] : m) {
        std::cout << "  "<< key << ": " << value << ",\n";
    }
    std::cout << "}\n";
}

template<typename T>
void print_vector(const std::vector<T>& vec) {
    if (vec.size() < 1){
        std::cout << "[] => size: 0" << std::endl;
        return;
    }
    std::cout << "[";
    std::for_each(vec.begin(), vec.end()-1, [](const T& val) {
        std::cout << val << ", ";
    });
    std::cout << vec.back() << "] => size: " << vec.size() << std::endl;
}

int main(){
    std::vector<int> testIntVector {1,2,3,4,5};
    std::vector<std::string> testStringVector {"hello", "world"};

    std::map<std::string, std::string> testMap {{"USA", "DC"}, {"Canada", "Ottawa"}};
    std::unordered_map<std::string, int> testUnorderedMap {{"Feb", 2},{"Jan", 1}};

    print_vector(testIntVector);
    print_vector(testStringVector);
    print_map(testMap);
    print_map(testUnorderedMap);

    return 0;
}