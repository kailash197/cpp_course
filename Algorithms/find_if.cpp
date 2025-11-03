#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

bool even_number(int num){
    return num % 2 == 0;
}

int main() {
    int num;
    vector<int> myVector {23, 33, 45, 56, 78, 89};
    cout << "Searching for even number " <<endl;

    auto end = myVector.cend();

    // C++17 style
    if (auto itr = find_if(myVector.cbegin(), end, even_number); itr != end){
        cout << "Found the number: " << *itr <<endl;
    } else {
        cout << "Number not found."<<endl;
    }

    // using lambda expression
    if (auto itr = find_if(myVector.cbegin(), end, [](int num){return num % 2 == 0;}); itr != end){
        cout << "Found the number: " << *itr <<endl;
    } else {
        cout << "Number not found."<<endl;
    }
}