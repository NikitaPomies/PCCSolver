#include "trails.h"

void Trail::saveDomainChange(IntVar *var, int removedValue)
{
    // Get a reference to the top vector
        std::vector<std::pair<IntVar *, int>>& topVector = trailStack.top();

        // Add the new pair to the top vector
        topVector.push_back({var, removedValue});
}

// Undo the last recorded domain change
void Trail::backtrack()
{
    if (!trailStack.empty())
    {
        // Get the last domain changes
        auto &lastChanges = trailStack.top();

        // Restore all recorded changes for this level
        for (auto &change : lastChanges)
        {
            IntVar *var = change.first;
            int removedValue = change.second;
            var->values.setvalues.insert(removedValue); // Reinsert the removed value
            //std::cout << "Value " << removedValue << " reinserted for variable " << var->name << std::endl;
        }

        trailStack.pop(); // Remove the trail entry for this level
    }
}

// Get the current trail level
int Trail::getCurrentLevel() const
{
    return trailStack.size();
}
