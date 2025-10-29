#include <iostream>
/*
lvalue:
    - An Lvalue refers to an object that persists beyond a single expression.
    - something of which address can be taken
    - It can only bind to objects that have a memory location. 
        These values are typically variables in most cases.
    - references are always lvalue in C++
    - can't have lvalue reference of rvalue

rvalue:
    - a temporary value that does not have a persistent memory address.
    - can be a literal, or return of a function which returns a rvalue
    - It typically appears on the right-hand side of an assignment and is not assignable.
    - can't assign values to rvalue, rvalue is assigned to lvalue
    - Often used in expressions and passed to functions.
    - can be stolen for efficiency instead of copying
    - All temporaries are rvalues, but not all rvalues are temporaries.
    - An rvalue reference refers to a temporary object (rvalue) that doesn't have a persistent memory location.
    - Rvalues are non-persistent, non-assignable, and typically used to initialize or move data.
    - They can be bound to `const T&` or `T&&` (rvalue reference), but not to non-const `T&`.
    - A named rvalue reference, such as an rvalue reference parameter, itself is an lvalue because it has a name!

Uses:
    - lvalue references are useful when passing large objects to functions.
    - lvalues are also useful when functions must modify the original object.
    - const lvalue refs (const int& ) can bind to both lvalue and rvalue.
    - they help distinguish between modifiable objects and temporary values
    - they're crucial in function overloading
    - Move semantics: Efficiently transfer resources from temporary objects.
    - rvalue references and move semantics enhance perfomance by making the process of transferring ownership of resources less costly.
    - Rvalue references (`&&`): Allow functions to accept and manipulate rvalues.

Function:
    - pass-by-value accept both lvalue and rvalue as it needs just a copy no ref.
*/

int& getvalue(){
    static int x = 5; // static - initialized only once in first call
    return x; // returns lvalue reference
}

// accepts both lvalue and rvalue, pass by value
void setvalue1(int value){
}

// const lvalue ref accepts both lvalue and rvalue
void setvalue2(const int& v){}

// non-const lvalue ref only accepts lvalue (no rvalues)
void setvalue3(int& v){}

// accepts Only Rvalues via T&&
void setvalue4(int&& v){};

//Template with Perfect Forwarding, accepts both lvalue and rvalue
template <typename T>
void setvalue5(T&& v){};


// overload using lvalue and rvalues
void printName(std::string& name){
    std::cout<<"[lvalue overload]: " <<name <<std::endl;
}

void printName(std::string&& name){
    std::cout<<"[rvalue overload]: " <<name <<std::endl;
}

void helper(std::string&& message){}

void handlemessage(std::string && message){
    //helper(message); // error: an rvalue reference cannot be bound to an lvalue

    //named variable `message` is an lvalue
    // If you want to forward this rvalue reference parameter to another function
    // as an rvalue, then you need to use std::move() to cast the lvalue to an rvalue.

    helper (std::move(message));
}


template <typename T>
void print(const T& x){
    std::cout<<x<<std::endl;
}

int main(){

    int x = 10;  // x is an lvalue
    int a = 5;       // a is an lvalue
    int b = a + 2;   // (a + 2) is an rvalue

    getvalue() = 500; // getvalue() is lvalue ref, rvalue is assigned to lvalue
    print(getvalue()); // 500

    // int& value = 10; invalid: can't bind non-const lvalue ref (int&) to an rvalue

    //1. rvalue can be bind to const lvalue reference
    const int& value = 10; print(value); // 10
    //2. can use rvalue reference which is specifically designed to bind to temporaries
    int&& value2 = 100; print(value2); // 100


    int& j = getvalue(); print(j); // 5 as j is lvalue ref to x
    j = 543;
    print(getvalue()); //543

    int num = 123;
    // SetValue() takes a copy so accepts both lvalue and rvalue
    setvalue1(123); // 
    setvalue1(num);

    //setvalue()
    setvalue2(123);
    setvalue2(num);

    //non-const lvalue ref
    // setvalue3(123); rejects rvalue
    setvalue3(num);
    
    // T&& - rvalue ref
    setvalue4(123); //accepts rvalue
    // setvalue4(num); rvalue ref can't be bind to lvalue

    //Template with Perfect Forwarding
    // Combined with std::forward<T>(v), this can forward both lvalues and rvalues correctly.
    // This is the backbone of universal references and modern C++ APIs.

    std::string name = "Wolverine";
    printName(name); // [lvalue overload]: Wolverine
    printName(name + " X-men"); //[rvalue overload]: Wolverine X-men    

    return 0;
}
