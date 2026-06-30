#pragma once

#include "PageTable.h"

#include <unordered_map>
#include <list>
#include <cstdint>

class LRUPageTable : public PageTable
{
private:
    static constexpr uint32_t MAX_FRAMES = 1024;

    // VPN -> Frame Number
    std::unordered_map<uint32_t, uint32_t> pageTable;

    // Front = Most Recently Used
    // Back = Least Recently Used
    std::list<uint32_t> lruList;

    // VPN -> Position in LRU list
    std::unordered_map<
        uint32_t,
        std::list<uint32_t>::iterator
    > position;

    uint32_t nextFrame = 0;

    uint64_t accesses = 0;
    uint64_t hits = 0;
    uint64_t pageFaults = 0;
    uint64_t evictions = 0;

public:
    uint32_t translate(uint32_t virtualAddress) override;
    void printStats() override;
    Stats getStats() const override;

    std::string getName() const override; 
};