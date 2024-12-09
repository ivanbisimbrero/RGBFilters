#include "SoftEdgeDetection.h"
#include "GrayScale.h"
#include "GaussianBlur.h"
#include <cmath>
#include <iostream>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

SoftEdgeDetection::SoftEdgeDetection() {}

Image SoftEdgeDetection::sequentialSoftEdgeDetection(Image& img, double sigma) {
    auto start = high_resolution_clock::now();

    // 1. Convert to grayscale (sequential)
    GrayScale gs;
    Image gray = gs.sequentialGrayScale(img);

    // 2. Apply Gaussian blur (sequential)
    // Pass the grayscale image to GaussianBlur constructor for consistency
    GaussianBlur gb(gray);
    double GKernel[5][5];
    gb.sequentialFilterCreation(GKernel, sigma);
    gray.pixels = gb.sequentialConvolution(GKernel, 5);
    Image blurred = gray;

    // 3. Apply Sobel operator (sequential: parallel = false)
    Image edged = applySobel(blurred, false);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Tiempo secuencial SoftEdgeDetection: " << duration << " µs" << endl;

    return edged;
}

Image SoftEdgeDetection::parallelSoftEdgeDetection(Image& img, double sigma) {
    auto start = high_resolution_clock::now();

    // 1. Convert to grayscale (parallel)
    GrayScale gs;
    Image gray = gs.parallelGrayScale(img);

    // 2. Apply Gaussian blur (parallel)
    GaussianBlur gb(gray);
    double GKernel[5][5];
    gb.parallelFilterCreation(GKernel, sigma);
    gray.pixels = gb.parallelConvolution(GKernel, 5);
    Image blurred = gray;

    // 3. Apply Sobel operator (parallel: parallel = true)
    Image edged = applySobel(blurred, true);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Tiempo paralelo SoftEdgeDetection: " << duration << " µs" << endl;

    return edged;
}

Image SoftEdgeDetection::applySobel(const Image& img, bool parallel) {
    Image result;
    result.width = img.width;
    result.height = img.height;
    result.pixels = img.pixels; // create a copy

    int width = img.width;
    int height = img.height;

    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        { 1,  2,  1},
        { 0,  0,  0},
        {-1, -2, -1}
    };

    // If parallel is true, enable parallelization. Remove collapse(2) to avoid complexity.
    #pragma omp parallel for if(parallel)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double gx = 0.0;
            double gy = 0.0;

            for (int ky = -1; ky <= 1; ky++) {
                int yy = i + ky;
                if (yy < 0) yy = 0;
                if (yy >= height) yy = height - 1;

                for (int kx = -1; kx <= 1; kx++) {
                    int xx = j + kx;
                    if (xx < 0) xx = 0;
                    if (xx >= width) xx = width - 1;

                    double val = img.pixels[yy][xx].r; // grayscale value
                    gx += val * Gx[ky+1][kx+1];
                    gy += val * Gy[ky+1][kx+1];
                }
            }

            double mag = sqrt(gx * gx + gy * gy);
            int c = clamp((int)round(mag), 0, 255);
            result.pixels[i][j] = Pixel(c, c, c);
        }
    }

    return result;
}