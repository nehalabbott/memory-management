#include "LRUPageTable.h"

#include <iostream>

uint32_t LRUPageTable::translate(uint32_t virtualAddress)
{
    accesses++;

    uint32_t vpn = virtualAddress >> 12;
    uint32_t offset = virtualAddress & 0xFFF;

    if (pageTable.count(vpn))
    {
        hits++;

        lruList.erase(position[vpn]);
        lruList.push_front(vpn);
        position[vpn] = lruList.begin();

        return (pageTable[vpn] << 12) | offset;
    }

-
    pageFaults++;

    if (pageTable.size() >= MAX_FRAMES)
    {
        uint32_t victim = lruList.back();
        lruList.pop_back();

        position.erase(victim);
        pageTable.erase(victim);

        evictions++;
    }

    pageTable[vpn] = nextFrame % MAX_FRAMES;

    lruList.push_front(vpn);
    position[vpn] = lruList.begin();

    nextFrame++;

    return (pageTable[vpn] << 12) | offset;
}

void LRUPageTable::printStats()
{
    std::cout << "Memory Accesses : " << accesses << '\n';
    std::cout << "Hits            : " << hits << '\n';
    std::cout << "Page Faults     : " << pageFaults << '\n';
    std::cout << "Evictions       : " << evictions << '\n';

    double hitRate = 100.0 * hits / accesses;

    std::cout << "Hit Rate        : "
              << hitRate
              << "%\n";
}