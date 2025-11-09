#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <type_traits>

// --- Base template for generic types ---
template<typename T>
void print(const T& value) {
    std::cout << value;
}

// --- Specialization for std::pair ---
template<typename T1, typename T2>
void print(const std::pair<T1, T2>& p) {
    std::cout << "(";
    print(p.first);
    std::cout << ", ";
    print(p.second);
    std::cout << ")" <<std::endl;
}

// --- Overload for std::vector ---
template<typename T>
void print(const std::vector<T>& vec) {
    std::cout << "[ ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        print(*it);
        if (std::next(it) != vec.end()) std::cout << ", ";
    }
    std::cout << " ]"<<std::endl;
}

// --- Overload for std::map ---
template<typename K, typename V>
void print(const std::map<K, V>& m) {
    std::cout << "{ ";
    for (auto it = m.begin(); it != m.end(); ++it) {
        print(it->first);
        std::cout << ": ";
        print(it->second);
        if (std::next(it) != m.end()) std::cout << ", ";
    }
    std::cout << " }"<<std::endl;
}

// --- Variadic helper for printing multiple things ---
template<typename T, typename... Args>
void print_all(const T& first, const Args&... rest) {
    print(first);
    ((std::cout << " ", print(rest)), ...);
    std::cout << std::endl;
}

// --- Example usage ---
// int main() {
//     std::pair<int, std::string> p = {1, "One"};
//     std::vector<int> v = {10, 20, 30};
//     std::map<std::string, int> m = {{"Alice", 25}, {"Bob", 30}};

//     std::cout << "Pair: "; print(p); std::cout << std::endl;
//     std::cout << "Vector: "; print(v); std::cout << std::endl;
//     std::cout << "Map: "; print(m); std::cout << std::endl;

//     std::cout << "Mixed: "; print_all(p, v, m);
// }
