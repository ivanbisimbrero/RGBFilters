#ifndef GAUSSIANBLUR_H
#define GUASSIANBLUR_H

#include <vector>
#include "Pixel.h"

using namespace std;

class GaussianBlur {
    public:
        GaussianBlur();
        GaussianBlur(vector<vector<Pixel> >& pixels);
        void applyBlur();
    private:
        vector<vector<Pixel> > pixels;
        int width, height = 0;
};

#endif // GAUSSIANBLUR_H