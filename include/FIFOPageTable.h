#pragma once

#include "PageTable.h"

#include <unordered_map>
#include <queue>
#include <cstdint>

class FIFOPageTable : public PageTable
{
private:

    static constexpr uint32_t MAX_FRAMES = 1024;

    std::unordered_map<uint32_t,uint32_t> pageTable;

    std::queue<uint32_t> fifoQueue;

    uint32_t nextFrame = 0;

    uint64_t accesses = 0;
    uint64_t hits = 0;
    uint64_t pageFaults = 0;
    uint64_t evictions = 0;

public:

    uint32_t translate(uint32_t virtualAddress) override;

    void printStats() override;
};