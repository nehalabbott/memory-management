#include "MultiLevelPageTable.h"

#include <iostream>

uint32_t MultiLevelPageTable::translate(uint32_t virtualAddress)
{
    accesses++;

    uint32_t directoryIndex = (virtualAddress >> 22) & 0x3FF;
    uint32_t tableIndex = (virtualAddress >> 12) & 0x3FF;
    uint32_t offset = virtualAddress & 0xFFF;

    auto &secondLevel = pageDirectory[directoryIndex];

    if (secondLevel.find(tableIndex) == secondLevel.end())
    {
        secondLevel[tableIndex] = nextFrame++;
        pageFaults++;
    }

    uint32_t frame = secondLevel[tableIndex];

    return (frame << 12) | offset;
}

void MultiLevelPageTable::printStats()
{
    std::cout << "Memory Accesses : " << accesses << '\n';
    std::cout << "Page Faults     : " << pageFaults << '\n';
    std::cout << "Frames Allocated: " << nextFrame << '\n';
    double hitRate =
        100.0 * (accesses - pageFaults) / accesses;

    std::cout << "Hit Rate        : "
              << hitRate
              << "%\n";
    std:: cout<< std:: endl;
}
Stats MultiLevelPageTable::getStats() const
{
    Stats s;

    s.accesses = accesses;
    s.pageFaults = pageFaults;
    s.framesAllocated = nextFrame;
    s.hits = accesses - pageFaults;

    return s;
}

std::string MultiLevelPageTable::getName() const
{
    return "Multi Level";
}