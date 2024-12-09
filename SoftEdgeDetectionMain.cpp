#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

#include "Image.h"
#include "SoftEdgeDetection.h"  // Include your SoftEdgeDetection class

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

        // Load the image
        Image img(file);

        SoftEdgeDetection sed;

        // Sequential Soft Edge Detection
        auto startSequential = high_resolution_clock::now();
        Image seq_result = sed.sequentialSoftEdgeDetection(img, 3.0);
        auto endSequential = high_resolution_clock::now();
        duration<double> elapsed_sequential_time = endSequential - startSequential;

        cout << "Sequential: " 
             << duration_cast<milliseconds>(elapsed_sequential_time).count() 
             << " ms" << endl;

        // Parallel Soft Edge Detection
        auto startParallel = high_resolution_clock::now();
        Image par_result = sed.parallelSoftEdgeDetection(img, 3.0);
        auto endParallel = high_resolution_clock::now();
        duration<double> elapsed_parallel_time = endParallel - startParallel;

        cout << "Parallel: " 
             << duration_cast<milliseconds>(elapsed_parallel_time).count() 
             << " ms" << endl;

        // Speedup
        double speedup = elapsed_sequential_time.count() / elapsed_parallel_time.count();
        speedups.push_back(speedup);
        cout << "Speedup: " << speedup << "x" << endl;

        // Write to file
        string baseName = file.substr(file.find_last_of("/") + 1);
        string outputFileSeq = "output/soft_edges_seq_" + baseName;
        string outputFilePar = "output/soft_edges_par_" + baseName;

        cout << "Writing sequential result to: " << outputFileSeq << endl;
        seq_result.writeImage(outputFileSeq);

        cout << "Writing parallel result to: " << outputFilePar << endl << endl;
        par_result.writeImage(outputFilePar);
    }

    // Calculate median speedup
    sort(speedups.begin(), speedups.end());
    double medianSpeedup = (speedups.size() % 2 == 0) 
        ? (speedups[speedups.size() / 2 - 1] + speedups[speedups.size() / 2]) / 2.0
        : speedups[speedups.size() / 2];

    cout << "Median Speedup: " << medianSpeedup << "x" << endl;

    return 0;
}