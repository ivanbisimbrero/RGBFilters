#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include <vector>
#include "Image.h"

using namespace std;

class GaussianBlur {
    public:
        GaussianBlur();
        GaussianBlur(Image& image);
        // Sequential methods
        void sequentialFilterCreation(double GKernel[][5]);
        vector<vector<Pixel> > sequentialConvolution(double GKernel[][5], int iterations);
        // Parallelised methods
        void parallelFilterCreation(double GKernel[][5]);
        vector<vector<Pixel> > parallelConvolution(double GKernel[][5], int iterations);
    private:
        vector<vector<Pixel> > pixels;
        int width, height = 0;
};

#endif // GAUSSIANBLUR_H