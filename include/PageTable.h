#pragma once

#include <cstdint>

class PageTable
{
public:
    virtual uint32_t translate(uint32_t virtualAddress) = 0;
    virtual void printStats() = 0;
    virtual ~PageTable() {}
};