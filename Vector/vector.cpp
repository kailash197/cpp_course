#include <iostream>
#include <vector>
#include <algorithm> // Required for sort, reverse
/*
Vector:
- the elements are stored in contiguous memory
- vector is defined in the <vector> header file as a class template
- vector provides a constructor that allows you to specify the number of elements

- Access:
    - Random access of individual elements has a constant complexity.
    - can index into a vector
    - provides an overloaded operator[] in order to access and modify those elements.
    - the operator[] on a vector does not provide bounds checking. 
    - The result of operator[] is undefined when used to access an element outside the vector bounds.
    - This means that any compiler can decide how to behave in that case eg. return value 0
    - at(), front(), back()

- Insert/delete:
    - add new elements to the back or insert them anywhere else
    - Inserting and deleting elements into and from a vector generally takes linear time,
      though these operations actually run in amortized constant time at the end of a vector

- Constructor/Destructors:
    - vector<int> intVector; // Creates a vector of ints with zero elements
    - vector<int> intVector(10, 100); // Creates vector of 10 ints with value 100
    - If you omit the default value, the new objects are zero-initialized. 
        Zero-initialization constructs objects with the default constructor, and 
        initializes primitive integer types (such as char, int, and so on) to 
        zero, primitive floating-point types to 0.0, and pointer types to nullptr.

*/



using namespace std;

template <typename T>
void print_vector(const std::vector<T>& vec) {
    std::cout << "size of vector is " << vec.size() << std::endl;
    for (const auto& val : vec) {
        std::cout << val << std::endl;
    }
}

int main() {
    // 1. Initialization
    vector<int> v1; // An empty vector of integers
    vector<int> v2(5, 10); // A vector with 5 elements, all initialized to 10
    vector<int> v3 = {1, 2, 3, 4, 5}; // List initialization

    // 2. Inserting elements
    v1.push_back(1); // Adds 1 to the end
    v1.push_back(2); // Adds 2 to the end
    v1.push_back(3); // Adds 3 to the end

    // 3. Accessing elements
    cout << "First element in v1: " << v1[0] << endl; // Access using operator[]
    cout << "Second element in v1: " << v1.at(1) << endl; // Access using at()
    cout << "Last element in v1: " << v1.back() << endl; // Access the last element

    // 4. Iterating over the vector
    cout << "Elements in v3: ";
    for (int x : v3) { // Range-based for loop
        cout << x << " ";
    }
    cout << endl;

    //4. using iterators
    vector<int>::iterator itr;
    cout<<"Elements in v3 using iterator: ";
    for(itr=v3.begin(); itr != v3.end(); itr++)
        cout<<*itr<<' ';
    cout << endl;

    // 5. Modifying elements
    v3[0] = 10; // Modify the first element
    v3.at(1) = 20; // Modify the second element using at()

    // 6. Inserting at specific positions
    v3.insert(v3.begin() + 2, 15); // Insert 15 at index 2

    // 7. Erasing elements
    v3.erase(v3.begin() + 3); // Erase element at index 3

    // 8. Checking size and capacity
    cout << "Size of v3: " << v3.size() << endl;
    cout << "Capacity of v3: " << v3.capacity() << endl; // storage capacity of current allocation

    // 9. Sorting the vector
    sort(v3.begin(), v3.end()); // Sort in ascending order

    // 10. Reversing the vector
    reverse(v3.begin(), v3.end()); // Reverse the order

    // 11. Clearing the vector
    v3.clear(); // Removes all elements

    // 12. Checking if the vector is empty
    if (v3.empty()) {
        cout << "v3 is empty." << endl;
    }

    return 0;
}
/*
First element in v1: 1
Second element in v1: 2
Last element in v1: 3
Elements in v3: 1 2 3 4 5 
Elements in v3 using iterator: 1 2 3 4 5 
Size of v3: 5
Capacity of v3: 10
v3 is empty.
*/