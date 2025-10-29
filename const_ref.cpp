#include <iostream>

static int i = 12;
int& return_lvalue(){
    return i;
}

int main(){
    
    int x = 10;

    const int& y = x;

    std::cout << "value: " << y+1<<std::endl;
    std::cout << "value: " << x <<std::endl;

    std::cout << "I: "<< i << std::endl;

    // int& value = x; // OK: value is a reference to x

    const int& value = 10; // OK: const reference can bind to rvalue
    return_lvalue() = 15;
    std::cout << "I: "<< i << std::endl;


    return 0;
}
/*
value: 11
value: 10
I: 12
I: 15
*/
