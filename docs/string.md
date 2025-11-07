
# Strings in C++

C++ provides a robust and flexible string class through the `<string>` header. While C-style character arrays (`char[]`) are still available, the C++ `std::string` class is superior in nearly every aspect.

---

## `std::string`

- Defined in `<string>`, `std::string` is a type alias for `std::basic_string<char>`.
- Offers dynamic memory management, bounds checking, and intuitive assignment and comparison operations.
- Supports rich string manipulation:
  - Concatenation
  - Substring extraction
  - Character and substring replacement

You can use `std::string` as if it were a regular class, without needing to understand its template internals.

```cpp
#include <string>
#include <iostream>

int main() {
    std::string greeting = "Hello";
    greeting += ", world!";
    std::cout << greeting << std::endl;
}
```

---

## `std::string_view`

- Introduced in C++17 via `<string_view>`.
- A **read-only view** of a string—does not own or copy the data.
- Can be used as a lightweight alternative to `const std::string&`.

```cpp
#include <string_view>
#include <iostream>

void print(std::string_view sv) {
    std::cout << sv << std::endl;
}

int main() {
    std::string name = "Kailash";
    print(name); // No copy made
}
```

Use `string_view` when:
- You want to avoid unnecessary copies.
- You’re passing string-like data to functions.
- You’re working with substrings or slices.

---

## Unicode and Localization

C++ supports internationalization through:
- **Unicode types**: `char16_t`, `char32_t`, `wchar_t`
- **Localization utilities**: Provided via `<locale>`

Locales allow formatting of:
- Numbers
- Dates
- Currency
- Text according to regional rules

```cpp
#include <locale>
#include <iostream>

int main() {
    std::locale loc("en_US.UTF-8");
    std::cout.imbue(loc);
    std::cout << 1234567.89 << std::endl;
}
```

---

## Summary

| Feature            | `std::string`               | `std::string_view`           |
|--------------------|-----------------------------|------------------------------|
| Ownership          | Owns data                   | Non-owning view              |
| Copying            | Copies on assignment        | No copy                      |
| Mutability         | Mutable                     | Immutable                    |
| Use case           | General-purpose string      | Lightweight read-only access |
| Header             | `<string>`                  | `<string_view>`              |

---
