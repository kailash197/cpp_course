## Literal and Variable Data Types in C++
In C++, variables and literals are fundamental concepts used to store and represent data.

### Literals
- A literal is a fixed value that appears directly in the source code of a program.
- Literals represent constant data that cannot be modified during program execution.
- Literals can be of different types, such as integer literals, floating-point literals, character literals, string literals, boolean literals, and more.
- They are used to initialize variables or as operands in expressions.
- Example

```cpp
#include <iostream>

int main() {
    int num = 10; // Integer literal
    double pi = 3.14159; // Floating-point literal
    char ch = 'A'; // Character literal
    std::string message = "Hello, world!"; // String literal
    bool flag = true; // Boolean literal

    std::cout << "Number: " << num << std::endl;
    std::cout << "Pi: " << pi << std::endl;
    std::cout << "Character: " << ch << std::endl;
    std::cout << "Message: " << message << std::endl;
    std::cout << "Flag: " << flag << std::endl;

    return 0;
}
```

### Variables
- A variable is a named storage location in computer memory; represents a value that can change during program execution.
- Variables must be declared with a specific data type before they can be used.
- The data type determines the kind of data the variable can hold (e.g., integer, floating-point number, character, etc.).
- Variables can be assigned values, and these values can be changed throughout the program's execution.
- Identifiers or variable names should be alphanumeric
- Example of variable declaration and assignment in C++:
    
```cpp
#include <iostream>

int main() {
    int age; // Variable declaration
    age = 25; // Variable assignment

    std::cout << "Age: " << age << std::endl; // Output: Age: 25

    return 0;
}

```

#### Dynamic Declaration of Variables
If a variable is declared in main function, it is created in stack of main function and scope is till the main function is completed. If possible, a variable can be declared inside `if` block it is again created in the stack memory of main function but as soon as the `if` block goes out of scope, the variable is deleted and memory is freed.
    
```cpp
#include <iostream>

using namespace std;

int main() {    
    int a=5;
    bool condition = true;
    if (condition) {
        cout<< "A: "<<a<<endl;
    }
    cout<< "A: "<<a<<endl;

    if (condition) {
        int b = 2;
        cout<< "B: "<<b<<endl;
    }
    // cout<< "A: "<<b<<endl; Error: identifier b unidentified.
    return 0;
}
```

**C++17:** Similar to `for` loop, dynamic declaration is supported in `if` condition, so that scope of the variable is same as `if` block.
```cpp
for (int i=0; i< 10; i++){
	cout<< i<< endl;
}

if (int j = 5; j < i) {
	cout << j << endl;
}
//	cout << j << endl; Error: undefined variable j
```
### Global variables & Local variables

In C++, **global** and **local** variables refer to the scope and lifetime of variables:

### Global Variables

- **Definition**: Variables declared outside of any function or class, typically at the top of a file.
- **Scope**: Accessible from any function or file that declares or includes the variable.
- **Lifetime**: Exist for the duration of the program's execution.
- **Example**:
    
    ```cpp
    int globalVar = 10; // Global variable
    
    void printGlobal() {
        std::cout << globalVar << std::endl; // Accessible here
    }
    
    int main() {
        printGlobal();
        return 0;
    }
    
    ```
    

### Local Variables

- **Definition**: Variables declared inside a function or a block (e.g., within curly braces `{}`).
- **Scope**: Accessible only within the function or block where they are declared.
- **Lifetime**: Exist only while the function or block is executing; they are destroyed when the function or block exits.
- **Example**:
    
    ```cpp
    void myFunction() {
        int localVar = 5; // Local variable
        std::cout << localVar << std::endl; // Accessible here
    }
    
    int main() {
        myFunction();
        // std::cout << localVar << std::endl; // Error: localVar is not accessible here
        return 0;
    }
    
    ```
    

### Summary

- **Global Variables**:
    - Declared outside functions.
    - Accessible throughout the program.
    - Persist for the entire runtime of the program.
    - accessible by any function
- **Local Variables**:
    - Declared inside functions or blocks.
    - Accessible only within their function or block.
    - Created and destroyed within the scope of their function or block.

### Static Variables

- global in scope but visibility is limited to certain function, class, or file.
- global vars are both global in scope and accessible to all functions, and classes.

In C++, a **static variable** is a variable that retains its value across multiple function calls and is shared across all instances of a class or function. Static variables have different behaviors depending on where they are declared: within a function, within a class, or at the global level.

### Types of Static Variables:

1. **Static Local Variables (Within a Function)**:
    - **Definition**: A static local variable is declared inside a function but retains its value between function calls.
    - **Scope**: Limited to the function in which it is declared.
    - **Lifetime**: Exists for the entire duration of the program, but only accessible within the function.
    - **Usage**: Useful when you need to maintain state between function calls without using global variables.
    - **Example**:
        
        ```cpp
        void func() {
            static int counter = 0; // Static local variable
            counter++;
            std::cout << "Counter: " << counter << std::endl;
        }
        
        int main() {
            func(); // Output: Counter: 1
            func(); // Output: Counter: 2
            func(); // Output: Counter: 3
            return 0;
        }
        
        ```
        
2. **Static Member Variables (Within a Class)**:
    - **Definition**: A static member variable is shared across all instances of a class. It is not tied to any specific object instance.
    - **Scope**: Visible to all members of the class and can be accessed using the class name.
    - **Lifetime**: Exists for the entire duration of the program.
    - **Usage**: Useful for storing information that should be shared among all instances of a class (e.g., a counter tracking the number of objects created).
    - **Example**:
        
        ```cpp
        class MyClass {
        public:
            static int objectCount; // Static member variable
        
            MyClass() {
                objectCount++;
            }
        };
        
        int MyClass::objectCount = 0; // Definition of the static variable
        
        int main() {
            MyClass obj1;
            MyClass obj2;
            std::cout << "Number of objects: " << MyClass::objectCount << std::endl; // Output: 2
            return 0;
        }
        
        ```
        
3. **Static Global Variables (File Scope)**:
    - **Definition**: A static global variable is a variable declared at the global level, but it is only accessible within the file in which it is declared.
    - **Scope**: Restricted to the file in which it is defined, not accessible from other files.
    - **Lifetime**: Exists for the entire duration of the program.
    - **Usage**: Useful for encapsulating global variables within a single file to prevent name conflicts.
    - **Example**:
        
        ```cpp
        static int globalVar = 100; // Static global variable
        
        void func() {
            std::cout << globalVar << std::endl; // Accessible within the same file
        }
        
        int main() {
            func(); // Output: 100
            return 0;
        }
        
        ```
        

### Summary:

- **Static Local Variables**: Retain their value between function calls, but only accessible within the function.
- **Static Member Variables**: Shared across all instances of a class, accessible via the class name.
- **Static Global Variables**: Accessible only within the file they are declared in, preventing external access.

Static variables are powerful tools in C++ for managing state, ensuring memory efficiency, and controlling variable accessibility across different parts of a program.

### Scope of a Variable

In C++, the scope of a variable determines where it can be accessed within a program. Here are the main scopes for variables:

### 1. **Block Scope (Local Scope)**:

- **Definition**: Variables declared inside a block of code, typically within `{}` braces such as inside functions, loops, or conditional statements.
- **Accessibility**: Limited to the block in which the variable is declared. It cannot be accessed outside this block.
- **Lifetime**: Exists only during the execution of the block.
- **Example**:
    
    ```cpp
    void func() {
        int x = 10; // x has block scope
        if (x > 5) {
            int y = 20; // y has a nested block scope
        }
        // y is not accessible here
    }
    
    ```
    

### 2. **Function Scope (Prototype Scope)**:

- **Definition**: Variables declared in the parameter list of a function or labels for `goto` statements.
- **Accessibility**: Parameters are accessible throughout the function body. Labels are accessible within the function but don't typically apply to variables.
- **Lifetime**: Parameters exist for the duration of the function call.
- **Example**:
    
    ```cpp
    void func(int x) { // x has function scope (also called parameter scope)
        std::cout << x << std::endl;
    }
    
    ```
    

### 3. **File Scope (Global Scope)**:

- **Definition**: Variables declared outside of all functions and classes, typically at the top of a file.
- **Accessibility**: Accessible from any function within the same file or across multiple files if declared with `extern`.
- **Lifetime**: Exists for the duration of the program’s execution.
- **Example**:
    
    ```cpp
    int globalVar = 100; // globalVar has file scope
    
    void func() {
        std::cout << globalVar << std::endl; // Accessible here
    }
    
    ```
    

### 4. **Class Scope (Member Scope)**:

- **Definition**: Variables (members) declared inside a class or struct.
- **Accessibility**: Accessible within the class or struct, depending on the access specifier (`private`, `protected`, `public`). Members can also be accessed via objects of the class.
- **Lifetime**: For non-static members, exists for the lifetime of the object. Static members exist for the duration of the program.
- **Example**:
    
    ```cpp
    class MyClass {
    private:
        int privateVar; // privateVar has class scope, accessible only within this class
    
    public:
        void setVar(int x) {
            privateVar = x; // Accessing within the class
        }
    };
    
    ```
    

### 5. **Namespace Scope**:

- **Definition**: Variables declared inside a namespace.
- **Accessibility**: Accessible within the namespace, and can be accessed outside using the `namespace::` qualifier or the `using` directive.
- **Lifetime**: Same as global variables, they exist for the duration of the program.
- **Example**:
    
    ```cpp
    namespace MyNamespace {
        int myVar = 10; // myVar has namespace scope
    
        void func() {
            std::cout << myVar << std::endl; // Accessible within the namespace
        }
    }
    
    ```
    

### Summary:

- **Block Scope**: Limited to the `{}` block in which the variable is declared.
- **Function (Parameter) Scope**: Applies to function parameters, accessible only within the function.
- **File (Global) Scope**: Variables declared outside any function, accessible across the entire file and potentially across multiple files.
- **Class (Member) Scope**: Applies to members of a class or struct, controlled by access specifiers.
- **Namespace Scope**: Variables declared within a namespace, controlling visibility within that namespace.

These scopes define the visibility and lifetime of variables within different parts of a C++ program, helping manage variable access and memory usage effectively.