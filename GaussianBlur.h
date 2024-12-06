#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include <vector>
#include "Image.h"

using namespace std;

class GaussianBlur {
    public:
        GaussianBlur();
        GaussianBlur(Image& image);

        void filterCreation(double GKernel[][5]);
        vector<vector<Pixel> > convolution(double GKernel[][5], int iterations);
    private:
        vector<vector<Pixel> > pixels;
        int width, height = 0;
        
};

#endif // GAUSSIANBLUR_H