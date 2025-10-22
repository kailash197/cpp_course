#include <iostream>
#include <vector>
/*

- Comparison:
    - six overloaded comparison operators ==. !=, >, <, >=, <=
    - Two vectors are equal if they have the same number of elements and all the corresponding
    elements in the two vectors are equal to each other. Two vectors are compared lexicographically, that
    is, one vector is “less than” another if all elements 0 through i–1 in the first vector are equal to
    elements 0 through i-1 in the second vector, but element i in the first is less than element i in the
    second, where i must be in the range 0…n and n must be less than the size() of the smallest of the two
    vectors.
    - Comparing two vectors with operator== or operator!= requires the individual elements to be
        comparable with operator==. Comparing two vectors with operator<, operator>, operator<=, or
        operator>= requires the individual elements to be comparable with operator<. If you intend to
        store objects of a custom class in a vector, make sure to write those operators.
*/


void print_vector(const std::vector<int>& vec) {
    std::cout << "size of vector is " << vec.size() << std::endl;
    for (const auto& val : vec) {
        std::cout<< val << std::endl;
    }
}

using namespace std;

int main(){

    vector<int> vectorOne(10, 15);
    vector<int> vectorTwo(10, 15);
    if (vectorOne == vectorTwo) {
    cout << "equal!" << endl;
    } else {
    cout << "not equal!" << endl;
    }
    
    vectorOne[3] = 50;
    if (vectorOne < vectorTwo) {
    cout << "vectorOne is less than vectorTwo" << endl;
    } else {
    cout << "vectorOne is not less than vectorTwo" << endl;
    }



    return 0;
}
/*
equal!
vectorOne is not less than vectorTwo
*/
