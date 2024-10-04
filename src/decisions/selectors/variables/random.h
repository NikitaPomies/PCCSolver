
#include "variableselector.h"

class RandomVariableSelector : public VariableSelector
{
public:
    IntVar& selectVariable(vector<IntVar> &v) override;
};