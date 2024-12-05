#include "GaussianBlur.h"

GaussianBlur::GaussianBlur() {
    this->width = 0;
    this->height = 0;
    this->pixels = vector<vector<Pixel> >();
}

GaussianBlur::GaussianBlur(vector<vector<Pixel> >& pixels) : pixels(pixels) {
    this->pixels = pixels;
    width = pixels[0].size();
    height = pixels.size();
}

void GaussianBlur::applyBlur() {

}