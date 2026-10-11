#include "JumpSearch.h"
#include <cmath>
#include <algorithm>

int JumpSearch::search(const std::vector<int>& elements, int target)
{
    beginSearch(elements);
    int taille = (int) elements.size();
    if (taille == 0)
        return endSearch(-1);
    int pas = (int) std::sqrt(taille);
    int debut = 0;
    int fin = pas;
    while (true)
    {
        ++numberComparisons;
        if (!(elements[fin - 1] < target))
            break;
        debut = fin;
        if (debut == taille)
            return endSearch(-1);
        fin += std::min(pas, taille - fin);
    }
    for (int i = debut; i < fin; ++i)
    {
        ++numberComparisons;
        if (elements[i] == target)
            return endSearch(i);
    }
    return endSearch(-1);
}
