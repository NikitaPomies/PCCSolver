#include "most_constrained.h"


IntVar &MostConstrainedVarSelector::selectVariable(vector<IntVar> &v)
{
    IntVar *mostConstrainedVar = nullptr;
    size_t minSize = std::numeric_limits<size_t>::max();

    for (auto &var : v)
    {
        if(!var.isAssigned()){
        size_t currentSize = var.values.setvalues.size();
        if (currentSize < minSize)
        {
            minSize = currentSize;
            mostConstrainedVar = &var;
        }
        }
    }
    if (mostConstrainedVar == nullptr){
        std::cout<<"pb"<<std::flush;
         for (auto &var : v)
    {
        if(!var.isAssigned()){
        size_t currentSize = var.values.setvalues.size();
        if (currentSize < minSize)
        {
            minSize = currentSize;
            mostConstrainedVar = &var;
        }
        }
        else {
            std::cout<<"Variable "<<var.name << " to "<< var.getValue()<<std::endl;}

    }
    std::cout<<"test";

    }

    return *mostConstrainedVar;

}