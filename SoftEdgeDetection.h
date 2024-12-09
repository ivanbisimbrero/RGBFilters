#ifndef SOFTEDGEDETECTION_H
#define SOFTEDGEDETECTION_H

#include "Image.h"
#include <chrono>

using namespace std::chrono;

class SoftEdgeDetection : public Image {
    public:
        SoftEdgeDetection();
        Image sequentialSoftEdgeDetection(Image& img, double sigma = 1.0);
        Image parallelSoftEdgeDetection(Image& img, double sigma = 1.0);

    private:
        Image convertToGray(Image& img, bool parallel);
        Image applySobel(const Image& img, bool parallel);

        inline int clamp(int val, int low, int high) {
            return (val < low) ? low : (val > high) ? high : val;
        }
};

#endif // SOFTEDGEDETECTION_H