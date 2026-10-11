#include "LinearSearch.h"

int LinearSearch::search(const std::vector<int>& elements, int target)
{
    beginSearch(elements);
    for (int i = 0; i < (int) elements.size(); ++i)
    {
        ++numberComparisons;
        if (elements[i] == target)
            return endSearch(i);
    }
    return endSearch(-1);
}
