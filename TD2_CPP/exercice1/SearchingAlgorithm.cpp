#include "SearchingAlgorithm.h"

long long SearchingAlgorithm::totalComparisons = 0;
long long SearchingAlgorithm::totalSearch = 0;
double SearchingAlgorithm::averageComparisons = 0;

SearchingAlgorithm::SearchingAlgorithm() : numberComparisons(0) {}
SearchingAlgorithm::~SearchingAlgorithm() {}

void SearchingAlgorithm::displaySearchResults(std::ostream& os, int results, int target) const
{
    os << "Cible " << target << " : ";
    if (results == -1)
        os << "absente";
    else
        os << "indice " << results;
    os << ", comparaisons : " << numberComparisons
       << ", total : " << totalComparisons << ", recherches : " << totalSearch
       << ", moyenne : " << averageComparisons << '\n';
}

int SearchingAlgorithm::getNumberComparisons() const { return numberComparisons; }
long long SearchingAlgorithm::getTotalComparisons()
{
    return totalComparisons;
}
long long SearchingAlgorithm::getTotalSearch() { return totalSearch; }
double SearchingAlgorithm::getAverageComparisons()
{
    return averageComparisons;
}
