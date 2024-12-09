#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

#include "Image.h"
#include "GrayScale.h"

int main() {
    vector<string> imageFiles = {
        "images/large.ppm",
        "images/medium.ppm",
        "images/really_large.ppm",
        "images/small.ppm"
    };

    vector<double> speedups;

    for (const auto& file : imageFiles) {
        cout << "Processing: " << file << endl;

        // Load image
        Image img(file);
        GrayScale gs;

        // Sequential
        auto startSequential = high_resolution_clock::now();
        Image sequentialResult = gs.sequentialGrayScale(img);
        auto endSequential = high_resolution_clock::now();
        duration<double> elapsed_sequential_time = endSequential - startSequential;

        cout << "Sequential: " 
             << duration_cast<microseconds>(elapsed_sequential_time).count() 
             << "µs" << endl;

        // Parallel
        auto startParallel = high_resolution_clock::now();
        Image parallelResult = gs.parallelGrayScale(img);
        auto endParallel = high_resolution_clock::now();
        duration<double> elapsed_parallel_time = endParallel - startParallel;

        cout << "Parallel: " 
             << duration_cast<microseconds>(elapsed_parallel_time).count() 
             << "µs" << endl;

        // Speedup
        double speedup = elapsed_sequential_time.count() / elapsed_parallel_time.count();
        speedups.push_back(speedup);
        cout << "Speedup: " << speedup << "x" << endl;

        // Write to file
        string baseName = file.substr(file.find_last_of("/") + 1);
        string outputFile = "output/grayscale_" + baseName;
        cout << "Writing to file: " << outputFile << endl << endl;
        parallelResult.writeImage(outputFile);
    }

    // Calculate the avg speedup
    sort(speedups.begin(), speedups.end());
    double medianSpeedup = (speedups.size() % 2 == 0) 
        ? (speedups[speedups.size() / 2 - 1] + speedups[speedups.size() / 2]) / 2.0
        : speedups[speedups.size() / 2];

    cout << "GrayScale Speedup: " << medianSpeedup << "x" << endl;

    return 0;
}