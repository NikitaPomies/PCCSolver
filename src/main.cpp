#include <iostream>
#include "../src/variables/IntVar.h" 
 // Include your class header
using namespace std;

int main() {

    cout<<"test"<<endl;
    
    IntVar var("Variable1", 1, 10);
    
    std::cout << "LB: " << var.getLB() << std::endl;
    std::cout << "UB: " << var.getUB() << std::endl;

    if (var.contains(5)) {
        std::cout << "5 is within the bounds of the variable." << std::endl;
    }

    // Optionally instantiate and get the value
    try {
        var.getValue();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    } 

    return 0;
}