#include "leastconstrainedvalueselector.h"
#include "../../../model.h"

int LeastConstrainingValue::selectValue(IntVar *i) {
    bool leastConstraining = true;
    const std::set<int> valueSet = i->values.setvalues;
    int bestValue = *valueSet.begin();
    int optimalRemainingValues = leastConstraining ? -1 : INT_MAX; // Initialize based on strategy

    for (int value : valueSet) {
        try {
            // Assign the current variable temporarily to this value
            i->instantiateTo(value);
            parent_model->worldPush();
            parent_model->forward_checking(i);

            // Count remaining available values for neighboring variables
            int remainingValues = 0;
            for (const auto &var : parent_model->vars) { // Assuming neighbors are accessible
                remainingValues += var.values.setvalues.size();
            }

            // Update best value based on least or most constraining criterion
            bool isBetterValue = (leastConstraining && remainingValues > optimalRemainingValues) ||
                                 (!leastConstraining && remainingValues < optimalRemainingValues);

            if (isBetterValue) {
                optimalRemainingValues = remainingValues;
                bestValue = value;
            }

            parent_model->worldBack();
            i->values.setvalues = valueSet;
        } catch (const std::runtime_error& ) {
            continue;
        }
    }

    return bestValue;
}