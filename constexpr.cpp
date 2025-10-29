#include <iostream>

constexpr int square(int x) {
    return x * x;
}

int main() {
    const int x = 10; // x is a const variable, initialized with a value known at compile-time
    int y = 20;
    const int z = y; // z is const, but its value is determined at run-time
    
    constexpr int a = square(5); // a is evaluated at compile-time
    // constexpr int b = square(y); // Error: y is not a constant expression

    std::cout << "x: " << x << std::endl;
    std::cout << "z: " << z << std::endl;
    std::cout << "a: " << a << std::endl;

    return 0;
}
