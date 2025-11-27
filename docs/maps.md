# `std::map`
- defined inside `<map>` header
- stores key-value pairs with **unique keys**
- insertion, lookup and deletion are key-based and logarithmic time
- keeps elements sorted based on keys
- when the elements are enumerated the elements, they come out in the ordering imposed by the type's `operator<` or a user-defined comparator
- usually implemented as some form of balanced tree, such as a red-black tree, however, the tree structure is not exposed to the client

## Features
*   **Complexity**: 
    - Most operations are **O(log N)** , `insert`, `emplace`, `erase` (by key/iterator), `find`, `lower_bound`, `upper_bound`, `contains` → **O(log N)**.
    - Iteration is **O(N)** in sorted order.
    - 
*   **Uniqueness**: Keys are unique. Use `std::multimap` for duplicate keys.
*   **No random access**: `operator[]` is for lookup/insert by key, not by index.
*   **Invalidation**: Iterators and references remain valid across inserts; only erased elements invalidate their iterators.
*   **Alternatives**: Prefer `std::unordered_map` for average **O(1)** lookups when ordering isn't needed; consider sorted `std::vector` (“flat map”) for small N and cache efficiency.

## Construction
- The `map` class template takes four types: the key type, the value type, the comparison type, and the allocator type
- supports uniform initialization:
    ```cpp
    map<string, int> m = {
        { "Marc G.", 123 },
        { "Warren B.", 456 },
        { "Peter V.W.", 789 }
    };
    ```

## Element Access

*   `at(const Key&)` – Bounds-checked access; **throws `std::out_of_range`** if key not present.
*   `operator[]` – Returns reference to value; **inserts a default-constructed value** if key not present.
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

## Insertion
- requires the key and the value to insert an element to `map`, the position to store the element will be determined by `map`'s internal implementation

#### `insert()` method
- need to provide key and value as `std::pair` object or an initializer list
- Adds a key-value pair **only if the key doesn’t already exist**.
- Returns: `std::pair<map<T1, T2>::iterator, bool>`  
    - `iterator`: points to the element (new or existing).  
    - `bool`: `true` if insertion succeeded, `false` if key already existed.

- Example:
    ```cpp
    std::map<std::string, int> points;
    auto result = points.insert({"Joe", 35}); // does not overwrite
    if (result.second) std::cout<< "Insertion success" << std::endl;
    else std::cout << "Insertion failed" << std::endl;
    print(points);

    //C++17: initializer for `if`
    if(auto [itr, success] = points.insert({"Mark", 25}); success) std::cout<< "Insertion success" << std::endl;
    print(points);
    ```
- Output:
    ```
    Insertion success
    { Joe: 35 }
    Insertion success
    { Joe: 35, Mark: 25 }
    ```



#### `insert_or_assign()` method
- requires key and value as two seperate parameters
- Inserts if key doesn’t exist; **overwrites** if key exists
- Returns same type as `insert()`.

- Example:
    ```cpp
    // insert or assign
    auto result1 = points.insert_or_assign("Joe", 45); // overwrites if exists
    if (result1.second) std::cout << "Insertion success" <<std::endl;
    else std::cout << "Value Overwritten" <<std::endl;
    print(points);
    ```
- Output:
    ```
    Value Overwritten
    { Joe: 45, Mark: 25 }
    ```

---

#### `operator[]`
- insert elements into a `map` through the overloaded `operator[]`
- Always succeeds.
- **Creates** a new element if key doesn’t exist.
- **Replaces** value if key exists.
- Requires default constructor for value type.
- **Not const**, so can't be used on `const map`.

- Example:
    ```cpp
    // using operator[]
    points["Harry"] = 34;
    print(points);
    points["Mark"] = 55;
    std::cout << points["Mark"] <<std::endl;
    print(points);
    ```
- Output:
    ```
    { Harry: 34, Joe: 45, Mark: 25 }
    55
    { Harry: 34, Joe: 45, Mark: 55 }
    ```
- Caveat:
    - always creates a new value object even if it doesn't need to use it.
    - so `operator[]` is not `const`, which means the following code won't compile even though it seems to access only
    - use `find()` instead
    ```cpp
    void func(const map<int, int>& m) {
    cout << m[1] << endl; // Error
    }
    ```

---

#### `emplace()`
- **Purpose**: Constructs an object **in-place** directly within the container, avoiding unnecessary copies or moves.
- **Efficiency**: Often more efficient than `insert()` because it constructs the object directly using the provided arguments.
- **Usage**: Available in containers like `std::vector`, `std::list`, `std::map`, `std::set`, etc.
- Example with `std::map`:
    ```cpp
    std::map<int, std::string> myMap;
    myMap.emplace(1, "Khadka"); // Constructs pair<int, string> in-place
    ```
- If key exists:
    - `emplace()` does nothing if the key already exists, does not overwrite the existing value.
    - but still evaluates the constructor arguments you pass (unlike `try_emplace()` which avoids this).
    - returns an iterator to the existing element and a bool indicating whether insertion happened.
    - Example:
        ```cpp
        #include <iostream>
        #include <map>

        class Data {
        public:
            Data(int x) {
                std::cout << "Data constructor called with " << x << "\n";
            }
        };

        int main() {
            std::map<int, Data> myMap;

            // First emplace: key doesn't exist
            auto [it1, inserted1] = myMap.emplace(1, 10);
            std::cout << "Inserted1: " << inserted1 << "\n";

            // Second emplace: key exists, but constructor still called
            auto [it2, inserted2] = myMap.emplace(1, 99);
            std::cout << "Inserted2: " << inserted2 << "\n";

            return 0;
        }
        ```
    - Output:
        ```
        Data constructor called with 10
        Inserted1: 1
        Data constructor called with 99
        Inserted2: 0
        ```

---

#### `emplace_hint()`
- **Purpose**: Similar to `emplace()`, but used with **ordered associative containers** like `std::map` and `std::set`.
- **Hint**: Accepts an iterator as a hint to where the element should be inserted, potentially improving performance.
- **Efficiency**: Can be faster than `emplace()` if the hint is correct.

- Example with `std::map`:
    ```cpp
    std::map<int, std::string> myMap;
    auto it = myMap.begin();
    myMap.emplace_hint(it, 2, "ROS2"); // Uses hint to optimize insertion
    ```

---


#### `try_emplace()` (C++17)
- Inserts in-place **only if key doesn’t exist**.
- Does **nothing** if key exists.
- Example:
    ```cpp
    #include <iostream>
    #include <map>

    class Data {
    public:
        Data(int x) {
            std::cout << "Data constructor called with " << x << "\n";
        }
    };

    int main() {
        std::map<int, Data> myMap;

        // First emplace: key doesn't exist
        auto [it1, inserted1] = myMap.emplace(1, 10);
        std::cout << "Inserted1: " << inserted1 << "\n";

        // Second emplace: key exists, but constructor still called
        auto [it2, inserted2] = myMap.emplace(1, 99);
        std::cout << "Inserted2: " << inserted2 << "\n";


        // First try_emplace: key doesn't exist
        auto [it3, inserted3] = myMap.try_emplace(2, 10);
        std::cout << "Inserted1: " << inserted3 << "\n";

        // Second try_emplace: key exists, constructor NOT called
        auto [it4, inserted4] = myMap.try_emplace(2, 99);
        std::cout << "Inserted2: " << inserted4 << "\n";


        return 0;
    }
    ```
- Output:
    ```
    Data constructor called with 10
    Inserted1: 1
    Data constructor called with 99
    Inserted2: 0
    Data constructor called with 10
    Inserted1: 1
    Inserted2: 0
    ```

---




## Iterators
*   `begin()`, `end()`, `cbegin()`, `cend()` – forward iteration in ascending key order.
*   `rbegin()`, `rend()`, `crbegin()`, `crend()` – reverse iteration.
- refer to **key-value pairs**, 'std::pair` object.
- Bidirectional.
- Access value via `iter->second` or `(*iter).second`.

```cpp
for (auto it = m.begin(); it != m.end(); ++it) {
    std::cout << it->first << " => " << it->second << '\n';
}

for (const auto& [k, v] : m) { /* structured bindings (C++17) */ }
```

### Examples:
    ```cpp
    #include <iostream>
    #include <map>

    class Data {
    private:
        int data;
    public:
        Data(int x): data(x) {
            std::cout << "Data constructor called with " << x << "\n";
        }
        int getData() const {
            return data;
        }
    };

    int main() {
        std::map<int, Data> myMap;

        // First emplace: key doesn't exist
        auto [it1, inserted1] = myMap.emplace(1, 10);
        auto [it3, inserted3] = myMap.try_emplace(2, 10);
        auto [it4, inserted4] = myMap.try_emplace(3, 99);

        //using iterators
        for (auto itr = myMap.cbegin(); itr != myMap.cend(); ++itr){
            std::cout << "Key: " << itr->first <<", Value: " << itr->second.getData() << std::endl;
        }

        //using range based for loop
        for (const auto& pair: myMap){
            std::cout << "Key: " << pair.first <<", Value: " << pair.second.getData() << std::endl;
        }

        //using range based for loop with structured binding C++17
        for (const auto& [first, second] : myMap ){
            std::cout << "Key: " << first <<", Value: " << second.getData() << std::endl;
        }


        return 0;
    }
    ```
- Output:
    ```
    Data constructor called with 10
    Data constructor called with 10
    Data constructor called with 99
    Key: 1, Value: 10
    Key: 2, Value: 10
    Key: 3, Value: 99
    Key: 1, Value: 10
    Key: 2, Value: 10
    Key: 3, Value: 99
    Key: 1, Value: 10
    Key: 2, Value: 10
    Key: 3, Value: 99
    ```
- <u>**Warning**</u>: You can modify element values through non-const iterators, but the compiler will generate an error if you try to modify the key of an element, even through a non-const iterator, because it would destroy the sorted order of the elements in the map.

---

### Iterator and Reference Invalidation

*   **Insertion**: Does **not** invalidate iterators/references to other elements.
*   **Erasure**: Invalidates iterators/references to the **erased** elements only.
*   **`clear()`**: Invalidates all iterators.

This makes `std::map` safe for scenarios where you keep references/iterators to other elements while inserting elsewhere.

***

## Lookup Methods
- provides logarithmic lookup of elements based on a supplied key.
- `operaotr[]`
    - use `operator[]` to lookup only if you know the key exists, else it will insert new element with the key.
    - use `find()` method if not sure 
    - inserts default constructed object and returns the iterator
    - then calls parameterized constructor to update object data.
    - returns a reference to the element that can be used and modify directly, without worrying about pulling the value out of a pair object
    - Example:
        ```cpp
        #include <iostream>
        #include <map>

        class Data {
        private:
            int data;
        public:
            Data(): data(0){
                std::cout << "DC called" <<std::endl;
            }
            Data(int x) : data(x) {
                std::cout << "PC called" <<std::endl;
            }
            int getData() const {
                return data;
            }
            void setData(int x) {
                data = x;
            }
        };

        int main() {
            std::map<int, Data> myMap;

            // Insert elements using operator[]
            myMap[1] = Data(10);
            myMap[2] = Data(20);
            myMap[3] = Data(90);

            // Lookup using operator[]
            std::cout << "Key: 1, Value: " << myMap[1].getData() << "\n";
            std::cout << "Key: 2, Value: " << myMap[2].getData() << "\n";

            // Demonstrate that operator[] creates a default object if key doesn't exist
            std::cout << "Key: 4 (not inserted yet), Value: " << myMap[4].getData() << "\n";

            // Print all elements using structured binding (C++17)
            std::cout << "\n--- Map Contents ---\n";
            for (const auto& [key, value] : myMap) {
                std::cout << "Key: " << key << ", Value: " << value.getData() << "\n";
            }

            return 0;
        }
        ```
    - Output:
        ```
        PC called
        DC called
        PC called
        DC called
        PC called
        DC called
        Key: 1, Value: 10
        Key: 2, Value: 20
        Key: 4 (not inserted yet), Value: DC called
        0

        --- Map Contents ---
        Key: 1, Value: 10
        Key: 2, Value: 20
        Key: 3, Value: 90
        Key: 4, Value: 0
        ```

- `find(key)`: 
    - Returns iterator to element or `end()` if not found.
    - Example:
        ```cpp
        auto it = dataMap.find(1);
        if (it != dataMap.end()) it->second.setValue(100);
        ```

- `count(key)`: Returns `0` or `1` (maps don’t allow duplicate keys).


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
---



---

## Non-member Utilities

*   Relational operators (`==`, `!=`, `<`, `<=`, `>`, `>=`) compare **lexicographically** by keys then values.
*   `<=>` (C++20) – three-way comparison (spaceship operator) for lexicographical comparison.
*   `std::swap(a, b)` – specialized swap.
*   `swap(other)` – O(1) pointer swap.
*   `erase_if(map, pred)` (C++20) – remove all elements satisfying `pred`.
*   `erase(key)` / `erase(iterator)` / `erase(range)` – erase by key or iterator(s).
*   **Node-based**:
    *   `extract(key)` / `extract(iterator)` (C++17) – remove a node and return a `node_handle`.
    *   `merge(other)` (C++17) – move nodes that don’t collide by key.
```cpp
std::erase_if(m, { return kv.second > 25; });
```

## **8. `erase()`**
- Removes by:
  - **Iterator**
  - **Key**
  - **Range of iterators**

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