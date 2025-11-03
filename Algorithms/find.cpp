#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int num;
    vector<int> myVector {23, 34, 45, 56, 78, 89};

    while(true){
        cout << "Enter number to search, 0 to exit: ";
        cin >> num;
        if (num == 0) break;

        auto end = myVector.cend();
        auto itr = find(myVector.cbegin(), end, num);
        // change iterator range to search in subrange.

        if (itr != end){
            cout << "Found the number: " << *itr <<endl;
        } else {
            cout << "Number not found."<<endl;
        }

        // C++17 style
        if (auto itr = find(myVector.cbegin(), end, num); itr != end){
            cout << "Found the number: " << *itr <<endl;
        } else {
            cout << "Number not found."<<endl;
        }
    }
}