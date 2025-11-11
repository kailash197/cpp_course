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

#### Iterators
- Refer to **key-value pairs**, 'std::pair` object.
- Bidirectional.
- Access value via `iter->second` or `(*iter).second`.

- Examples:
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

