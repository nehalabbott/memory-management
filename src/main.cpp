#include "SingleLevelPageTable.h"
#include "MultiLevelPageTable.h"
#include "LRUPageTable.h"
#include "FIFOPageTable.h"
#include "HashPageTable.h"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "Benchmark.h"
#include "CSVWriter.h"

using namespace std;
template<typename T>
BenchmarkResult benchmark(const string& name, const vector<uint32_t>& addresses)
{
    T pageTable;

    auto start = chrono::high_resolution_clock::now();

    for (uint32_t addr : addresses)
    {
        pageTable.translate(addr);
    }

    auto end = chrono::high_resolution_clock::now();

    auto duration =
        chrono::duration_cast<chrono::milliseconds>(end - start);


    cout << name << '\n';

    cout << "Execution Time : "
         << duration.count()
         << " ms\n\n";

    pageTable.printStats();

    BenchmarkResult result;

    result.algorithm = pageTable.getName();
    result.executionTime = duration.count();
    result.stats = pageTable.getStats();

    return result;
}
int main()
{
    const int NUM_ADDRESSES = 1000000;

    vector<uint32_t> addresses;
    addresses.reserve(NUM_ADDRESSES);

    mt19937 rng(42);

    // Simulate 500 "hot" pages that are frequently accessed
    uniform_int_distribution<uint32_t> hotPageDist(0, 499);

    // Random offset within a 4KB page
    uniform_int_distribution<uint32_t> offsetDist(0, 4095);

    // Every 100 accesses, jump to a different region
    uniform_int_distribution<uint32_t> jumpDist(500, 50000);

    uint32_t currentPage = 0;

    for (int i = 0; i < NUM_ADDRESSES; i++)
    {
        if (i % 100 == 0)
            currentPage = jumpDist(rng);

        uint32_t page;

        if (rng() % 10 < 9)
            page = currentPage + hotPageDist(rng) % 20;
        else
            page = jumpDist(rng);

        uint32_t address = (page << 12) | offsetDist(rng);

        addresses.push_back(address);
    }
    vector<BenchmarkResult> results;
    results.push_back(

        benchmark<SingleLevelPageTable>(
            "Single",
            addresses
        )
    );
    results.push_back(

        benchmark<MultiLevelPageTable>(
            "Two-Level Page Table",
            addresses
        )
    );
    results.push_back(

        benchmark<LRUPageTable>(
            "LRU Page Table",
            addresses
        )
    );
    results.push_back(

        benchmark<FIFOPageTable>(
            "FIFO Page Table",
            addresses
        )
    );  
    results.push_back(

        benchmark<HashPageTable>(
            "Hash Page Table",
            addresses
        )

    );
    CSVWriter::save(results, "results.csv");
    return 0;
}