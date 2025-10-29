#include <iostream>
using namespace std;
/*
const:
- an object whose value can't be changed
- For const, reference to const or pointer to a const object, the compiler doesn't let you 
  call any methods on that object unless those methods guarantee that they won't change any data members.
- const specification is part of the method protype and must accompany in its defintion as well.
- static method can't be const. It's redundant as static methods don't have instance of class so 
    can't change object members.
- You can call const and non-const methods on a non-const object. 
  However, you can only call const methods on a const object.


*/


int main(){
    
    /*
        1. Constant Identifiers
    */
    int x = 10;
    cout<<"After increment: "<<++x<<endl; //possible

    const int y = 15;
    // ++y; Error: expression must be a modifiable lvalue

    /*
        2. Pointer to a constant indentifier
    */
    int z = 25, a =100;
    
    int* ptr = &z;
    cout<<"z before: "<<z<<", after: "<<++(*ptr)<<endl;
    ptr = &a; // possible to point to another int.
    
    const int* ptr2 = &z; //pointer to constant integer
    ptr2 = &y;
    // ++(*ptr2); //Error: expression must be a modifiable lvalue
    ptr2 = &a; // Pointer itself is not constant so can point elsewhere.
    // ++(*ptr2); but again pointer can't change the value it points to
    

    /*
        3. constant Pointer to a variable
    */

    int b = 5, c = 55;
    int* const ptr3 = &b; // point to integer (pointer itself is constant)
    cout<<"before b: "<<(*ptr3)<<", after: "<<++(*ptr3)<<endl;
    //    ptr3 = &c; Error: expression must be a modifiable lvalue

    /*
        4. constant Pointer to a constant identifier
    */

    int d = 7, e = 77;
    const int* const ptr4 = &d; 
    // ++(*ptr4); //error coz. const int* means data can't be changed using pointer, however ++d can be used to change value.
    // ptr4 = &e; //Error coz. int* const means pointer is constant, can't point to new variable.

    const int f = 8;
    // ++f;
    const int* ptr5 = &f; // data can't be changed directly and also can't modify using pointer
    // ++*ptr5;


    /* 
        5. Constant Member functions, see notes.
            
        6. Constant Parameters, see notes.
    */

    return 0;
}
/* 
After increment: 11
z before: 25, after: 26
before b: 5, after: 6
*/