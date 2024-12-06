#ifndef MEDIANPARALLEL_H
#define MEDIANPARALLEL_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Pixel.h"
#include "Image.h"

class MedianParallel {
    public:
        Image image;
        MedianParallel();
        MedianParallel(const Image& img);
        void applyMedianFilterParallel(int windowSize);
        vector<vector<Pixel>> createWindowParallel(int x, int y, int windowSize);
        void adjustWindowWithTheMedianParallel(int x, int y, vector<vector<Pixel>> window);
};

#endif