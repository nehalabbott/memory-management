#include "SingleLevelPageTable.h"

#include <iostream>

uint32_t SingleLevelPageTable::translate(uint32_t virtualAddress)
{
    accesses++;

    uint32_t vpn = virtualAddress >> 12;
    uint32_t offset = virtualAddress & 0xFFF;

    if (table.find(vpn) == table.end())
    {
        table[vpn] = nextFrame++;
        pageFaults++;
    }

    uint32_t frame = table[vpn];

    return (frame << 12) | offset;
}

void SingleLevelPageTable::printStats()
{
    std::cout << "Memory Accesses : " << accesses << '\n';
    std::cout << "Page Faults     : " << pageFaults << '\n';
    std::cout << "Frames Allocated: " << nextFrame << '\n';
}