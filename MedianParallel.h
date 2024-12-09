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
        Pixel adjustWindowWithTheMedianParallel(int x, int y, int displacement, int M);
        int medianValue(const vector<int>& vec);
};

#endif