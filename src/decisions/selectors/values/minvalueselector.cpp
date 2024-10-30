#include "minvalueselector.h"

int MinValueSelector::selectValue(IntVar * i){

    //The set is always sorted
    return *i->values.setvalues.begin();
}