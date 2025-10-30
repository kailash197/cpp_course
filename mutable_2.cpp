/*
mutable data members:

- Allow modification inside const member functions.
- Useful for tracking internal state (e.g., counters, caches, flags) without violating logical constness.
- Does not affect the object's externally visible state.
- Common use cases:
    - Logging or debugging counters.
    - Lazy evaluation or memoization.
    - Thread-local or transient flags.
- Should be used sparingly and only when truly necessary.
- Helps preserve const-correctness while enabling internal flexibility.
*/

#include <iostream>
#include <string>
#include <memory>

class Robot {
private:
    int version;
    std::string name;

    // 🔹 mutable members
    mutable size_t accessCount = 0;         // Tracks how many times getName() is called
    mutable bool cached = false;            // Simulates lazy evaluation
    mutable std::string cachedName;         // Stores cached result
    mutable std::string logMessage;         // Simulates logging

public:
    Robot(int v, std::string s) : version(v), name(s) {}

    // 🔹 const method modifying mutable members
    std::string getName() const {
        ++accessCount;  // ✅ allowed because accessCount is mutable

        if (!cached) {
            cachedName = "Robot-" + name;  // Simulate expensive computation
            cached = true;
        }

        logMessage = "getName() called";  // ✅ allowed because logMessage is mutable

        return cachedName;
    }

    void printStatus() const {
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Access Count: " << accessCount << std::endl;
        std::cout << "Log: " << logMessage << std::endl;
    }
};

int main() {
    auto bot = std::make_unique<Robot>(1, "XTY");

    bot->printStatus();   // First call → triggers computation
    bot->printStatus();  // Second call → uses cached result
    bot->printStatus();  // Third call → uses cached result

    return 0;
}

/*
mutable allows internal state changes in const methods.
accessCount tracks how many times getName() is called.
cachedName and cached simulate lazy evaluation — computed once, reused later.
logMessage simulates internal logging without breaking const correctness.

// 🔹 Lazy Evaluation:
//   - Delay computation until the result is actually needed.
//   - Avoids unnecessary work if the value is never used.

// 🔹 Memoization:
//   - Cache the result of expensive computation.
//   - Reuse cached result on future calls with the same input.
//   - Common in recursive algorithms and performance-critical code.

Output:

Name: Robot-XTY
Access Count: 1
Log: getName() called
Name: Robot-XTY
Access Count: 2
Log: getName() called
Name: Robot-XTY
Access Count: 3
Log: getName() called

*/