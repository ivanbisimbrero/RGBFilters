#ifndef GAUSSIANBLUR_H
#define GUASSIANBLUR_H

#include <vector>
#include "Image.h"

using namespace std;

class GaussianBlur {
    public:
        GaussianBlur();
        GaussianBlur(Image& image);

        vector<vector<int>> generateKernel(int size, double sigma);
        void applyBlur(vector<vector<int> >& kernel, const string& filename);
    private:
        vector<vector<Pixel> > pixels;
        int width, height = 0;
        
};

#endif // GAUSSIANBLUR_H