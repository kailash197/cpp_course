### `main()` function
- Entrypoint where the program starts
```cpp
#include <iostream>

int main(int argc, char* argv)
{
	std::cout << "Hello, World!" << std::endl;
	return 0;
}
```

- Function return type :
    - `int`
    - if return statement is omitted, zero is automatically returned.
- Parameters:
    - nummber of parameters either zero or two
    - `int argc` : number of arguments passed to the main program
    - `char* argv`: contains the arguments 
        - `argv[0]` can be empty or the program name; not reliable to depend
        - actual parameters start at index 1.
