#include "GrayScale.h"

GrayScale::GrayScale() {}

Image GrayScale::sequentialGrayScale(Image& img) {
    Image gray_image;
    gray_image.width = img.width;
    gray_image.height = img.height;
    gray_image.pixels = img.pixels;

    for (int i = 0; i < gray_image.height; ++i) {
        for (int j = 0; j < gray_image.width; ++j) {
            int gray = (gray_image.pixels[i][j].r + gray_image.pixels[i][j].g + gray_image.pixels[i][j].b) / 3;
            gray_image.pixels[i][j] = Pixel(gray, gray, gray);
        }
    }

    return gray_image;
}