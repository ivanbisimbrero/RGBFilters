#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "Image.h"

class GrayScale : public Image {
    public:
        GrayScale();
        Image sequentialGrayScale(Image& img);
        Image parallelGrayScale(Image& img);
};

#endif // GRAYSCALE_H