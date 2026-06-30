#include "CSVWriter.h"

#include <fstream>

void CSVWriter::save(
    const std::vector<BenchmarkResult>& results,
    const std::string& filename)
{
    std::ofstream file(filename);

    file << "Algorithm,"
         << "ExecutionTime,"
         << "Accesses,"
         << "Hits,"
         << "PageFaults,"
         << "Evictions,"
         << "Frames,"
         << "HitRate\n";

    for(const auto& r : results)
    {
        double hitRate =
            100.0 * r.stats.hits / r.stats.accesses;

        file
            << r.algorithm << ","
            << r.executionTime << ","
            << r.stats.accesses << ","
            << r.stats.hits << ","
            << r.stats.pageFaults << ","
            << r.stats.evictions << ","
            << r.stats.framesAllocated << ","
            << hitRate
            << "\n";
    }
}