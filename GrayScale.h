#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "Image.h"
#include <chrono>

using namespace std::chrono;

class GrayScale : public Image {
    public:
        GrayScale();
        Image sequentialGrayScale(Image& img);
        Image parallelGrayScale(Image& img);
};

#endif // GRAYSCALE_H