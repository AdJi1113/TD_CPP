#ifndef SEARCHING_ALGORITHM_H
#define SEARCHING_ALGORITHM_H

#include <ostream>
#include <vector>

class SearchingAlgorithm
{
protected:
    int numberComparisons;
    void beginSearch(const std::vector<int>& elements);
    int endSearch(int result);
private:
    static long long totalComparisons;
    static long long totalSearch;
    static double averageComparisons;
    static long long pendingComparisons;
    static void updateStatistics();
public:
    SearchingAlgorithm();
    virtual ~SearchingAlgorithm();
    virtual int search(const std::vector<int>& elements, int target) = 0;
    void displaySearchResults(std::ostream& os, int results, int target) const;
    int getNumberComparisons() const;
    static long long getTotalComparisons();
    static long long getTotalSearch();
    static double getAverageComparisons();
};

#endif
