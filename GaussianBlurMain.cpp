#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>

using namespace std;

#include "Image.h"
#include "GaussianBlur.h"

using namespace std;
using namespace std::chrono;

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

        // Load image & initiliase kernel
        Image img(file);
        GaussianBlur gb(img);
        double GKernel[5][5];

        // Sequential
        auto startSequential = high_resolution_clock::now();
        gb.sequentialFilterCreation(GKernel, 3.0);
        vector<vector<Pixel> > new_sequential_pixels = gb.sequentialConvolution(GKernel, 5);
        auto endSequential = high_resolution_clock::now();
        duration<double> elapsed_sequential_time = endSequential - startSequential;

        cout << "Sequential: " 
             << duration_cast<milliseconds>(elapsed_sequential_time).count() 
             << "ms" << endl;

        // Parallel
        auto startParallel = high_resolution_clock::now();
        gb.parallelFilterCreation(GKernel, 3.0);
        vector<vector<Pixel> > new_parallel_pixels = gb.parallelConvolution(GKernel, 5);
        auto endParallel = high_resolution_clock::now();
        duration<double> elapsed_parallel_time = endParallel - startParallel;

        cout << "Parallel: " 
             << duration_cast<milliseconds>(elapsed_parallel_time).count() 
             << "ms" << endl;

        // Speedup
        double speedup = elapsed_sequential_time.count() / elapsed_parallel_time.count();
        speedups.push_back(speedup);
        cout << "Speedup: " << speedup << "x" << endl;

        // Write to file
        string baseName = file.substr(file.find_last_of("/") + 1);
        string outputFile = "output/blurred_" + baseName;
        cout << "Writing to file: " << outputFile << endl << endl;
        img.pixels = new_parallel_pixels;
        img.writeImage(outputFile);
    }

    // Calculate median speedup
    sort(speedups.begin(), speedups.end());
    double medianSpeedup = (speedups.size() % 2 == 0) 
        ? (speedups[speedups.size() / 2 - 1] + speedups[speedups.size() / 2]) / 2.0
        : speedups[speedups.size() / 2];

    cout << "Median Speedup: " << medianSpeedup << "x" << endl;

    return 0;
}