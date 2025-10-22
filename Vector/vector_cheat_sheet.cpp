// 🔥 C++ VECTOR CHEAT SHEET 🔥

// ✅ Declaration
// std::vector<int> v;               // Empty vector, zero elements
// std::vector<int> v(5);            // 5 default-initialized elements (0s)
// std::vector<int> v(10, 100);      // Creates vector of 10 ints with value 100
// std::vector<int> v = {1, 2, 3};   // Initializer list
// std::vector<int> v{1, 2, 3};      // Initializer list
// std::vector<int> v({1, 2, 3});   // Initializer list
// auto elementVector = make_unique<vector<Element>>(10); //heap

// 🔹 MODIFIERS
// v.push_back(val);       // Add at end
// v.pop_back();           // Remove last element
// v.insert(it, val);      // Insert before iterator position
// v.erase(it);            // Erase element at iterator
// v.clear();              // Remove all elements
// v.resize(n);            // Resize vector to n elements
// v.emplace_back(val);    // In-place push_back (faster for objects)

// 🔹 ACCESS
// v.at(i);                // Safe element access // throws exception std::out_of_range
// v[i];                   // Fast access (no check)
// v.front();              // R/W reference to first element, undefined in empty container
// v.back();               // R/W reference to last element, undefined in empty container
// v.data();               // Pointer to underlying array

// 🔹 CAPACITY
// v.size();               // Current number of elements
// v.capacity();           // Allocated storage size
// v.empty();              // Check if empty
// v.reserve(n);           // Pre-allocate storage
// v.shrink_to_fit();      // Reduce capacity to match size

// 🔹 ITERATORS
// v.begin();              // Iterator to first
// v.end();                // Iterator to past last
// v.rbegin();             // Reverse iterator to last
// v.rend();               // Reverse iterator before first

// 🔹 LOOP EXAMPLES
// for (int x : v) {}                     // Range-based loop
// for (auto it = v.begin(); it != v.end(); ++it) {}  // Iterator loop
// std::for_each(v.begin(), v.end(), func);           // Algo-style loop
