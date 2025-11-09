# `std::pair` template
- `std::pair` is a **template class** in the C++ Standard Library, defined in the `<utility>` header.
- It is used to store two potentially heterogeneous objects, but related values, as a single unit.
- The two elements are referred to as `first` and `second`.

### **Definition**

```cpp
template <class T1, class T2>
struct pair {
    T1 first;
    T2 second;

    // Constructors
    constexpr pair();
    constexpr pair(const T1& x, const T2& y);
    constexpr pair(T1&& x, T2&& y);
    template<class U1, class U2> constexpr pair(U1&& x, U2&& y);

    // Copy and move constructors
    pair(const pair& p);
    pair(pair&& p);

    // Assignment operators
    pair& operator=(const pair& p);
    pair& operator=(pair&& p);
};
```

---

### **Key Features**

1. **Holds Two Values**: Can store two values of any types.
2. **Useful in Containers**: Commonly used in associative containers like `std::map` and `std::unordered_map`.
3. **Comparison Operators**: Supports comparison operators (`==`, `!=`, `<`, `>`, etc.) based on lexicographical comparison.
4. **Utility Functions**:
   - `std::make_pair`: Creates a pair without specifying types explicitly.
   - Structured bindings (C++17): Allows unpacking pairs easily.

---

### **Basic Example**

```cpp
#include <iostream>
#include <utility>
#include <string>

int main() {
    std::pair<int, std::string> p1(1, "robot");
    std::cout << "ID: " << p1.first << ", Name: " << p1.second << std::endl;

    auto p2 = std::make_pair(2, "drone");
    std::cout << "ID: " << p2.first << ", Name: " << p2.second << std::endl;

    return 0;
}
```

**Output:**
```
ID: 1, Name: robot
ID: 2, Name: drone
```

---

### **Use Case in `std::map`**

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> robotMap;
    robotMap.insert(std::make_pair(1, "xArm"));
    robotMap.insert({2, "RB-1"});
    
    for (const auto& p : robotMap) {
        std::cout << "ID: " << p.first << ", Name: " << p.second << std::endl;
    }

    return 0;
}
```

---

### **Structured Bindings (C++17)**

```cpp
#include <iostream>
#include <utility>

int main() {
    std::pair<int, std::string> p = {3, "TUGBOT"};
    auto [id, name] = p;

    std::cout << "ID: " << id << ", Name: " << name << std::endl;

    return 0;
}
```

---

### **Advanced Use Case: Returning Multiple Values**

```cpp
std::pair<int, int> getMinMax(const std::vector<int>& nums) {
    int min = *std::min_element(nums.begin(), nums.end());
    int max = *std::max_element(nums.begin(), nums.end());
    return {min, max};
}
```

---

### **Why Use `std::pair`?**

- **Convenience**: Avoids creating a custom struct for simple two-value groupings.
- **Generic Programming**: Works well with templates and STL containers.
- **Readable Code**: Makes code more expressive when returning or passing two related values.

---
