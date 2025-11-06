# Structured Bindings in C++

Structured bindings allow you to unpack tuples, pairs, arrays, and user-defined types into individual named variables in a clean and readable way.

---

## Key Features

- Use `auto` to declare multiple variables from a tuple, array, or struct.
- You cannot specify types like `float`, `double`, etc. — only `auto` is allowed.
- The number of variables on the left must match the number of elements on the right.
- Especially useful with STL containers like `std::map` and `std::unordered_map`.

---

## Example Code

{% raw %}
```cpp
#include <tuple>
#include <iostream>
#include <map>
#include <array>

int main() {
    // Unpacking a tuple
    std::tuple<int, double, std::string> tup = {1, 3.14, "hello"};
    auto [i, d, s] = tup;
    std::cout << i << ", " << d << ", " << s << std::endl;

    // Unpacking an array
    std::array<float, 3> coordinates = {1.1, 2.2, 3.4};
    auto [x, y, z] = coordinates;
    std::cout << x << ", " << y << ", " << z << std::endl;

    // Unpacking elements in a map
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}};
    for (const auto& [key, value] : m) {
        std::cout << key << ": " << value << std::endl;
    }

    return 0;
}
```
{% endraw %}

---

## Summary

Structured bindings simplify code readability and reduce boilerplate when working with compound types. They are available starting from C++17 and are a great tool for modern C++ development.
