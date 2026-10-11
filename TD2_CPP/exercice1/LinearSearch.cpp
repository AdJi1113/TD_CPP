#include "LinearSearch.h"

int LinearSearch::search(const std::vector<int>& elements, int target)
{
    numberComparisons = 0;
    int resultat = -1;
    for (int i = 0; i < (int) elements.size(); ++i)
    {
        ++numberComparisons;
        if (elements[i] == target)
        {
            resultat = i;
            break;
        }
    }
    ++totalSearch;
    totalComparisons += numberComparisons;
    averageComparisons = (double) totalComparisons / totalSearch;
    return resultat;
}
