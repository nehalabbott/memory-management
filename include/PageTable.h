#pragma once

#include <cstdint>
#include <string>

struct Stats
{
    uint64_t accesses = 0;
    uint64_t hits = 0;
    uint64_t pageFaults = 0;
    uint64_t evictions = 0;
    uint64_t framesAllocated = 0;
};

class PageTable
{
public:
    virtual uint32_t translate(uint32_t virtualAddress) = 0;

    virtual void printStats() = 0;

    virtual Stats getStats() const = 0;

    virtual std::string getName() const = 0;

    virtual ~PageTable() = default;
};