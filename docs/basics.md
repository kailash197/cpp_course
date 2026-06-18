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
2. [Preprocessor Directives]({{ site.baseurl }}/docs/preprocessor.html)
3. [`main()` function]({{ site.baseurl }}/docs/main.html)

--- 

## Build and Run a program
There are three stages in building:
1. Preprocessing
	- run through preprocessor
	- Preprocessor recognizes meta-information about the code
2. Compilation:
	- translation of code to machine-readable object files
3. Linking:
	- the individual object files are linked togther into a single application

---
