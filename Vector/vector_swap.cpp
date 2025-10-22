#include <iostream>
#include <vector>
/*

- swap
    - swap contents of two vectors in constant time
*/


void print_vector(const std::vector<int>& vec) {
    std::cout << "size of vector is " << vec.size() << std::endl;
    for (const auto& val : vec) {
        std::cout<< val << std::endl;
    }
}
int main(){

    std::vector<int> first{1,2,3,4,5};
    std::vector<int> second{11,22,33,44,55,66};
    std::cout<<"First: "<<std::endl;
    print_vector(first);

    std::cout<<"Second: "<<std::endl;
    print_vector(second);

    first.swap(second);
    std::cout<<"First: "<<std::endl;
    print_vector(first);

    std::cout<<"Second: "<<std::endl;
    print_vector(second);



    return 0;
}
/*

First: 
size of vector is 5
1
2
3
4
5
Second: 
size of vector is 6
11
22
33
44
55
66
First: 
size of vector is 6
11
22
33
44
55
66
Second: 
size of vector is 5
1
2
3
4
5

*/
