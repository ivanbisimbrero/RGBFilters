#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Pixel.h"

using namespace std;

class Image {
    public:
        int width, height;
        vector<vector<Pixel> > pixels;
        Image();
        Image(const string& filename);

        void writeImage(const string& filename);
        void readImage(const string& filename);
        
        Image* getImage();
};

#endif // IMAGE_H