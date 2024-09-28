#include <iostream>
#include "../src/variables/IntVar.h"
#include "../src/model.h" 
 // Include your class header
using namespace std;

int main() {

    cout<<"test"<<endl;
    
    IntVar var("Variable1", 1, 10);
    IntVar var2("Variable2", 6, 10);
    
    std::cout << "LB: " << var.getLB() << std::endl;
    std::cout << "UB: " << var.getUB() << std::endl;

    if (var.contains(5)) {
        std::cout << "5 is within the bounds of the variable." << std::endl;
    }
    for (int i=0; i<9;++i){
    }
    
    var.removeValue(6);
    std::cout<<var.toString()<<endl;
    


    // Optionally instantiate and get the value
    try {
        var.getValue();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    } 


    Model m = Model();
    
    m.vars.push_back(var);
    m.vars.push_back(var2);
    for(int i =0; i<m.vars.size();++i){
        std::cout<<m.vars[i].toString();
    }
    m.add_binary_cstr(&m.vars[0],&m.vars[1]);

    //m.vars[0].setUB(7);
    m.vars[0].instantiateTo(7);
    m.propagator_queue.back()->propagate();

     for(int i =0; i<m.vars.size();++i){
        std::cout<<m.vars[i].toString();
    }

    return 0;
}