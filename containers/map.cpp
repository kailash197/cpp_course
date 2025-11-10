#include <iostream>
#include <map>
#include "../utilities/print_utils.hpp"


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
}
