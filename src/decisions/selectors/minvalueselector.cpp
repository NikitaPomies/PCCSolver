#include "minvalueselector.h"

int MinValueSelector::selectValue(const IntVar * i){

    //The set is always sorted
    return *i->values.setvalues.begin();
}