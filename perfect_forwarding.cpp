// Demonstrates perfect forwarding in C++
// Inspired by Eli Bendersky's article: https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c/

#include <iostream>
#include <string>
#include <utility> // for std::forward

// 1: Overloaded functions to detect value category
// These simulate different behaviors based on whether the argument is an lvalue or rvalue
void log(const std::string& msg) {
    std::cout << "[Lvalue] " << msg << "\n";
}

void log(std::string&& msg) {
    std::cout << "[Rvalue] " << msg << "\n";
}

// 2. Perfect forwarding wrapper
// =======================================================
// This template preserves the value category of the argument
// T&& is a forwarding (universal) reference ONLY in a deduced context
template<typename T>
void forwardToLog(T&& arg) {
    // std::forward<T>(arg) ensures:
    // - If arg is an lvalue, it stays an lvalue
    // - If arg is an rvalue, it stays an rvalue
    // This is the essence of perfect forwarding
    log(std::forward<T>(arg));
}

// 3: Factory pattern using perfect forwarding
// =======================================================
// This shows how perfect forwarding is used in constructors
// to forward arguments to member objects efficiently
template<typename T>
class Wrapper {
public:
    template<typename... Args>
    Wrapper(Args&&... args) {
        // Perfectly forward constructor arguments to T
        // This avoids unnecessary copies and preserves value categories
        obj = T(std::forward<Args>(args)...);
    }

    void show() const {
        obj.display();
    }

private:
    T obj;
};

// A simple class to be wrapped
class Greeter {
public:
    Greeter(std::string name) : name_(std::move(name)) {}

    void display() const {
        std::cout << "Hello, " << name_ << "!\n";
    }

private:
    std::string name_;
};

int main() {
    // test log() function
    std::string test = "Test message";
    log(test);
    log("Temp test message");


    std::string text = "Forwarded";
    // 'text' is an lvalue, so log(const std::string&) is called
    forwardToLog(text); // Output: [Lvalue] Forwarded


    // A temporary string is an rvalue, so log(std::string&&) is called
    forwardToLog(std::string("Temporary")); // Output: [Rvalue] Temporary

    // std::move turns 'text' into an rvalue, so rvalue overload is called
    forwardToLog(std::move(text)); // Output: [Rvalue] Forwarded

    // 4: Using perfect forwarding in a factory
    // =======================================================
    // Wrapper forwards constructor arguments to Greeter
    // Wrapper<Greeter> w1("Kailash"); // Perfectly forwards string to Greeter constructor
    // w1.show(); // Output: Hello, Kailash!

    // std::string name = "Ada";
    // Wrapper<Greeter> w2(name); // Forwards lvalue
    // w2.show(); // Output: Hello, Ada!

    return 0;
}
