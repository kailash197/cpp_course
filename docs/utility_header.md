# <utility> header

The `<utility>` header in C++ is part of the Standard Library and provides a collection of general-purpose utility components that are widely used in modern C++ programming. It was introduced in **C++98** and has been expanded in later standards like C++11, C++14, C++17, and C++20.

---

### **Importance of `<utility>` in Modern C++**

The `<utility>` header is important because it provides foundational tools that simplify common programming tasks, especially those involving:

- Efficient value transfers (move semantics)
- Pairing values together
- Forwarding arguments in templates
- Working with tuples and structured bindings

These utilities are essential for writing clean, efficient, and modern C++ code, especially in generic programming and template metaprogramming.

---

### **Key Components of `<utility>`**

Here are the most important contents of the `<utility>` header:

#### 1. **`std::pair`**
- A simple container to store two heterogeneous objects.
- Commonly used in associative containers like `std::map`.
- [std::pair](pair.md)

#### 2. **`std::make_pair`**
- A helper function to create a `std::pair` without specifying types explicitly.

#### 3. **`std::move`**
- Enables move semantics by converting an object to an rvalue reference.
- Crucial for performance optimization in modern C++.

#### 4. **`std::forward`**
- Used in perfect forwarding, especially in template functions.
- Preserves the value category (lvalue/rvalue) of arguments.

#### 5. **`std::swap`**
- Swaps the values of two objects.
- Can be customized for user-defined types.

#### 6. **`std::declval`**
- Used in template metaprogramming to simulate the creation of objects without constructing them.

#### 7. **`std::exchange`** (C++14)
- Replaces the value of an object with a new one and returns the old value.

#### 8. **`std::as_const`** (C++17)
- Converts a non-const reference to a const reference.

#### 9. **`std::tuple_size`, `std::tuple_element`** (also used with `<tuple>`)
- Used for compile-time introspection of tuples and pairs.

#### 10. **`std::index_sequence`, `std::make_index_sequence`** (C++14)
- Useful in template metaprogramming, especially with parameter packs.

---
