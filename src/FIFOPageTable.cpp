#include "FIFOPageTable.h"

#include <iostream>

uint32_t FIFOPageTable::translate(uint32_t virtualAddress)
{
    accesses++;

    uint32_t vpn = virtualAddress >> 12;
    uint32_t offset = virtualAddress & 0xFFF;

    // Page already in memory
    if(pageTable.count(vpn))
    {
        hits++;
        return (pageTable[vpn] << 12) | offset;
    }

    pageFaults++;

    if(pageTable.size() >= MAX_FRAMES)
    {
        uint32_t victim = fifoQueue.front();
        fifoQueue.pop();

        pageTable.erase(victim);

        evictions++;
    }

    pageTable[vpn] = nextFrame % MAX_FRAMES;

    fifoQueue.push(vpn);

    nextFrame++;

    return (pageTable[vpn] << 12) | offset;
}

void FIFOPageTable::printStats()
{
    std::cout << "Memory Accesses : " << accesses << '\n';
    std::cout << "Hits            : " << hits << '\n';
    std::cout << "Page Faults     : " << pageFaults << '\n';
    std::cout << "Evictions       : " << evictions << '\n';

    double hitRate = 100.0 * hits / accesses;

    std::cout << "Hit Rate        : " << hitRate << "%\n";
}

Stats FIFOPageTable::getStats() const
{
    Stats s;

    s.accesses = accesses;
    s.pageFaults = pageFaults;
    s.framesAllocated = nextFrame;
    s.hits = accesses - pageFaults;

    return s;
}

std::string FIFOPageTable::getName() const
{
    return "FIFO";
}