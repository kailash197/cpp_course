#include <iostream>
#include <vector>

/*
- every container defines a type named iterator to represent iterators for that type of container
- begin(): iterator to the first object/element
- end(): iterator to one past the last element
- rbegin(): reverse begin() or iterator to the last element
- rend(): iteratore to one before the first element
- Use pre-increment instead of post-increment when possible because pre-increment is at least as
efficient, and usually more efficient. iter++ must return a new iterator object, while ++iter can
simply return a reference to iter.

const_iterator
- If you do not need to modify the elements of a vector, you should use a const_iterator. This rule
makes it easier to guarantee correctness of your code, and helps the compiler to perform better
optimizations.
- use cbegin() and cend(), rcbegin(), rcend() with auto as const-ness is ignored by auto
*/
template<typename T>
void print_vector(const std::vector<T>& vec) {
    std::cout<<"[ ";
    for (const auto& val : vec) {
        std::cout<< val << ", ";
    }
    std::cout<<"] => size: " << vec.size() << std::endl;
}

int main(){
    std::vector<int> numbers {1,2,3,4,5};
    print_vector(numbers);
    std::vector<int>::iterator front = numbers.begin();
    auto last = numbers.end();
    std::cout << *front <<std::endl;
    std::cout << *(last-1) <<std::endl;

    for(auto itr = numbers.begin(); itr != numbers.end(); ++itr){
        std::cout<<*itr<<std::endl;
    }

    for(auto itr = begin(numbers); itr != end(numbers); ++itr){
        std::cout<<*itr<<std::endl;
    }

    //string objects
    std::vector<std::string> strings(5, "hello");
    print_vector(strings);
    for(auto& val: strings){
        val.append(" world");
    }

    print_vector(strings);

    for(auto it=strings.begin(); it != strings.end(); ++it){
        it->append(" again");
    }
    print_vector(strings);

    return 0;
}