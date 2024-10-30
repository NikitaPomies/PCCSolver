#include "randomvalueselector.h"
#include <ctime>  

 int RandomValueSelector::selectValue(IntVar* i) {
        // Seed the random number generator
        std::srand(std::time(0));

        // Get the set from values.setvalues
        const std::set<int>& valueSet = i->values.setvalues;

        // Choose a random index within the size of the set
        int randomIndex = std::rand() % valueSet.size();

        // Use an iterator to advance to the random element
        auto it = valueSet.begin();
        std::advance(it, randomIndex);

        // Return the randomly selected value
        return *it;
    }