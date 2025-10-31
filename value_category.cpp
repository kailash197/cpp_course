#include <iostream>
#include <utility>
#include <string>

// ===============================================================
// 🧱 INTRODUCTION
// ---------------------------------------------------------------
// - lvalue: has a name and can appear on the left side of assignment.
// - rvalue: temporary object or literal (no persistent name).
//
//   int x = 10;   // x is lvalue, 10 is rvalue
//
// - lvalue ref: T&
// - rvalue ref: T&&
// - universal ref: T&& inside a template where T is deduced
// ===============================================================


// ===============================================================
// 🧩 Example 1: lvalue and rvalue basics
// ===============================================================

void simple_examples() {
    std::cout << "=== Example 1: lvalue and rvalue basics ===\n";
    int x = 10;           // x is lvalue
    int& lref = x;        // lvalue reference binds to x
    int&& rref = 20;      // rvalue reference binds to temporary 20

    std::cout << "x = " << x << "\n";
    std::cout << "lref = " << lref << "\n";
    std::cout << "rref = " << rref << "\n";

    rref = 50;            // we can modify the temporary through rvalue ref
    std::cout << "rref after modification = " << rref << "\n\n";
}


// ===============================================================
// 🧩 Example 2: Overloading functions for lvalue and rvalue references
// ===============================================================

void process(const std::string& s) {
    std::cout << "Called lvalue reference overload: " << s << "\n";
}

void process(std::string&& s) {
    std::cout << "Called rvalue reference overload: " << s << "\n";
}

void overloading_examples() {
    std::cout << "=== Example 2: Overloading for lvalue and rvalue ===\n";

    std::string name = "Robot";
    process(name);                  // lvalue → calls const lvalue overload
    process(std::string("Drone"));  // rvalue → calls rvalue overload
    process("Sensor");              // rvalue (temporary std::string) → rvalue overload

    std::cout << "\n";
}


// ===============================================================
// 🧩 Example 3: Universal (Forwarding) Reference
// ---------------------------------------------------------------
// T&& becomes:
//   - T&  if passed an lvalue
//   - T&& if passed an rvalue
// ===============================================================

template<typename T>
void universal_ref_example(T&& value) {
    // Inside, we can check what type we actually got
    if constexpr (std::is_lvalue_reference_v<T>) {
        std::cout << "universal_ref_example got an LVALUE reference\n";
    } else {
        std::cout << "universal_ref_example got an RVALUE reference\n";
    }
}

void universal_ref_demo() {
    std::cout << "=== Example 3: Universal Reference ===\n";

    std::string msg = "Hello";
    universal_ref_example(msg);               // lvalue → T = std::string&
    universal_ref_example(std::string("Hi")); // rvalue → T = std::string
    universal_ref_example("World");           // rvalue → T = const char[6]
    std::cout << "\n";
}


// ===============================================================
// 🧩 Example 4: Perfect Forwarding
// ---------------------------------------------------------------
// Perfect forwarding lets you forward arguments exactly as they came in:
// if caller passed an lvalue → forward as lvalue
// if caller passed an rvalue → forward as rvalue
//
// This avoids unnecessary copies and preserves value category.
// ===============================================================

void consume(const std::string& s) {
    std::cout << "consume(const lvalue&): " << s << "\n";
}

void consume(std::string&& s) {
    std::cout << "consume(rvalue&&): " << s << "\n";
}

template<typename T>
void forwarder(T&& arg) {
    std::cout << "forwarder received something...\n";

    // Without std::forward → always lvalue inside this function!
    consume(arg);  // This will always call the lvalue version

    // With std::forward → preserve the original value category
    consume(std::forward<T>(arg));
}

void perfect_forwarding_demo() {
    std::cout << "=== Example 4: Perfect Forwarding ===\n";

    std::string data = "Telemetry";

    std::cout << "\n-- passing lvalue --\n";
    forwarder(data);

    std::cout << "\n-- passing rvalue --\n";
    forwarder(std::string("Odometry"));

    std::cout << "\n";
}


// ===============================================================
// 🧩 Example 5: Move Semantics with rvalue reference
// ---------------------------------------------------------------
// Demonstrates how move semantics improve performance by avoiding copies.
// ===============================================================

class BigData {
public:
    BigData(const std::string& name) : name_(name) {
        std::cout << "Constructed BigData: " << name_ << "\n";
    }

    // Copy constructor
    BigData(const BigData& other) : name_(other.name_) {
        std::cout << "Copied BigData: " << name_ << "\n";
    }

    // Move constructor
    BigData(BigData&& other) noexcept : name_(std::move(other.name_)) {
        std::cout << "Moved BigData: " << name_ << "\n";
    }

private:
    std::string name_;
};

void move_semantics_demo() {
    std::cout << "=== Example 5: Move Semantics ===\n";

    BigData a("MapData");
    BigData b = a;                 // Copy
    BigData c = std::move(a);      // Move (rvalue ref)
    BigData d = BigData("Image");  // Move (temporary)
    std::cout << "\n";
}


// ===============================================================
// 🧠 MAIN FUNCTION
// ===============================================================
int main() {
    simple_examples();
    overloading_examples();
    universal_ref_demo();
    perfect_forwarding_demo();
    move_semantics_demo();

    std::cout << "✅ Done.\n";
    return 0;
}


/*
===============================================================
📘 WHY LEARN VALUE CATEGORIES (lvalue, rvalue, etc.)?
---------------------------------------------------------------
They are the foundation for many modern C++ features that you
will use in ROS 2 and performance-critical C++ code.

Understanding value categories helps you write code that is:
  ✅ Efficient  (avoids unnecessary copies)
  ✅ Correct    (preserves ownership and lifetimes)
  ✅ Modern     (uses move semantics, perfect forwarding, etc.)

---------------------------------------------------------------
| Modern C++ Feature                 | Depends On              | Why It Matters                              |
|------------------------------------|--------------------------|---------------------------------------------|
| Move semantics (std::move)         | rvalue references        | Move data instead of copying (fast message passing). |
| Perfect forwarding (std::forward)  | universal references     | Build generic functions that forward efficiently (used in templates, ROS 2 internals). |
| Emplace functions (emplace_back)   | rvalues                  | Construct objects in-place in containers.   |
| Smart pointers                     | move semantics           | Transfer ownership safely.                  |
| (std::unique_ptr, std::shared_ptr) |                          |                                             |
| Lambda captures and return values  | value category rules     | Control lifetimes and copies.               |
---------------------------------------------------------------

In short:
  • RAII → ensures resources are cleaned up automatically.
  • Value categories → ensure objects are moved or copied efficiently.

Together, they make modern C++ and ROS 2 both safe and fast.
===============================================================
*/


/*
=== Example 1: lvalue and rvalue basics ===
x = 10
lref = 10
rref = 20
rref after modification = 50

=== Example 2: Overloading for lvalue and rvalue ===
Called lvalue reference overload: Robot
Called rvalue reference overload: Drone
Called rvalue reference overload: Sensor

=== Example 3: Universal Reference ===
universal_ref_example got an LVALUE reference
universal_ref_example got an RVALUE reference
universal_ref_example got an LVALUE reference

=== Example 4: Perfect Forwarding ===

-- passing lvalue --
forwarder received something...
consume(const lvalue&): Telemetry
consume(const lvalue&): Telemetry

-- passing rvalue --
forwarder received something...
consume(const lvalue&): Odometry
consume(rvalue&&): Odometry

=== Example 5: Move Semantics ===
Constructed BigData: MapData
Copied BigData: MapData
Moved BigData: MapData
Constructed BigData: Image

✅ Done.
*/
