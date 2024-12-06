#include "Image.h"
#include "Median.h"
#include "MedianParallel.h"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main() {
    Image img("images/noise.ppm");

    //1. SECUENTIAL
    Median median(img);
    auto start_seq = high_resolution_clock::now();
    median.applyMedianFilter(3);
    auto end_seq = high_resolution_clock::now();
    auto duration_seq = duration_cast<milliseconds>(end_seq - start_seq).count();
    cout << "Writing sequential img..." << endl;
        cout << duration_seq << "ms" << endl;
    median.image.writeImage("images/noise_output.ppm");

    //2. PARALLEL
    MedianParallel medianParallel(img);
    auto start_par = high_resolution_clock::now();
    medianParallel.applyMedianFilterParallel(3);
    auto end_par = high_resolution_clock::now();
    auto duration_par = duration_cast<milliseconds>(end_par - start_par).count();
    cout << "Writing parallel img..."  << endl;
    cout << duration_par << "ms" << endl;
    medianParallel.image.writeImage("images/noise_p_output.ppm");

    double speedup = static_cast<double>(duration_seq)/duration_par;
    cout  << endl << "SPEEDUP: " << speedup << "x" << endl;

    return 0;
}