#pragma once

#include "Benchmark.h"

#include <vector>

class CSVWriter
{
public:

    static void save(
        const std::vector<BenchmarkResult>& results,
        const std::string& filename
    );
};