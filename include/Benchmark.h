#pragma once

#include "PageTable.h"

#include <vector>
#include <string>

struct BenchmarkResult
{
    std::string algorithm;

    long long executionTime;

    Stats stats;
};