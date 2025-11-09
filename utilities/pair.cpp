#include <iostream>
#include <utility>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include "print_utils.hpp"

std::pair<int, int> getMinMax(const std::vector<int>& nums) {
    int min = *std::min_element(nums.begin(), nums.end());
    int max = *std::max_element(nums.begin(), nums.end());
    return {min, max};
}

int main(){
    std::pair<int, std::string> p1(1, "robot");
    std::cout << "ID: " << p1.first << ", Name: " << p1.second << std::endl;

    auto p2 = std::make_pair(2, "drone");
    std::cout << "ID: " << p2.first << ", Name: " << p2.second << std::endl;

    std::pair<double, int> apair {1.1,2};
    std::cout<<"Pair: ";
    print(apair);

    // std::pair in map
    std::map<int, std::string> robotMap;
    robotMap.insert(std::make_pair(1, "xArm"));
    robotMap.insert({2, "RB-1"});
    
    for (const auto& p : robotMap) {
        std::cout << "ID: " << p.first << ", Name: " << p.second << std::endl;
    }

    for (const auto [first, second] : robotMap) {
        std::cout << "ID: " << first << ", Name: " << second << std::endl;
    }

    // Structured Bindings (C++17)
    std::pair<int, std::string> p = {3, "TUGBOT"};
    auto [id, name] = p;
    std::cout << "ID: " << id << ", Name: " << name << std::endl;

    return 0;
}
