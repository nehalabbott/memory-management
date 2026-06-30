#pragma once

#include "PageTable.h"

#include <unordered_map>
#include <cstdint>

class SingleLevelPageTable : public PageTable
{
private:
    std::unordered_map<uint32_t, uint32_t> table;

    uint32_t nextFrame = 0;

    uint64_t accesses = 0;
    uint64_t pageFaults = 0;

public:
    uint32_t translate(uint32_t virtualAddress) override;

    void printStats() override;
    Stats getStats() const override;
    
std::string getName() const override;
};