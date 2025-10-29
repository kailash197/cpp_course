/*
// Move semantics require a move constructor and move assignment operator.
// Used when the source object is a temporary that will be destroyed soon.
// They transfer ownership of resources from source to target object.
// Source object is left in a valid but indeterminate state.
// Often, source members are reset to null or default values.
// Enables shallow copy of member variables with ownership transfer.
// Prevents dangling pointers and memory leaks.
// Improves performance by avoiding deep copies.

// 🔹 Shallow Copy:
// Copies pointers and basic member variables.
// Both objects share the same underlying memory.
// Changes in one may affect the other.
// Fast but risky if ownership isn't managed properly.

// 🔹 Deep Copy:
// Copies actual data, not just pointers.
// Each object has its own independent copy of resources.
// Safe and avoids shared state or memory issues.
// Slower due to full duplication of resources.

// move semantics to a class:
    - implement move constructor, marked noexcept and 
    - implement move assignment operator also marked noexcept

// noexcept qualifier to tell the compiler that they don’t throw any
exceptions.

//If you have dynamically allocated memory in your class, then
you typically should implement a destructor, copy constructor,
move constructor, copy assignment operator, and move
assignment operator. This is called the Rule of Five.

//However, in modern C++, you should adopt the so-called rule of zero.
The rule of zero states that you should design your classes in such a
way that they do not require any of those five special member
functions. How do you do that? Basically, you should avoid having
any old-style dynamically allocated memory. Instead, use modern
constructs such as Standard Library containers. For example, use a
vector<vector<SpreadsheetCell>> instead of the SpreadsheetCell** data member in the Spreadsheet class. 
The vector handles memory automatically, so there is no need for any of those five special member functions.




*/

#include <iostream>

using namespace std;

template <typename T>

// swap using move semantics
void swap(T& a, T& b){
    T temp(std::move(a));
    a = std::move(b);
    b = std::move(temp);
}

int main(){
    std::string firstName = "Kailash";
    std::string lastName = "Khadka";

    cout << firstName << lastName << endl;
    swap(firstName, lastName);
    cout << firstName << lastName << endl;

    return 0;
}