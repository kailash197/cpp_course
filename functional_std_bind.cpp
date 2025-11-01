#include <iostream>
#include <functional>
#include <string>

// A simple logging function that takes a prefix and a message
void logMessage(const std::string& prefix, const std::string& message) {
    std::cout << prefix << ": " << message << "\n";
}

int main() {
    // ===============================
    // 🔹 std::bind: Partial Application
    // ===============================
    // std::bind creates a new callable by fixing some arguments.
    // Here, we bind the first argument ("INFO") and leave the second as a placeholder.
    // std::placeholders::_1 represents the first argument to be passed later.
    std::cout << "Using std::bind:\n";
    auto infoLoggerBind = std::bind(logMessage, "INFO", std::placeholders::_1);
    infoLoggerBind("System initialized"); // Output: INFO: System initialized

    // 🔸 Point to Remember:
    // - std::bind is useful for adapting functions to fit callback signatures.
    // - It's less readable than lambdas and considered legacy in modern C++.

    // ===============================
    // 🔹 Lambda: Clearer and Modern
    // ===============================
    // Lambdas are anonymous functions that can capture variables and define behavior inline.
    // This lambda captures nothing and forwards the message with a fixed prefix.
    std::cout << "\nUsing lambda:\n";
    auto infoLoggerLambda = [](const std::string& msg) {
        logMessage("INFO", msg);
    };
    infoLoggerLambda("System initialized"); // Output: INFO: System initialized

    // 🔸 Point to Remember:
    // - Lambdas are preferred in modern C++ for clarity and flexibility.
    // - They support captures, making them powerful for closures and local state.

    // ===============================
    // 🔹 std::function: Type-Erased Wrapper
    // ===============================
    // std::function can store any callable with a matching signature.
    // It's useful when you need runtime polymorphism or to pass callables generically.
    std::cout << "\nUsing std::function:\n";
    std::function<void(std::string)> logger;

    // Assign the lambda to std::function
    logger = infoLoggerLambda;
    logger("System initialized"); // Output: INFO: System initialized

    // Reassign to std::bind version
    logger = infoLoggerBind;
    logger("System initialized"); // Output: INFO: System initialized

    // Reassign to a new lambda with a different prefix
    logger = [](const std::string& msg) {
        logMessage("DEBUG", msg);
    };
    logger("Debugging mode"); // Output: DEBUG: Debugging mode

    // 🔸 Point to Remember:
    // - std::function adds overhead due to type erasure and possible heap allocation.
    // - Use it when you need to store or pass callables generically (e.g., plugin systems, event handlers).

    return 0;
}
