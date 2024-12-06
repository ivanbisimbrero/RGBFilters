#include <algorithm>
#include "Median.h"

using namespace std;

Median::Median() {}

Median::Median(const Image& img) {
    this->image = img;
}

void Median::applyMedianFilter(int windowSize) {
    int itHeight = this->image.height - windowSize + 1;
    int itWidth = this->image.width - windowSize + 1;
    for(int i = 0; i < itHeight; i++) {
        for (int j = 0; j < itWidth; j++) {
            adjustWindowWithTheMedian(i,j,createWindow(i,j, windowSize));
        }
    }
}

vector<vector<Pixel>> Median::createWindow(int x, int y, int windowSize) {
    vector<vector<Pixel>> window(windowSize, vector<Pixel>(windowSize));
    
    for (int i = 0; i < windowSize; i++) {
        for (int j = 0; j < windowSize; j++) {
            int imgX = x + i;
            int imgY = y + j;
            window[i][j] = this->image.pixels[imgX][imgY];
        }
    }
    return window;
}


void Median::adjustWindowWithTheMedian(int x, int y, vector<vector<Pixel>> window) {
    int n = window.size();
    vector<int> vecR(n*n);
    vector<int> vecG(n*n);
    vector<int> vecB(n*n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            vecR[i*n+j] = window[i][j].r;
            vecG[i*n+j] = window[i][j].g;
            vecB[i*n+j] = window[i][j].b;
        }
    }

    sort(vecR.begin(), vecR.end());
    sort(vecG.begin(), vecG.end());
    sort(vecB.begin(), vecB.end());

    Pixel medianPixel = Pixel(vecR[vecR.size()/2], vecG[vecG.size()/2], vecB[vecB.size()/2]);
    this->image.pixels[x+n/2][y+n/2] = medianPixel;
}
