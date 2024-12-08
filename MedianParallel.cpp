#include <algorithm>
#include <omp.h>

#include "MedianParallel.h"

using namespace std;

MedianParallel::MedianParallel() {}

MedianParallel::MedianParallel(const Image& img) {
    this->image = img;
}

void MedianParallel::applyMedianFilterParallel(int windowSize) {
    int displacement = (windowSize - 1) / 2;
    Image filteredImage = this->image;

    #pragma omp parallel for
    for (int i = 0; i < this->image.height; i++) {
        for (int j = 0; j < this->image.width; j++) {
            filteredImage.pixels[i][j] = adjustWindowWithTheMedianParallel(i, j, displacement, windowSize);
        }
    }

    this->image = filteredImage;
}



Pixel MedianParallel::adjustWindowWithTheMedianParallel(int x, int y, int displacement, int M) {
    vector<int> vecR;
    vector<int> vecG;
    vector<int> vecB;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            int imI = x - displacement + i;
            int imJ = y - displacement + j;
            if (imI >= 0 && imI < this->image.height && imJ >= 0 && imJ < this->image.width) {
                vecR.push_back(this->image.pixels[imI][imJ].r);
                vecG.push_back(this->image.pixels[imI][imJ].g);
                vecB.push_back(this->image.pixels[imI][imJ].b);
            }
        }
    }

    sort(vecR.begin(), vecR.end());
    sort(vecG.begin(), vecG.end());
    sort(vecB.begin(), vecB.end());

    Pixel medianPixel = Pixel(medianValue(vecR), medianValue(vecG), medianValue(vecB));
    return medianPixel;
}

int MedianParallel::medianValue(const vector<int>& vec) {
    int size = vec.size();
    if (size % 2 == 0) {
        int mid1 = size / 2 - 1;
        int mid2 = size / 2;
        return (vec[mid1] + vec[mid2]) / 2;
    } else {
        return vec[size / 2];
    }
}