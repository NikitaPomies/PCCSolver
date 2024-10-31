#include "hybridvalueselector.h"
#include "../../../model.h"

int HybridSelector::selectValue(IntVar *i)
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