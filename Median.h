#ifndef MEDIAN_H
#define MEDIAN_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Pixel.h"
#include "Image.h"

class Median {
    public:
        Image image;
        Median();
        Median(const Image& img);
        void applyMedianFilter(int windowSize);
        Pixel adjustWindowWithTheMedian(int x, int y, int displacement, int M);
        int medianValue(const vector<int>& vec);
};

#endif