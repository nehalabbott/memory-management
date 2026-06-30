#pragma once

#include "PageTable.h"

#include <vector>
#include <list>
#include <cstdint>
#include <string>

struct HashEntry
{
    uint32_t vpn;
    uint32_t frame;
};

class HashPageTable : public PageTable
{
private:

    static constexpr uint32_t TABLE_SIZE = 4096;

    std::vector<std::list<HashEntry>> table;

    uint32_t nextFrame = 0;

    uint64_t accesses = 0;
    uint64_t hits = 0;
    uint64_t pageFaults = 0;

public:

    HashPageTable();

    uint32_t translate(uint32_t virtualAddress) override;

    void printStats() override;

    Stats getStats() const override;

    std::string getName() const override;
};