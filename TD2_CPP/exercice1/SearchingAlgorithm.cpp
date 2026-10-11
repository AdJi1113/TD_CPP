#include "SearchingAlgorithm.h"
#include <climits>
#include <stdexcept>

long long SearchingAlgorithm::totalComparisons = 0;
long long SearchingAlgorithm::totalSearch = 0;
double SearchingAlgorithm::averageComparisons = 0;
long long SearchingAlgorithm::pendingComparisons = 0;

SearchingAlgorithm::SearchingAlgorithm() : numberComparisons(0) {}
SearchingAlgorithm::~SearchingAlgorithm() {}

void SearchingAlgorithm::beginSearch(const std::vector<int>& elements)
{
    if (elements.size() > (std::size_t) INT_MAX)
        throw std::length_error("Indice non representable par un int");
    numberComparisons = 0;
}

int SearchingAlgorithm::endSearch(int result)
{
    ++totalSearch;
    pendingComparisons += numberComparisons;
    return result;
}

void SearchingAlgorithm::updateStatistics()
{
    // Consomme les comparaisons une seule fois, meme si on reaffiche le resultat.
    totalComparisons += pendingComparisons;
    pendingComparisons = 0;
    averageComparisons = totalSearch == 0 ? 0 : (double) totalComparisons / totalSearch;
}

void SearchingAlgorithm::displaySearchResults(std::ostream& os, int results, int target) const
{
    updateStatistics();
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
    updateStatistics();
    return totalComparisons;
}
long long SearchingAlgorithm::getTotalSearch() { return totalSearch; }
double SearchingAlgorithm::getAverageComparisons()
{
    updateStatistics();
    return averageComparisons;
}
