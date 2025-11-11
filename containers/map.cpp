#include <iostream>
#include <map>
#include "../utilities/print_utils.hpp"

class Data{
    private:
        int data;
    
    public:
        Data() = default;
        
        Data(int d): data(d) {}
        int getData() const{
            return data;
        }
};


int main(){
    std::map<std::string, int> points;
    auto result = points.insert({"Joe", 35});
    if (result.second) std::cout<< "Insertion success" << std::endl;
    else std::cout << "Insertion failed" << std::endl;
    print(points);

    //C++17: initializer for `if`
    if(auto [itr, success] = points.insert({"Mark", 25}); success) std::cout<< "Insertion success" << std::endl;
    print(points);

    // insert or assign
    auto result1 = points.insert_or_assign("Joe", 45);
    if (result1.second) std::cout << "Insertion success" <<std::endl;
    else std::cout << "Value Overwritten" <<std::endl;
    print(points);

    // using operator[]
    points["Harry"] = 34;
    print(points);
    points["Mark"] = 55;
    std::cout << points["Mark"] <<std::endl;
    print(points);

    // using emplace
    std::map<int, Data> map1;
    auto res = map1.insert({1, 2}); // automatically calls Data(int d)
    for (const auto& v: map1){
        std::cout << v.first << "  =>  " << v.second.getData() << std::endl;
    }

    
    std::map<int, std::string> myMap;

    auto [it1, inserted1] = myMap.emplace(1, "ROS2");
    auto [it2, inserted2] = myMap.emplace(1, "Robotics"); // Key exists

    std::cout << "First insert: " << inserted1 << "\n"; // true
    std::cout << "Second insert: " << inserted2 << "\n"; // false
    std::cout << "Value for key 1: " << it2->second << "\n"; // ROS2

    return 0;
}
