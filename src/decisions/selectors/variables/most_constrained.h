#include "variableselector.h"
#include <limits>
class MostConstrainedVarSelector : public VariableSelector{

    public:
        IntVar& selectVariable(vector<IntVar> &v) override;
};
