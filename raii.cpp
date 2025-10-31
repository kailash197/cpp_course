#include <iostream>
#include <fstream>
#include <mutex>
#include <string>

// ===============================================================
// 🧱 WHAT IS RAII?
// ---------------------------------------------------------------
// RAII = Resource Acquisition Is Initialization
//
// It’s a C++ design principle:
//    → Acquire resources in the constructor
//    → Release them in the destructor
//
// Resources can be: files, memory, locks, sockets, connections, etc.
// When your object goes out of scope → destructor runs automatically.
//
// The idea: cleanup happens automatically and safely.
// ===============================================================

/*

Key Lessons Inside the Code
- RAII is not a library — it’s a pattern you apply.
- You can make your own RAII classes to manage anything (files, locks, connections).
- ROS 2 and C++ STL already use RAII heavily (std::unique_ptr, std::lock_guard, etc.).
- Destructors are automatically called when objects go out of scope → cleanup is guaranteed.
*/


// ===============================================================
// 🧩 EXAMPLE 1: Basic Custom RAII Class
// ---------------------------------------------------------------
// This class manages a file resource using RAII.
// ===============================================================
class FileHandler {
public:
    // Constructor → acquire resource
    FileHandler(const std::string& path)
        : file_(path) 
    {
        if (!file_.is_open()) {
            throw std::runtime_error("Failed to open file: " + path);
        }
        std::cout << "File opened: " << path << "\n";
    }

    // Destructor → release resource
    ~FileHandler() {
        file_.close();
        std::cout << "File closed.\n";
    }

    void writeLine(const std::string& line) {
        file_ << line << "\n";
    }

private:
    std::ofstream file_;
};


// ===============================================================
// 🧩 EXAMPLE 2: RAII Applied to a Lock
// ---------------------------------------------------------------
// This class manages a mutex lock using RAII.
// It automatically locks in the constructor and unlocks in the destructor.
// ===============================================================
class LockGuard {
public:
    LockGuard(std::mutex& m) : m_(m) {
        m_.lock(); // acquire resource
        std::cout << "🔒 Locked\n";
    }

    ~LockGuard() {
        m_.unlock(); // release resource
        std::cout << "🔓 Unlocked\n";
    }

private:
    std::mutex& m_;
};


// ===============================================================
// 🧩 EXAMPLE 3: RAII + Exception Safety
// ---------------------------------------------------------------
// Demonstrates how destructors still run even if exceptions are thrown.
// ===============================================================
class SensorConnection {
public:
    SensorConnection() {
        std::cout << "Connecting to sensor...\n";
        connected_ = true;
    }

    ~SensorConnection() {
        if (connected_) {
            std::cout << "Disconnecting from sensor...\n";
        }
    }

    void readData() {
        if (connected_) {
            std::cout << "Reading sensor data...\n";
        }
    }

private:
    bool connected_ = false;
};


// ===============================================================
// 🧩 EXAMPLE 4: RAII Style Similar to ROS2 Node Lifetime
// ---------------------------------------------------------------
// This is a simplified, *fake* example showing how ROS2 nodes and
// publishers use RAII behind the scenes.
// ===============================================================
class MockPublisher {
public:
    MockPublisher(const std::string& topic) : topic_(topic) {
        std::cout << "📡 Publisher created for topic: " << topic_ << "\n";
    }

    ~MockPublisher() {
        std::cout << "📡 Publisher destroyed for topic: " << topic_ << "\n";
    }

    void publish(const std::string& msg) {
        std::cout << "[" << topic_ << "] " << msg << "\n";
    }

private:
    std::string topic_;
};

class MockNode {
public:
    MockNode(const std::string& name) : name_(name) {
        std::cout << "🟢 Node '" << name_ << "' started.\n";
    }

    ~MockNode() {
        std::cout << "🔴 Node '" << name_ << "' stopped.\n";
    }

    MockPublisher create_publisher(const std::string& topic) {
        return MockPublisher(topic);
    }

private:
    std::string name_;
};


// ===============================================================
// 🧠 MAIN FUNCTION — DEMONSTRATE EVERYTHING
// ===============================================================
int main() {
    try {
        std::cout << "\n=== Example 1: FileHandler (RAII for file) ===\n";
        {
            FileHandler log("log.txt");
            log.writeLine("Hello from RAII FileHandler!");
        } // Destructor closes file automatically here

        std::cout << "\n=== Example 2: LockGuard (RAII for mutex) ===\n";
        {
            std::mutex m;
            LockGuard lock(m);  // automatically locks
            std::cout << "   Doing thread-safe work...\n";
        } // Destructor unlocks automatically

        std::cout << "\n=== Example 3: Exception safety ===\n";
        {
            try {
                SensorConnection sensor;
                sensor.readData();
                throw std::runtime_error("Something went wrong!");
            } catch (const std::exception& e) {
                std::cout << "Caught exception: " << e.what() << "\n";
            }
        }

        std::cout << "\n=== Example 4: ROS2-like Node and Publisher ===\n";
        {
            MockNode node("example_node");
            auto pub = node.create_publisher("chatter");
            pub.publish("Hello ROS2!");
        } // Node and publisher are destroyed automatically

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    std::cout << "\n✅ Program ended cleanly (all resources freed automatically).\n";
    return 0;
}


/*
=== Example 1: FileHandler (RAII for file) ===
File opened: log.txt
File closed.

=== Example 2: LockGuard (RAII for mutex) ===
🔒 Locked
   Doing thread-safe work...
🔓 Unlocked

=== Example 3: Exception safety ===
Connecting to sensor...
Reading sensor data...
Disconnecting from sensor...
Caught exception: Something went wrong!

=== Example 4: ROS2-like Node and Publisher ===
🟢 Node 'example_node' started.
📡 Publisher created for topic: chatter
[chatter] Hello ROS2!
📡 Publisher destroyed for topic: chatter
🔴 Node 'example_node' stopped.

✅ Program ended cleanly (all resources freed automatically).
*/
