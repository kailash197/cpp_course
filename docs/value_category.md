### `lvalue`
- A value that has a persistent memory location. 
- can take its address.
- Example:
    ```cpp
    int x = 10;
    x // is an lvalue.
    ```

### `rvalue`
- A temporary value that does not have a stable memory location.
-  You cannot take its address directly.
- Example:
    ```cpp
    10 // an rvalue.
    (x + 5) // an rvalue.
    ```

### `xvalue` (expiring value)
- A value that is about to expire.
- It refers to a specific object but is treated as a temporary.
- Example:
    ```cpp
    std::move(x) // produces an xvalue.
    ```

### `prvalue` (pure rvalue)
- A pure temporary value with no identity.
- Examples:
    ```cpp
    10
    3.14
    std::string("hi")
    ```
### `glvalue`
- generalized lvalue.  
- a value that has an identity, whether or not it’s about to expire.
- `glvalue` = `lvalue` + `xvalue`
- Every `lvalue` is a glvalue.  
- Every `xvalue` is also a glvalue.  
- `prvalue`s are NOT glvalues.
- Examples:
    ```CPP
    int x = 5; // x is an lvalue → glvalue
    std::move(x); // this is an xvalue → glvalue
    ```

### Quick summary
`lvalue` = has identity and address  
`rvalue` = temporary  
`xvalue` = expiring object (rvalue with identity)  
`prvalue` = pure temporary  
`glvalue` = lvalue or xvalue  
`rvalue` = xvalue or prvalue  


