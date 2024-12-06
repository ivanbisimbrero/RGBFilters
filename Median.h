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
        vector<vector<Pixel>> createWindow(int x, int y, int windowSize);
        void adjustWindowWithTheMedian(int x, int y, vector<vector<Pixel>> window);
};

#endif