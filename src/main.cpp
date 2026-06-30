#include "SingleLevelPageTable.h"
#include "MultiLevelPageTable.h"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
template <typename T>
void benchmark(const string& name, const vector<uint32_t>& addresses)
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
}
int main()
{
    const int NUM_ADDRESSES = 1000000;

    vector<uint32_t> addresses;
    addresses.reserve(NUM_ADDRESSES);

    mt19937 rng(42);

    uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);

    for (int i = 0; i < NUM_ADDRESSES; i++)
    {
        addresses.push_back(dist(rng));
    }

    benchmark<SingleLevelPageTable>(
        "Single Level Page Table",
        addresses
    );

    benchmark<MultiLevelPageTable>(
        "Two-Level Page Table",
        addresses
    );

    return 0;
}