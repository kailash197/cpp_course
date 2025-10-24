#include <iostream>
#include <vector>
#include <algorithm> // for std::for_each

/*
- Copy & Assign Vectors
    - vector stores copies of objects
    - vector destructor calls desctructor for each objects
    - copy constructor and assignment operator of vector class perform deep copies
    - RECOMMENDATION: pass vectors by reference or const reference to func or methods.
    - assign(): method to clear current elements and adds any number of new elements.
*/

// template<typename T>
// void print_vector(const std::vector<T>& vec) {
//     std::cout<<"[ ";
//     for (const auto& val : vec) {
//         std::cout<< val << ", ";
//     }
//     std::cout<<"] => size: " << vec.size() << std::endl;
// }

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
    std::vector<int> intVector(10); 
    print_vector(intVector); // [0, 0, 0, 0, 0, 0, 0, 0, 0, 0] => size: 10

    // reuse 
    intVector.assign(5, 100); // clear & reassign
    print_vector(intVector); // [100, 100, 100, 100, 100] => size: 5

    intVector.assign({ 1, 2, 3, 4 }); // assign() accepts initializer list
    print_vector(intVector); // [1, 2, 3, 4] => size: 4

    std::vector<double> v1{};
    print_vector(v1); // [] => size: 0

    return 0;
}
