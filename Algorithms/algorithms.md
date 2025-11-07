# Standard Library Algorithms

## Algorithms
- Algorithms work on iterators instread of the containers themselves, so not tied to specific containers.
- All standard library algorithms are implemented as function templates, parameters are generally iterator types.
- Templatized functions generally deduce the types from function arguments so can be called normally.
- Arguments are usually iterator ranges (half-open).
- Different algorithms have different requirement for iterators.
    #### Example
    - `copy_backward()` requires bidirectional iterator.
    - `stable_sort()` requires random access iterator.  
    As `forward_list` supports only forward iterator hence `copy_backward()` and `stable_sort()` can't be applied to it.
- namspace: std
- header `<algorithm>`, few defined in `<numeric>`

---

### `find()`
- find specific element in an iterator range in any container type, iterator range can be any subset of entire range
-  returns an iterator referring to the element found, or the end iterator specified in the functional call if not found, not the end iterator of the underlying container.
- Example:
    ```cpp
    #include <algorithm>
    #include <vector>
    #include <iostream>

    using namespace std;

    int main() {
        int num;
        vector<int> myVector {23, 34, 45, 56, 78, 89};

        while(true){
            cout << "Enter number to search, 0 to exit: ";
            cin >> num;
            if (num == 0) break;

            auto end = myVector.cend();
            auto itr = find(myVector.cbegin(), end, num);
            // change iterator range to search in subrange.

            if (itr != end){
                cout << "Found the number: " << *itr <<endl;
            } else {
                cout << "Number not found."<<endl;
            }
        }
    }
    ```
    `C++17` provides initializers for `if statements`, the call to `find()` and checking the result can be done with one statement as follows:
    ```cpp
        if (auto itr = find(myVector.cbegin(), end, num); itr != end){
            cout << "Found the number: " << *itr <<endl;
        } else {
            cout << "Number not found."<<endl;
        }
    ```


#### **Lookup Performance Across C++17 Containers**

| Container              | `.find()` Available | `.find()` Complexity     | `std::find()` Complexity | Notes |
|------------------------|---------------------|---------------------------|---------------------------|-------|
| `std::vector`          | No               | —                         | $O(n)$                | Linear scan only |
| `std::list`            | No               | —                         | $O(n)$                | Doubly-linked list |
| `std::deque`           | No               | —                         | $O(n)$                | Random access, but no fast lookup |
| `std::array`           | No               | —                         | $O(n)$                | Fixed-size array |
| `std::forward_list`    | No               | —                         | $O(n)$                | Singly-linked list |
| `std::set`             | Yes             | $O(log n)$           | $O(n)$                | Tree-based |
| `std::map`             | Yes             | $O(log n)$           | $O(n)$                | Tree-based |
| `std::multiset`        | Yes             | $O(log n)$           | $O(n)$                | Tree-based, allows duplicates |
| `std::multimap`        | Yes             | $O(log n)$           | $O(n)$                | Tree-based, allows duplicates |
| `std::unordered_set`   | Yes             |$O(1)$ average        | $O(n)$                | Hash-based |
| `std::unordered_map`   | Yes             |$O(1)$ average        | $O(n)$                | Hash-based |
| `std::unordered_multiset` | Yes          |$O(1)$ average        | $O(n)$                | Hash-based, allows duplicates |
| `std::unordered_multimap` | Yes          |$O(1)$ average        | $O(n)$                | Hash-based, allows duplicates |

---

### `find_if()`
- similar to `find()`, accepts a predicate function callback instead of a simple element to match, calls predicate on each element in the range until the predicate returns `true`
- A predicate returns `true` or `false`
- if predicate returns `true`, `find_if()` returns iterator referring to that element.
- Example:
    ```cpp
    #include <algorithm>
    #include <vector>
    #include <iostream>

    using namespace std;

    bool even_number(int num){
        return num % 2 == 0;
    }

    int main() {
        int num;
        vector<int> myVector {23, 33, 45, 56, 78, 89};
        cout << "Searching for even number " <<endl;

        auto end = myVector.cend();

        // C++17 style
        // pass pointer to function, even_number
        if (auto itr = find_if(myVector.cbegin(), end, even_number); itr != end){
            cout << "Found the number: " << *itr <<endl;
        } else {
            cout << "Number not found."<<endl;
        }
    }
    /*
    Searching for even number 
    Found the number: 56
    */
    ```
    Using lambda expressions:
    ```cpp
        auto end = myVector.cend();
        if (auto itr = find_if(myVector.cbegin(), end, [](int num){return num % 2 == 0;}); itr != end){
            cout << "Found the number: " << *itr <<endl;
        } else {
            cout << "Number not found."<<endl;
        }
    ```
---

### `accumulate()`
- Defined in `<numeric>`, not `<algorithm>`
- Combines elements in a range using a binary operation
- Default operation is addition
- Can be customized with a callback or lambda to make custom operations concise and readable
- `std::accumulate(begin, end, init)` → sums elements
- `std::accumulate(begin, end, init, binary_op)` → custom reduction
- Initial value must match the operation’s identity (e.g., `0` for sum, `1` for product)

- Example 1: Arithmetic Mean (Sum)
    ```cpp
    #include <vector>
    #include <numeric> // for accumulate

    double arithmeticMean(const std::vector<int>& nums) {
        double sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        return sum / nums.size();
    }
    ```
    - `0` is the identity for addition
    - Uses default addition internally


- Example 2: Geometric Mean (Product)
    ```cpp
    #include <vector>
    #include <numeric>
    #include <cmath> // for pow

    int product(int a, int b) {
        return a * b;
    }

    double geometricMean(const std::vector<int>& nums) {
        double mult = std::accumulate(nums.cbegin(), nums.cend(), 1, product);
        return std::pow(mult, 1.0 / nums.size());
    }
    ```

    - `1` is the identity for multiplication
    - Uses a named function as the binary operation

- Example 3: Geometric Mean with Lambda
    ```cpp
    double geometricMeanLambda(const std::vector<int>& nums) {
        double mult = std::accumulate(nums.cbegin(), nums.cend(), 1,
            [](int a, int b) { return a * b; });
        return std::pow(mult, 1.0 / nums.size());
    }
    ```
    - Cleaner and more expressive
    - No need to define a separate `product()` function
- Example 4: Sum of Squares and Product of squares
    ```cpp
    #include <iostream>
    #include <numeric> // for accumulate
    #include <vector>
    #include <cmath>

    using namespace std;

    double arithmeticMean(const vector<int>& v1){
        return std::accumulate(v1.cbegin(), v1.cend(), 0) / v1.size();
    }

    double geometricMean(const vector<int>& v){
        int product = std::accumulate(v.cbegin(), v.cend(), 1, [](int a, int b){return a*b;});
        return std::pow(product, 1.0 / v.size());
    }

    int main(){
        vector<int> v1 {1, 2, 3, 4, 5};
        cout << "The average of elements: "<<arithmeticMean(v1)<<endl;
        cout << "The geometric mean of elements: "<<geometricMean(v1)<<endl;

        cout << "sum of squares: " << std::accumulate(v1.cbegin(), v1.cend(), 0, [](int a, int b){return a +  b * b;}) << endl;
        cout << "product of squares: " << std::accumulate(v1.cbegin(), v1.cend(), 1, [](int a, int b){return a * b * b;}) << endl;

        return 0;
    }
    /*
    The average of elements: 3
    The geometric mean of elements: 2.60517
    sum of squares: 55
    product of squares: 14400
    */
    ```
---

## Move Semantics with Algorithms
- Similar to Standard Library containers, Standard Library algorithms are also optimized to use move semantics at appropriate times. 
- can greatly speed up certain algorithms, for example, `remove()`
- highly recommended that you implement move semantics in your custom element classes that you want to store in containers. 
- Move semantics can be added to any class by implementing a move constructor and a move assignment operator. Both should be marked as `noexcept`, because they should not throw exceptions.
