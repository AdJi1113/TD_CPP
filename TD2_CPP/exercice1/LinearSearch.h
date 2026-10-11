#ifndef LINEAR_SEARCH_H
#define LINEAR_SEARCH_H
#include "SearchingAlgorithm.h"

class LinearSearch : public SearchingAlgorithm
{
public:
    int search(const std::vector<int>& elements, int target) override;
};
#endif
