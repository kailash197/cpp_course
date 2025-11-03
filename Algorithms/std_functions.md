
# `std::function`

- `std::function`, defined in the `<functional>` header
- is a **polymorphic function wrapper**.
- can store and invoke any callable target—functions, function objects, or lambda expressions.

---

## Syntax

```cpp
std::function<R(ArgTypes...)>
```

- `R`: Return type
- `ArgTypes...`: Comma-separated list of parameter types

---

## Example: Basic Usage

```cpp
#include <iostream>
#include <functional>
#include <string>

void func(int num, const std::string& str) {
    std::cout << "func(" << num << ", " << str << ")\n";
}

int main() {
    std::function<void(int, const std::string&)> f1 = func;
    f1(1, "test");
    return 0;
}
```

You can also use `auto`:

```cpp
auto f1 = func; // deduced as: void (*)(int, const std::string&)
```

---

## Using `std::function` with STL Algorithms
`std::function` types behave as function pointers, thus they can be passed to Standard Library algorithms.

```cpp
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

bool isEven(int num) {
    return num % 2 == 0;
}

int main() {
    std::vector<int> vec{1,2,3,4,5,6,7,8,9};
    std::function<bool(int)> fcn = isEven;

    auto result = std::find_if(vec.cbegin(), vec.cend(), fcn);
    if (result != vec.cend()) {
        std::cout << "First even number: " << *result << "\n";
    } else {
        std::cout << "No even number found.\n";
    }

    return 0;
}
```

---

## Callback Example with `std::function`

```cpp
#include <vector>
#include <functional>
#include <iostream>

void process(const std::vector<int>& vec, std::function<void(int)> f) {
    for (auto& i : vec) {
        f(i);
    }
}

void print(int num) {
    std::cout << num << " ";
}

int main() {
    std::vector<int> vec{0,1,2,3,4,5,6,7,8,9};

    process(vec, print);
    std::cout << "\n";

    int sum = 0;
    process(vec, [&sum](int num) { sum += num; });
    std::cout << "sum = " << sum << "\n";

    return 0;
}
/*
0 1 2 3 4 5 6 7 8 9 
sum = 45
*/
```

## Alternative: Function Template

```cpp
template <typename F>
void processTemplate(const std::vector<int>& vec, F f) {
    for (auto& i : vec) {
        f(i);
    }
}
```

This template version can accept:
- Raw function pointers
- Lambdas
- Functors

---

## Summary

- `std::function` is ideal for storing callbacks or passing callables to functions.
- It provides type-erased flexibility at the cost of slight overhead.
- Prefer templates when performance is critical and type flexibility is not needed.

---
