# Basics of CPP

## What is C++?
- a superset of C++
- designed to be object-oriented C ie. C with classes
- many limitations of C were addressed

---

## Hello, World!
```cpp
// filename: helloworld.cpp
/* This is a multiline comment; 
	ignored by compiler
*/
#include <iostream>

int main()
{
	std::cout << "Hello, World!" << std::endl;
	return 0;
}	
```
Three are three basic parts in a C++ program.

1. Comments
	- Single line comments begin with `//` followed by texts
	- Multi-line comments are enlosed within `/*` and `*/`
	- Comments are ignored by compilers and are not part of the program execution.
2. Preprocessor Directives
3. `main()` function
--- 

## Build and Run a program
There are three stages in building:
1. Preprocessing
2. Compilation
3. Linking
