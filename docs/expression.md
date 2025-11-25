### Expression
An expression is a sequence of operators and operands that specifies a computation. Its evaluation typically produces a result value, designates an object or function, or generates side effects (like modifying a variable's value).  
Expressions are fundamental building blocks in C++ code, combining elements like:  
- Literals: Constant values such as `10`, `3.14`, `'a'`, `"hello"`.  
- Variables: Named storage locations that hold values, e.g., `x`, `myVariable`.  
- Operators: Symbols that perform operations on operands, like `+`, `-`, `*`, `/`, `=`, `==`, `&&`, `||`.  
- Function Calls: Invocations of functions that may return a value, e.g., `std::cout << "Hello", calculateSum(a, b)`.
- Examples of C++ expressions:
    ```C++
    // Literal expression, evaluates to the value 5
    5

    // Variable expression, evaluates to the value stored in 'x'
    x

    // Arithmetic expression, evaluates to the sum of x and 10
    x + 10

    // Assignment expression, assigns the value 20 to 'y' and evaluates to 20
    y = 20

    // Function call expression, calls the 'printMessage' function
    printMessage("Hello, World!");

    // More complex expression combining multiple elements
    (a * b) + calculateTax(price)
    ```
Every C++ expression possesses two key properties: 
- a type (e.g., int, double, bool) and 
- a value category (e.g., lvalue, prvalue),  

which determine how it can be used within the program.