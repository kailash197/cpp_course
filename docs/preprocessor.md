## Preprocessor
- Recognizes meta-information about the code
- Directives start with `#` sign followed by directive command eg.`#include`

### `#include`
- Use: `#include <library_name>`
- used to refer to a library used in the program

### `Header files`
- used to declare functions that are used elsewhere`
- function declaration tells compiler how a function is called, declaring the number and types of parameters and function return type
- declarations usually go into `header files` ; header.hpp (.h for c, hpp for cpp)
- function defintion contains the actual code for the function
- definitions usually go into `source files`, source.cpp
Example:
- `<iostream>` declares the input and output mechanisms provided by C++
- `iostream` library has `cout`, `cin` objects

### `#define`
- `#define` is a **preprocessor directive** used to create **macros**—symbolic names or expressions that are replaced by their values before compilation.
- It helps in defining constants, simplifying repetitive code, and enabling conditional compilation.
- C++ encourages to use `const`, `constexpr`

```cpp
// 🚀 Robot Constants
#define WHEEL_RADIUS 0.05           // meters
#define MAX_LINEAR_SPEED 1.2        // m/s
#define MAX_ANGULAR_SPEED 2.5       // rad/s

// 🧠 Sensor Thresholds
#define OBSTACLE_DISTANCE_THRESHOLD 0.3  // meters
#define LOW_BATTERY_VOLTAGE 11.0         // volts
// ⚙️ Pin Assignments (for microcontrollers)
#define MOTOR_LEFT_PIN 5
#define MOTOR_RIGHT_PIN 6
#define ULTRASONIC_TRIGGER_PIN 9
#define ULTRASONIC_ECHO_PIN 10

// 🧮 Macro Function
#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

// 🛑 Usage Example
double speed = CLAMP(requested_speed, 0.0, MAX_LINEAR_SPEED);
if (distance_to_obstacle < OBSTACLE_DISTANCE_THRESHOLD) {
    stopRobot();
}
```
While `#define is powerful, modern C++ prefers using const, constexpr, and inline functions for better type safety, debugging, and scoping.

### `#ifdef, #ifndef, #endif`
These directives control **conditional compilation**, allowing parts of code to be included or excluded based on whether certain macros are defined. One use case is to avoid multiple includes.
- `#ifdef` → *If defined*: Includes code only if the macro is defined.
- `#ifndef` → *If not defined*: Includes code only if the macro is **not** defined.
- `#endif` → Ends the conditional block.
    
```cpp
// Define a macro to enable LIDAR support
#define USE_LIDAR

#ifdef USE_LIDAR
    #include "lidar_driver.hpp"
    void initLidar() {
        // Initialize LIDAR sensor
    }
#endif

#ifndef USE_CAMERA
    #define USE_CAMERA
    #include "camera_driver.hpp"
    void initCamera() {
        // Initialize camera sensor
    }
#endif
```
    
✅ Use Cases in Robotics
- Enable/disable specific sensors (LIDAR, camera, IMU).
- Compile platform-specific code (e.g., Raspberry Pi vs Jetson).
- Toggle debug or simulation modes.

### `#pragma`:
- `#pragma` is a compiler-specific directive used to give special instructions to the compiler.
- It is not part of the C++ language standard, but widely supported by most compilers.
    
Common Use: 
- `#pragma once`
```cpp
#pragma once
class MotorController {
public:
    void setSpeed(double speed);
};

```

Examples (compiler-specific):
```cpp
#pragma warning(disable : 4996)   // Disable specific warning (MSVC)
#pragma pack(1)                   // Set memory alignment to 1 byte (useful in embedded robotics)
```        
⚠️ Warning: Use pragma directives carefully, as they may not be portable across different compilers.
