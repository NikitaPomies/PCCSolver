#pragma once

#include <set>
#include <optional>

class OrderedSet
{
public:
    // Inserts a value into the set
    void insert(int value);

    // Removes a value from the set
    void remove(int value);

    bool contains(int value);

    // Returns the next value greater than the given value
    std::optional<int> nextValue(int value) const;

    // Returns the previous value smaller than the given value
    std::optional<int> previousValue(int value) const;

    std::set<int> setvalues; // Internal set to store values in sorted order
private:
};
