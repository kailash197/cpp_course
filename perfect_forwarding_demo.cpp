// perfect_forwarding_demo.cpp
// Demonstrates perfect forwarding in C++
// Inspired by Eli Bendersky's article:
// https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c/

#include <iostream>
#include <string>
#include <utility> // for std::forward

// =======================================================
// 🔹 Class with overloaded constructors to show copy vs move
// =======================================================
class Greeter {
public:
    // Constructor for lvalue references (copy)
    Greeter(const std::string& name) : name_(name) {
        std::cout << "[Greeter] Copy constructor\n";
    }

    // Constructor for rvalue references (move)
    Greeter(std::string&& name) : name_(std::move(name)) {
        std::cout << "[Greeter] Move constructor\n";
    }

    void display() const {
        std::cout << "Hello, " << name_ << "!\n";
    }

private:
    std::string name_;
};

// =======================================================
// 🔹 Wrapper class using perfect forwarding
// =======================================================
template<typename T>
class Wrapper {
public:
    // This constructor uses perfect forwarding to construct T in-place
    template<typename... Args>
    Wrapper(Args&&... args) : obj(std::forward<Args>(args)...) {
        std::cout << "[Wrapper] Constructed with perfect forwarding\n";
    }

    void show() const {
        obj.display();
    }

private:
    T obj;
};

int main() {
    std::cout << "=== Forwarding an rvalue ===\n";
    Wrapper<Greeter> w1("Kailash"); // rvalue → move constructor
    w1.show(); // Output: Hello, Kailash!

    std::cout << "\n=== Forwarding an lvalue ===\n";
    std::string name = "Ada";
    Wrapper<Greeter> w2(name); // lvalue → copy constructor
    w2.show(); // Output: Hello, Ada!

    std::cout << "\n=== Forwarding a moved lvalue ===\n";
    Wrapper<Greeter> w3(std::move(name)); // moved lvalue → move constructor
    w3.show(); // Output: Hello, Ada!

    return 0;
}
