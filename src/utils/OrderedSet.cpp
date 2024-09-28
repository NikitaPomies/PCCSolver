#include <set>
#include <iostream>
#include <optional>
#include "OrderedSet.h"


void OrderedSet::insert(int value) {
    setvalues.insert(value);
}

void OrderedSet::remove(int value) {
    setvalues.erase(value);
}
bool OrderedSet::contains(int value){
    return (setvalues.find(value)!=setvalues.end());
}

std::optional<int> OrderedSet::nextValue(int value) const {
    auto it = setvalues.upper_bound(value);
    if (it != setvalues.end()) {
        return *it;
    }
    return std::nullopt;
}

std::optional<int> OrderedSet::previousValue(int value) const {
    auto it = setvalues.lower_bound(value);
    if (it != setvalues.begin() && it != setvalues.end()) {
        --it;
        return *it;
    }
    return std::nullopt;
}


