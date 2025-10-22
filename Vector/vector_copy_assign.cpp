#include <iostream>
#include <vector>
/*

- Constructor/Destructors:
    - vector<int> intVector; // Creates a vector of ints with zero elements
    - vector<int> intVector(10, 100); // Creates vector of 10 ints with value 100
    - If you omit the default value, the new objects are zero-initialized. 
        Zero-initialization constructs objects with the default constructor, and 
        initializes primitive integer types (such as char, int, and so on) to 
        zero, primitive floating-point types to 0.0, and pointer types to nullptr.

- Copy & Assign Vectors
    - vector stores copies of objects
    - vector destructor calls desctructor for each objects
    - copy constructor and assignment operator of vector class perform deep copies
    - RECOMMENDATION: pass vectors by reference or const reference to func or methods.
    - assign(): method to clear current elements and adds any number of new elements.
*/



class Robot{
    private:
        std::string model="default";
        int id;

    public:
        Robot(){
            std::cout<<"DC Called: ";
            print();
        };
        Robot(const std::string& mod, int idt): model(mod), id(idt){
            std::cout<<"PC Called: ";
            print();
        }
        Robot(const Robot& rt){
            model = rt.model;
            id = rt.id;
            std::cout<<"CC Called: ";
            print();
        }
        void print() const{
            std::cout<<"["<<model<<", "<<id<<"]"<<std::endl;
        }
        ~Robot(){
            std::cout<<"DD Called: ";
            print();
        };
};


void print_vector(const std::vector<Robot>& vec) {
    std::cout << "size of vector is " << vec.size() << std::endl;
    for (const auto& val : vec) {
        val.print();
    }
}
int main(){

    std::vector<Robot> robots(5, {"latest", 345}); // PC once, copy 5 times, destroy first
    print_vector(robots); 

    Robot r{"ex", 2};
    robots.assign({r});
    print_vector(robots);

    return 0;
}
/*

PC Called: [latest, 345]
CC Called: [latest, 345]
CC Called: [latest, 345]
CC Called: [latest, 345]
CC Called: [latest, 345]
CC Called: [latest, 345]
DD Called: [latest, 345]
size of vector is 5
[latest, 345]
[latest, 345]
[latest, 345]
[latest, 345]
[latest, 345]
PC Called: [ex, 2]
CC Called: [ex, 2]
DD Called: [latest, 345]
DD Called: [latest, 345]
DD Called: [latest, 345]
DD Called: [latest, 345]
DD Called: [ex, 2]
size of vector is 1
[ex, 2]
DD Called: [ex, 2]
DD Called: [ex, 2]

*/
