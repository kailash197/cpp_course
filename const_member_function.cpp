#include <iostream>
#include <string>

using namespace std;

class Person {
public:
    Person(const string& fName, const string& lName) : firstName(fName), lastName(lName) {}
    const string& getFirstName() const; // this member fucntion can't modify any member variables & returned value can't be modified
    const string& getLastName() const;
    string getName() ;  // Note that getName now returns a string, not a const string&

private:
    string firstName;
    string lastName;
};

const string& Person::getFirstName() const {
    return firstName;
}

const string& Person::getLastName() const {
    return lastName;
}

string Person::getName()  {
    // Concatenate the first and last name and return the result
    string fname = this->getFirstName();
    fname = "Jack";
    return fname + " " + lastName;
}

int main() {
    Person myP("John", "Doe");
    cout << myP.getFirstName() << endl;
    

    string name = myP.getName();
    cout << name << endl;

    cout<< myP.getFirstName( )<<endl;


    return 0;
}
/*
John
Jack Doe
John
*/
