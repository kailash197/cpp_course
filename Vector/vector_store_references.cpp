#include <iostream>
#include <vector>
#include <functional>
#include <type_traits>

template<typename T>
void print_vector(const std::vector<T>& vec) {
    std::cout<<"[ ";
    for (const auto& val : vec) {
        //ensures the check is done at compile time, so only the correct branch is compiled.
        if constexpr (std::is_same_v<T, std::reference_wrapper<typename T::type>>) {
            std::cout<< val.get() << ", ";
        } else {
            std::cout<< val << ", ";
        }
        
    }
    std::cout<<"] => size: " << vec.size() << std::endl;
}

int main(){

    std::string s1 = "Hello";
    std::string s2 = "There";

    //create vector of references to strings
    std::vector<std::reference_wrapper<std::string>> v1 {std::ref(s1)};
    print_vector(v1);

    v1.push_back(std::ref(s2)); //add an element
    print_vector(v1);

    v1[1].get() += "!!!"; // modify second element
    std::cout << v1[1].get()  <<std::endl;
    print_vector(v1);
    std::cout << s2 << std::endl; // s2 is also modified
    return 0;
}
