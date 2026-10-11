#include "JumpSearch.h"
#include <cmath>
#include <algorithm>

int JumpSearch::search(const std::vector<int>& elements, int target)
{
    numberComparisons = 0;
    int resultat = -1;
    int taille = (int) elements.size();
    int pas = (int) std::sqrt(taille);
    int debut = 0;
    int fin = pas;
    while (debut < taille)
    {
        ++numberComparisons;
        if (elements[fin - 1] >= target)
            break;
        debut = fin;
        fin += std::min(pas, taille - fin);
    }
    for (int i = debut; i < fin; ++i)
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
