/*
mutable data members:
- mutable data members can be modified by inside a const method

*/

#include <iostream>
#include <memory>

class Robot{
    private: 
        int version;
        std::string name;
        mutable size_t counter;
    
    public:
        std::string getName() const;
        Robot(int v, std::string s):version(v), name(s){};
        void printCount() const {
            std::cout<<"Counter: "<<counter<<std::endl;
        }
};

std::string Robot::getName() const{
    ++counter;
    return name;
}

int main(){
    auto mybot = std::make_unique<Robot>(2, "xty");
    std::cout<<mybot->getName() <<std::endl;
    std::cout<<mybot->getName() <<std::endl;
    std::cout<<mybot->getName() <<std::endl;

    mybot->printCount();

    return 0;
}
