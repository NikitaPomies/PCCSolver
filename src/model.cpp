

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <stdexcept>


#include"model.h"



// void Model::initialize_propagation(){
//     for (auto &constraint: cstrs){
//         for (auto &propagator: constraint.propagators){
//             propagator_queue.push(&propagator);
//         }
//     }
// };

void Model::add_binary_cstr(IntVar *i , IntVar *j){
    
    propagator_queue.push(new PropXnotY(i,j));
}




