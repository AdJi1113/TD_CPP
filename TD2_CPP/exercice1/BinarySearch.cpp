#include "BinarySearch.h"

int BinarySearch::search(const std::vector<int>& elements, int target)
{
    beginSearch(elements);
    int gauche = 0;
    int droite = (int) elements.size() - 1;
    while (gauche <= droite)
    {
        int milieu = gauche + (droite - gauche) / 2;
        ++numberComparisons;
        if (elements[milieu] == target)
            return endSearch(milieu);
        ++numberComparisons;
        if (elements[milieu] < target)
            gauche = milieu + 1;
        else
            droite = milieu - 1;
    }
    return endSearch(-1);
}
