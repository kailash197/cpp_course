---
layout: default
title: C++ Self-Learning Roadmap
---

# C++ Self-Learning Roadmap

## I. Basic Concepts
- Variables and Data Types  
- Operators (Arithmetic, Logical, Bitwise)  
- Control Flow (if, switch, loops)  
- Functions and Overloading  
- Arrays and Strings  
- Pointers and References  
- Structures  
- Input/Output (`cin`, `cout`)  
- File Handling  
- Dynamic Memory (`new`, `delete`)  
- Namespaces  
- Header Files and Compilation Units  

**Resources:** [LearnCpp.com](https://www.learncpp.com/), Bjarne Stroustrup's book

---

## II. Intermediate Concepts
- Object-Oriented Programming (OOP)  
- Inheritance and Polymorphism  
- Virtual Functions and Abstract Classes  
- Templates and Specialization  
- Exception Handling  
- [Standard Template Library (STL)](docs/standard_library.md)
- Iterators and Algorithms  
- Operator Overloading  
- Type Casting  

**Resources:** C++ Primer, [cppreference.com](https://en.cppreference.com/)

---

## III. Advanced Concepts
- RAII  
- Smart Pointers  
- Move Semantics and Rvalue References  
- Lambdas and Functors  
- `std::function` and `std::bind`  
- Multithreading  
- Type Traits and SFINAE  
- CRTP  
- Expression Templates  
- Custom Allocators  
- Design Patterns  

**Resources:** Effective Modern C++, [C++ Weekly](https://www.youtube.com/@cppweekly)

---

## IV. C++11 Features
- `auto` and Range-based `for`  
- Lambdas  
- Rvalue References  
- `nullptr` and Uniform Initialization  
- Smart Pointers  
- `std::function`, `std::bind`  
- `constexpr`, `static_assert`  
- Variadic Templates  
- Thread Library  
- `enum class`, `override`, `final`  

**Reference:** [Perfect Forwarding by Eli Bendersky](https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c/)

---

## V. C++14 Features
- Generic Lambdas  
- Return Type Deduction  
- `std::make_unique`  
- Variable Templates  
- `decltype(auto)`  
- Relaxed `constexpr`  
- `std::integer_sequence`  

**Reference:** [C++14 Reference](https://en.cppreference.com/w/cpp/14)

---

## VI. C++17 Features
- [Structured Bindings](structured_binding.md)
- `if constexpr`  
- Inline Variables  
- Fold Expressions  
- `std::optional`, `std::variant`, `std::any`  
- `std::filesystem`  
- `std::string_view`  
- Parallel STL Algorithms  
- Template Argument Deduction  
- `std::scoped_lock`  

**Reference:** [Modern C++ Feature Summary](https://www.slideshare.net/slideshow/mastering-modern-c-c-11-c-14-c-17-c-20-c-23/275446486)

---

## VII. C++20 Features
- Concepts and Constraints  
- Ranges Library  
- Coroutines (`co_await`, `co_yield`, `co_return`)  
- Modules (experimental)  
- Three-way Comparison (`<=>`)  
- Calendar and Time Zones (`std::chrono` updates)  
- Expanded `constexpr` (e.g., `std::vector` in `constexpr`)  
- Immediate Functions (`consteval`)  
- Template Parameter Lists in Lambdas  
- Designated Initializers  
- Bit Manipulation Utilities (`std::rotl`, `std::countr_zero`, etc.)  
- `std::span` for lightweight array views  
- Improved `thread`, `atomic`, and synchronization primitives  

**Reference:** [C++20 Feature Support](https://en.cppreference.com/w/cpp/compiler_support/20)

---

## VIII. C++23 Features
- Deduction Guides for `std::pair`, `std::tuple`, and `std::array`  
- `std::expected` for error handling  
- `std::print` and `std::println`  
- `std::flat_map` and `std::flat_set`  
- Multidimensional Subscript Operator (`operator[](...)`)  
- Monadic Operations for `std::optional`  
- Improved `constexpr` and `consteval` support  
- Unicode Character Support (`char8_t`, `std::u8string`)  
- Standard Library Modules (`std`, `std.compat`)  
- Stacktrace Library (`std::stacktrace`)  
- Ranges Improvements (`views::cartesian_product`, `views::chunk`, etc.)  

**Reference:** [C++23 Feature Support](https://en.cppreference.com/w/cpp/compiler_support/23)
