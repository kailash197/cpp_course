#include <iostream>
/*
- apply to the class as a whole, not to each object. 
- can write static methods as well as data members.
- Static methods don’t access information about specific objects.
- don’t repeat the static keyword in front of the method definitions
// can access private and protected static members of the class. 
It can also access private and protected non-static data members on 
objects of the same type, if those objects are made visible to the
static method, for example, by passing in a reference or pointer to such an object.
*/

class Quadcopter {
private:
    std::string id;
    double flightTime;
public:
    // Static member variables
    static int totalQuadcopters;
    static double totalFlightTime;

    Quadcopter(const std::string& id, double initialFlightTime)
        : id(id), flightTime(initialFlightTime) {
        ++totalQuadcopters;
        totalFlightTime += flightTime;
    }

    ~Quadcopter() { 
        --totalQuadcopters; 
        totalFlightTime -= flightTime;
        std::cout<<"Destructor Killed: "<<this->id<<std::endl;
    }

    void fly(double time) {
        flightTime += time;
        totalFlightTime += time;
    }

    static double averageFlightTime() {
        if (totalQuadcopters == 0) {
            return 0.0;
        }
        return totalFlightTime / totalQuadcopters;
    }

    void displayStatus() const {
        std::cout << "Quadcopter " << id << " - Flight Time: " << flightTime << " hours\n";
    }

    static void displayFleetStatus();
};
// don't repeat static keyword in fron of the method definitions
void Quadcopter::displayFleetStatus() {
        std::cout << std::endl<<"Total Quadcopters: " << totalQuadcopters << "\n";
        std::cout << "Total Flight Time: " << totalFlightTime << " hours\n";
        std::cout << "Average Flight Time: " << averageFlightTime() << " hours\n"<<std::endl;
        /* possible to access nonstatic members using objects inside static member functions
        Quadcopter q4("a", 2);
        q4.flightTime;
        */        
    }

// Initialize static member variables
int Quadcopter::totalQuadcopters = 0;
double Quadcopter::totalFlightTime = 0.0;

int main() {
    Quadcopter q1("Quad1", 5.0);
    Quadcopter q2("Quad2", 3.0);
    Quadcopter q3("Quad3", 4.0);

    q1.fly(2.0);  // Quad1 flies for 2 more hours
    q2.fly(1.5);  // Quad2 flies for 1.5 more hours

    q1.displayStatus();
    q2.displayStatus();
    q3.displayStatus();
    Quadcopter::displayFleetStatus(); // same as q3.displayFleetStatus();

    return 0;
}
/*
Quadcopter Quad1 - Flight Time: 7 hours
Quadcopter Quad2 - Flight Time: 4.5 hours
Quadcopter Quad3 - Flight Time: 4 hours

Total Quadcopters: 3
Total Flight Time: 15.5 hours
Average Flight Time: 5.16667 hours

Destructor Killed: Quad3
Destructor Killed: Quad2
Destructor Killed: Quad1
*/