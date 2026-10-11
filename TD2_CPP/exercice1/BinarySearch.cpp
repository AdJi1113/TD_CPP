#include "BinarySearch.h"

int BinarySearch::search(const std::vector<int>& elements, int target)
{
    numberComparisons = 0;
    int resultat = -1;
    int gauche = 0;
    int droite = (int) elements.size() - 1;
    while (gauche <= droite)
    {
        int milieu = gauche + (droite - gauche) / 2;
        ++numberComparisons;
        if (elements[milieu] == target)
        {
            resultat = milieu;
            break;
        }
        ++numberComparisons;
        if (elements[milieu] < target)
            gauche = milieu + 1;
        else
            droite = milieu - 1;
    }
    ++totalSearch;
    totalComparisons += numberComparisons;
    averageComparisons = (double) totalComparisons / totalSearch;
    return resultat;
}
