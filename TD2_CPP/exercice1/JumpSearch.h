#ifndef JUMP_SEARCH_H
#define JUMP_SEARCH_H
#include "SearchingAlgorithm.h"

class JumpSearch : public SearchingAlgorithm
{
public:
    int search(const std::vector<int>& elements, int target) override;
};
#endif
