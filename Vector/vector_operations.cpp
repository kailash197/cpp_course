#include <iostream>
#include <vector>
#include <algorithm>

// Function to print a task
void printTask(int task) {
    std::cout << "Task " << task << " completed." << std::endl;
}

int main() {
    // Declaration
    std::vector<int> tasks; // Empty vector
    std::vector<int> tasksCompleted(5); // 5 default-initialized elements (0s)
    std::vector<int> tasksToday = {1, 2, 3}; // Initializer list

    // Modifiers
    tasks.push_back(4); // Add at end
    tasksCompleted.pop_back(); // Remove last element
    tasks.insert(tasks.begin(), 0); // Insert before iterator position
    tasksCompleted.erase(tasksCompleted.begin()); // Erase element at iterator
    tasksToday.clear(); // Remove all elements
    tasks.resize(10); // Resize vector to n elements
    tasks.emplace_back(5); // In-place push_back (faster for objects)

    // Access
    std::cout << "First task: " << tasks.at(0) << std::endl; // Safe element access
    std::cout << "Second task: " << tasks[1] << std::endl; // Fast access (no check)
    std::cout << "First completed task: " << tasksCompleted.front() << std::endl; // First element
    std::cout << "Last completed task: " << tasksCompleted.back() << std::endl; // Last element
    std::cout << "Underlying array: " << tasks.data() << std::endl; // Pointer to underlying array

    // Capacity
    std::cout << "Number of tasks: " << tasks.size() << std::endl; // Current number of elements
    std::cout << "Allocated storage size: " << tasks.capacity() << std::endl; // Allocated storage size
    std::cout << "Is tasks empty? " << tasks.empty() << std::endl; // Check if empty
    tasks.reserve(20); // Pre-allocate storage
    tasks.shrink_to_fit(); // Reduce capacity to match size

    // Iterators
    std::cout << "First task: " << *tasks.begin() << std::endl; // Iterator to first
    std::cout << "Past last task: " << *(tasks.end() - 1) << std::endl; // Iterator to past last
    std::cout << "Last task: " << *tasks.rbegin() << std::endl; // Reverse iterator to last
    std::cout << "Before first task: " << *(tasks.rend())<<std::endl;
}