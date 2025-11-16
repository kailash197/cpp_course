# `std::map` — A Practical, Modern C++ Guide

This page distills the key APIs and idioms for `std::map`, and fills in important details you won’t find at a glance—like complexity guarantees, iterator invalidation rules, exception safety, C++17/C++20/C++23 specifics, and common pitfalls. It’s designed to be a handy reference as well as a mini-tutorial.

> **What is it?**  
> `std::map<Key, T, Compare, Allocator>` is an **ordered associative container** that stores key–value pairs with **unique keys**, typically implemented as a **balanced binary search tree** (e.g., red–black tree). Keys are kept in **sorted order** according to `Compare` (default: `std::less<Key>`).

If you’re doing performance work in robotics or systems (like you do with ROS2), knowing when to choose `std::map` vs `std::unordered_map` or a flat container is crucial. This guide highlights those trade-offs.

***

## TL;DR Cheatsheet

*   **Ordering**: Always sorted by `Compare`. Great when you need order-dependent operations like `lower_bound`, `upper_bound`, `equal_range`.
*   **Complexity**: Most operations are **O(log N)** (find/insert/erase). Iteration is **O(N)** in sorted order.
*   **Uniqueness**: Keys are unique. Use `std::multimap` for duplicate keys.
*   **No random access**: `operator[]` is for lookup/insert by key, not by index.
*   **Invalidation**: Iterators and references remain valid across inserts; only erased elements invalidate their iterators.
*   **Alternatives**: Prefer `std::unordered_map` for average **O(1)** lookups when ordering isn’t needed; consider sorted `std::vector` (“flat map”) for small N and cache efficiency.

***

## Common Operations by Category

### Element Access

*   `at(const Key&)` – Bounds-checked access; **throws `std::out_of_range`** if key not present.
*   `operator` – Returns reference to value; **inserts a default-constructed value** if key not present.
*   `operator` – Same as above with move key.

> **Use `at()`** when you want to **avoid accidental insertion** and detect missing keys.  
> **Use `operator[]`** when you **want insertion-on-miss**.

```cpp
std::map<std::string, int> m{{"CPU",10}, {"GPU",15}};

int x = m.at("CPU");    // OK
// int y = m.at("RAM"); // throws std::out_of_range

m["RAM"] = 20;          // inserts
int z = m["UPS"];       // inserts "UPS" with value 0, then returns reference
```

***

### Iterators

*   `begin()`, `end()`, `cbegin()`, `cend()` – forward iteration in ascending key order.
*   `rbegin()`, `rend()`, `crbegin()`, `crend()` – reverse iteration.

```cpp
for (auto it = m.begin(); it != m.end(); ++it) {
    std::cout << it->first << " => " << it->second << '\n';
}

for (const auto& [k, v] : m) { /* structured bindings (C++17) */ }
```

***

### Capacity

*   `empty()`, `size()`, `max_size()`.

***

### Modifiers

*   `clear()` – removes all elements.
*   `insert(...)` – multiple overloads: single element, hints, range, initializer list.
*   `insert_range(...)` (C++23) – insert a range directly (works with ranges).
*   `insert_or_assign(key, value)` (C++17) – insert if missing; otherwise assign to existing.
*   `emplace(...)`, `emplace_hint(...)` – **construct in place**.
*   `try_emplace(key, args...)` (C++17) – construct in place **only if** key is missing; otherwise **no move/assign occurs**.
*   `erase(key)` / `erase(iterator)` / `erase(range)` – erase by key or iterator(s).
*   `swap(other)` – O(1) pointer swap.
*   **Node-based**:
    *   `extract(key)` / `extract(iterator)` (C++17) – remove a node and return a `node_handle`.
    *   `merge(other)` (C++17) – move nodes that don’t collide by key.

**Idiomatic inserts:**

```cpp
std::map<std::string, std::string> cfg;

// Avoid double work on existing keys:
cfg.insert({"baudrate", "115200"});          // does not overwrite
cfg.insert_or_assign("baudrate", "9600");    // overwrites if exists
cfg.try_emplace("port", "/dev/ttyUSB0");     // constructs only if missing

// Emplace to avoid extra copies:
cfg.emplace("mode", "read-only");
```

**Hints** help performance if you know approximate position:

```cpp
auto it = cfg.lower_bound("m");              // hint: near keys >= "m"
cfg.emplace_hint(it, "mtu", "1500");
```

***

### Lookup

*   `find(key)` – returns iterator or `end()`.
*   `count(key)` – returns 0 or 1 for `std::map`.
*   `contains(key)` (C++20) – returns `bool`.
*   `lower_bound(key)` – first element **not less than** key.
*   `upper_bound(key)` – first element **greater than** key.
*   `equal_range(key)` – pair `{lower_bound, upper_bound}`.

```cpp
if (m.contains("GPU")) { /* ... */ }

auto it = m.lower_bound("N"); // first key >= "N"
if (it != m.end()) {
    std::cout << it->first << '\n';
}
```

> **Heterogeneous lookup** (C++14 + transparent comparator):  
> If your comparator is `std::less<>` (notice the empty template argument), you can search using different but comparable key types **without constructing `Key`**:

```cpp
std::map<std::string, int, std::less<>> m;
/* ... */
bool has = m.contains("literal");            // no std::string temporary needed
auto it = m.find(std::string_view("CPU"));
```

***

### Observers

*   `key_comp()` – returns the key comparator.
*   `value_comp()` – comparator for `value_type` (pairs).

***

### Non-member Utilities

*   Relational operators (`==`, `!=`, `<`, `<=`, `>`, `>=`) compare **lexicographically** by keys then values.
*   `<=>` (C++20) – three-way comparison (spaceship operator) for lexicographical comparison.
*   `std::swap(a, b)` – specialized swap.
*   `erase_if(map, pred)` (C++20) – remove all elements satisfying `pred`.

```cpp
std::erase_if(m, { return kv.second > 25; });
```

***

## Full Example (with Output)

```cpp
#include <iostream>
#include <map>
#include <string>
#include <string_view>

void print_map(std::string_view comment, const std::map<std::string, int>& m)
{
    std::cout << comment;
    for (const auto& [key, value] : m)
        std::cout << '[' << key << "] = " << value << "; ";
    std::cout << '\n';
}

int main()
{
    std::map<std::string, int> m{{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};

    print_map("1) Initial map: ", m);

    m["CPU"] = 25; // update existing
    m["SSD"] = 30; // insert new
    print_map("2) Updated map: ", m);

    // operator[] with non-existent key inserts default value (0 for int)
    std::cout << "3) m[UPS] = " << m["UPS"] << '\n';
    print_map("4) Updated map: ", m);

    m.erase("GPU");
    print_map("5) After erase: ", m);

    std::erase_if(m, { return pair.second > 25; });
    print_map("6) After erase: ", m);
    std::cout << "7) m.size() = " << m.size() << '\n';

    m.clear();
    std::cout << std::boolalpha << "8) Map is empty: " << m.empty() << '\n';
}
```

**Output**

    1) Initial map: [CPU] = 10; [GPU] = 15; [RAM] = 20;
    2) Updated map: [CPU] = 25; [GPU] = 15; [RAM] = 20; [SSD] = 30;
    3) m[UPS] = 0
    4) Updated map: [CPU] = 25; [GPU] = 15; [RAM] = 20; [SSD] = 30; [UPS] = 0;
    5) After erase: [CPU] = 25; [RAM] = 20; [SSD] = 30; [UPS] = 0;
    6) After erase: [CPU] = 25; [RAM] = 20; [UPS] = 0;
    7) m.size() = 3
    8) Map is empty: true

***

## Complexity Guarantees

*   `insert`, `emplace`, `erase` (by key/iterator), `find`, `lower_bound`, `upper_bound`, `contains` → **O(log N)**.
*   Iteration over all elements → **O(N)** in sorted order.
*   `merge` and node operations keep **O(log N)** per node moved (amortized).

***

## Iterator and Reference Invalidation

*   **Insertion**: Does **not** invalidate iterators/references to other elements.
*   **Erasure**: Invalidates iterators/references to the **erased** elements only.
*   **`clear()`**: Invalidates all iterators.

This makes `std::map` safe for scenarios where you keep references/iterators to other elements while inserting elsewhere.

***

## Exception Safety

*   Strong exception guarantees in most modifying operations (no change on failure), provided comparison and element constructors do not throw in the middle of tree rebalancing.
*   `operator[]` may allocate and construct a default value; if construction throws, no insertion happens.

***

## Choosing Between `std::map` and Alternatives

*   **`std::unordered_map`**
    *   Pros: Average **O(1)** lookup/insert; usually faster for large N with random access patterns.
    *   Cons: No ordering; hash and equality operations needed; rehashing can invalidate iterators.
    *   Use when **ordering isn’t needed** and performance is critical.

*   **Flat map (sorted `std::vector<std::pair<Key,T>>`)**
    *   Pros: **Excellent cache locality**, very fast scans and small-N performance.
    *   Cons: Inserts/erases are **O(N)** due to shifting.
    *   Use when data set is **small/moderate**, mostly read-only, and you perform many lookups/iterations.

*   **`std::multimap`**
    *   Use when **duplicate keys** are required.

***

## Modern Tips & Patterns

### 1) Avoid Accidental Insertion

```cpp
if (auto it = m.find(key); it != m.end()) {
    use(it->second);
} else {
    // missing
}
```

Prefer `find`/`contains` or `at` over `operator[]` if insertion is not desired.

***

### 2) Use `try_emplace` to Avoid Unnecessary Moves/Copies

```cpp
std::map<std::string, std::string> m;
std::string big = compute_large_string();

m.try_emplace("result", std::move(big)); // constructs in place only if absent
// If key exists, big is NOT moved-from; no construction/assignment occurs.
```

***

### 3) Heterogeneous Lookup with Transparent Comparators

```cpp
std::map<std::string, int, std::less<>> m;
m.emplace("CPU", 10);

// Search with string literal without creating std::string
if (m.contains("CPU")) { /* ... */ }

// Or with std::string_view:
auto it = m.find(std::string_view{"CPU"});
```

***

### 4) Batch Insert with Ranges (C++23)

```cpp
#include <vector>
#include <ranges>

std::vector<std::pair<std::string, int>> v = {{"A",1},{"B",2},{"C",3}};
std::map<std::string, int> m;

m.insert_range(v); // C++23: inserts all; duplicates are ignored
```

***

### 5) Node Handles & `merge` (C++17)

Node handles let you extract and re-insert **without reallocation** of the stored node payload:

```cpp
std::map<std::string, int> a{{"A",1},{"B",2}};
std::map<std::string, int> b{{"B",20},{"C",3}};

auto nh = a.extract("A");
if (nh) {
    nh.key() = "AA";         // modify key before re-insertion
    b.insert(std::move(nh)); // O(log N)
}

b.merge(a); // moves non-colliding nodes from a -> b
```

***

## Feature-Test Macros (for Conditional Compilation)

*   Ranges construction & insertion for containers: `__cpp_lib_containers_ranges` = **202202L** (C++23)
*   `constexpr std::map`: `__cpp_lib_constexpr_map` = **202502L** (C++26 draft/working)
*   Use these with `#if defined(...)` to guard newer APIs in cross-version code.

***

## Gotchas & Best Practices

*   **`operator[]` default-inserts**: If `T` is expensive or non-default-constructible, prefer `find`/`at`/`try_emplace`.
*   **Comparator consistency**: Ensure `Compare` imposes a **strict weak ordering**; violating this leads to undefined behavior.
*   **Custom Key Types**: Provide total ordering (e.g., `operator<`) or a comparator.
*   **Performance**: For sorted traversal or range queries, `std::map` shines. For high-volume random lookups, consider `std::unordered_map`.
*   **Memory overhead**: Node-based trees allocate per element; consider flat maps when memory and locality matter.

***

## Minimal “Rosy” Example (C++17) — Parameter Registry

This is a pattern you might reuse in robotics subsystems to manage configuration keyed by parameter names:

```cpp
#include <map>
#include <string>
#include <optional>

class ParamRegistry {
public:
    bool set(std::string key, std::string value) {
        return params_.insert_or_assign(std::move(key), std::move(value)).second;
    }

    std::optional<std::string> get(std::string_view key) const {
        if (auto it = params_.find(std::string(key)); it != params_.end())
            return it->second;
        return std::nullopt;
    }

    bool has(std::string_view key) const {
        return params_.find(std::string(key)) != params_.end();
    }

    void prune_prefix(std::string_view prefix) {
        auto it = params_.lower_bound(std::string(prefix));
        while (it != params_.end() && it->first.rfind(prefix, 0) == 0) {
            it = params_.erase(it);
        }
    }

private:
    std::map<std::string, std::string, std::less<>> params_;
};
```

***

## When You Need Compile-Time or `constexpr`

*   As of C++26 (proposed), `std::map` gains broader `constexpr` support (`__cpp_lib_constexpr_map`). Until then, you cannot generally build a `constexpr std::map` at compile time; consider other techniques (e.g., `constexpr std::array` + binary search) for compile-time lookup tables.

***

## FAQ

**Q: Why is iteration sorted if I insert out of order?**  
A: The tree maintains sorted order by `Compare`, so iteration always yields sorted keys.

**Q: Why is `m["missing"]` zero?**  
A: For `T=int`, default constructor yields `0`. `operator[]` inserts a default-constructed `T` for missing keys, then returns a reference.

**Q: How do I find the next key after `k`?**  
A: Use `auto it = m.upper_bound(k);` — it points to the first key strictly greater than `k`.

**Q: Does `insert` overwrite existing values?**  
A: No. It does nothing if the key exists; use `insert_or_assign` to overwrite, or `try_emplace` to avoid overwriting and unnecessary work.

***
