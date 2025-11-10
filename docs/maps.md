# `std::map`
- defined inside `<map>` header
- stores key-value pairs
- insertion, lookup and deletion are key-based and logarithmic time
- keeps elements sorted based on keys
- when the elements are enumerated the elements, they come out in the ordering imposed by the type's `operator<` or a user-defined comparator
- usually implemented as some form of balanced tree, such as a red-black tree, however, the tree structure is not exposed to the client
- keys should be unique

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
    auto result = points.insert({"Joe", 35});
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
- Inserts if key doesn’t exist; **overwrites** if it does.
- Returns same type as `insert()`.

- Example:
    ```cpp
    // insert or assign
    auto result1 = points.insert_or_assign("Joe", 45);
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

### **4. `emplace()`, `emplace_hint()`**
- Constructs elements **in-place**.
- More efficient than `insert()` in some cases.

### **5. `try_emplace()` (C++17)**
- Inserts in-place **only if key doesn’t exist**.
- Does **nothing** if key exists.

---

### **6. Iterators**
- Refer to **key-value pairs**.
- Bidirectional.
- Access value via `iter->second` or `(*iter).second`.

**Examples:**
```cpp
for (auto iter = dataMap.cbegin(); iter != dataMap.cend(); ++iter)
    cout << iter->second.getValue();

for (const auto& [key, data] : dataMap)
    cout << data.getValue();
```

---

### **Lookup Methods**
- **`find(key)`**: Returns iterator to element or `end()` if not found.
```cpp
auto it = dataMap.find(1);
if (it != dataMap.end()) it->second.setValue(100);
```

- **`count(key)`**: Returns `0` or `1` (maps don’t allow duplicate keys).

---

### **8. `erase()`**
- Removes by:
  - **Iterator**
  - **Key**
  - **Range of iterators**

---

