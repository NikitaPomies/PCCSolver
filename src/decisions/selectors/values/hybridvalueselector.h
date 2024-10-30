#pragma once
#include "valueselector.h"
#include "randomvalueselector.h"
#include "leastconstrainedvalueselector.h"

class HybridSelector : public ValueSelector
{
private:
    RandomValueSelector randomSelector;        // Random value selector instance
    LeastConstrainingValue lcvSelector;        // Least constraining value selector instance
    const int threshold = 5;                  // Threshold for switching heuristics

public:
    using ValueSelector::ValueSelector;

    HybridSelector(Model* model) 
        : ValueSelector(model), 
          randomSelector(model), 
          lcvSelector(model) {}

    int selectValue(IntVar *i) override
    {
        if (i->values.setvalues.size() < threshold)
        {
            // Call the Least Constraining Value selector if domain size is below the threshold
            return lcvSelector.selectValue(i);
        }
        else
        {
            // Otherwise, use the Random Value selector
            return randomSelector.selectValue(i);
        }
    }
};