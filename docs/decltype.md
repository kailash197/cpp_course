# `decltype`
### What is it? 
- type specifier that allows you to determine the exact type of an expression at compile time.
- a compile-time operator that queries the type of an [expression](./expression.md) without evaluating it 
- stands for **declared type**.
- yields the type exactly including references and `const`/`volatile` qualifiers
- extremely useful for templates, generic programming, and when the type of an expression is required.
- Since **C++11**

### Use cases
- Generic Programming: `decltype` is particularly useful in template programming where the types of variables or function return values depend on template parameters and cannot be explicitly named.
- Variable Declaration: You can declare a variable with a type deduced from an expression, without needing to initialize it with that expression.
- Return Type Deduction: In conjunction with `auto`, it enables the deduction of complex return types for functions, especially in scenarios involving perfect forwarding or lambda expressions.

---
### Syntax
```cpp
decltype(expression)
```

### Example
```cpp
int x = 10;
const int cx = 0;
const int& rcx = x;

decltype(x) a; // 'a' will be of type 'int'
decltype(rcx) b = y; // 'b' will be of type 'const int&'
decltype(x + 5) c; // 'c' will be of type 'int' (the result of the expression)
```
--- 


### Semantics:
Value-category preservation rules: [value category](value_category.md)

| Expression form      | Value category of expression | Result of `decltype(...)` | Example result |
| -------------------- | ---------------------------- | ------------------------- | -------------- |
| `x` (just a name)    | lvalue                       | Declared type of x        | `int`          |
| `(x)`                | lvalue                       | `T&`                      | `int&`         |
| `std::move(x)`       | xvalue                       | `T&&`                     | `int&&`        |
| `x + 1`              | prvalue                      | `T`                       | `int`          |
| `func()` returning T | prvalue (usually)            | `T`                       | `std::string`  |
| `arr[i]`             | lvalue                       | `T&`                      | `int&`         |
| `*ptr`               | lvalue                       | `T&`                      | `double&`      |
| `(T&&)x` cast        | xvalue                       | `T&&`                     | `int&&`        |

Note: `(x)` → treated as an `lvalue` expression → gives reference type

---

### Use Cases

#### 1) Trailing return types & expression-based returns

```cpp
template <class A, class B>
auto add(const A& a, const B& b) -> decltype(a + b) {
    return a + b;
}
```

The return type is exactly whatever `a + b` would yield (including references, if applicable).

#### 2) `decltype(auto)` (C++14+)

`decltype(auto)` deduces using `decltype` rules from the return expression—preserving references:

```cpp
int x = 42;
int& getRef() { return x; }

auto f1() { return getRef(); }          // f1 returns int (reference is lost)
decltype(auto) f2() { return getRef(); }// f2 returns int& (reference preserved)
```

#### 3) Perfect forwarding & `std::forward`

```cpp
template <class F, class... Args>
decltype(auto) call(F&& f, Args&&... args) {
    return std::forward<F>(f)(std::forward<Args>(args)...);
}
```

Return type matches the call expression exactly (including lvalue/rvalue).

#### 4) Accessing member types via expressions

```cpp
template <class T>
auto first(T& t) -> decltype(*begin(t)) {
    return *begin(t);   // type of dereferenced iterator
}
```

#### 5) With `std::declval` (type-only contexts)

`std::declval<T>()` creates a pretend rvalue of type `T` without requiring construction—useful for SFINAE or traits:

```cpp
template <class T>
using add_result_t = decltype(std::declval<T>() + std::declval<T>());
```

***

### Subtleties & gotchas

*   **Parentheses matter**:  
    `decltype(x)` vs `decltype((x))` differ if `x` is an lvalue.
    *   `decltype(x)` → declared type
    *   `decltype((x))` → `T&`
*   **Unevaluated context**: `decltype` does **not evaluate** its operand, so you can safely use expressions that would be undefined at runtime.
*   **Functions and member access**: `decltype(&T::member)` yields a member pointer type.
*   **Arrays and functions**: `decltype(array)` gives the array type; `decltype(func)` gives the function type (not a pointer).
*   **Comparison with `auto`**:
    *   `auto` strips references and `cv` when deducing from initializers (except `auto&`, `auto&&`).
    *   `decltype(auto)` preserves reference/category like `decltype`.

***

### Practical recipes

**Preserve exact return type of an expression:**

```cpp
template <class T, class U>
decltype(auto) max_like(T&& t, U&& u) {
    return (t < u) ? std::forward<U>(u) : std::forward<T>(t);
}
```

**Get container’s value type via iterator:**

```cpp
template <class C>
using value_t = std::remove_reference_t<decltype(*std::declval<C>().begin())>;
```

**Detect if an expression is valid (SFINAE style, pre-concepts):**

```cpp
template <class T, class = decltype(std::declval<T>().size())>
constexpr bool has_size_impl(int) { return true; }

template <class>
constexpr bool has_size_impl(...) { return false; }

template <class T>
constexpr bool has_size = has_size_impl<T>(0);
```

(With C++20, prefer concepts and `requires`.)

***

### Summary

*   `decltype(expr)` returns the **exact type** of `expr` at compile time, including references and qualifiers, following value-category rules.
*   Use it for **precise type deduction**, **trailing return types**, **perfect forwarding**, and **traits/metaprogramming**.
*   Prefer `decltype(auto)` when returning expressions to **preserve references** automatically.

---
