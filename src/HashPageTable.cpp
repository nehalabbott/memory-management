#include "HashPageTable.h"

#include <iostream>

HashPageTable::HashPageTable()
{
    table.resize(TABLE_SIZE);
}

uint32_t HashPageTable::translate(uint32_t virtualAddress)
{
    accesses++;

    uint32_t vpn = virtualAddress >> 12;
    uint32_t offset = virtualAddress & 0xFFF;

    uint32_t index = vpn % TABLE_SIZE;

    for (auto &entry : table[index])
    {
        if (entry.vpn == vpn)
        {
            hits++;
            return (entry.frame << 12) | offset;
        }
    }

    pageFaults++;

    table[index].push_back({vpn, nextFrame});

    uint32_t physical =
        (nextFrame << 12) | offset;

    nextFrame++;

    return physical;
}

void HashPageTable::printStats()
{
    std::cout << "Memory Accesses : " << accesses << '\n';
    std::cout << "Hits            : " << hits << '\n';
    std::cout << "Page Faults     : " << pageFaults << '\n';
    std::cout << "Frames Allocated: " << nextFrame << '\n';

    double hitRate =
        100.0 * hits / accesses;

    std::cout << "Hit Rate        : "
              << hitRate
              << "%\n";
}

Stats HashPageTable::getStats() const
{
    Stats s;

    s.accesses = accesses;
    s.hits = hits;
    s.pageFaults = pageFaults;
    s.framesAllocated = nextFrame;

    return s;
}

std::string HashPageTable::getName() const
{
    return "Hash Page Table";
}