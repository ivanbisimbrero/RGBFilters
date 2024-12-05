#include "GrayScale.h"

GrayScale::GrayScale() {}

Image GrayScale::sequentialGrayScale(Image& img) {
    Image gray_image;
    gray_image.width = img.width;
    gray_image.height = img.height;
    gray_image.pixels = img.pixels;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < gray_image.height; ++i) {
        for (int j = 0; j < gray_image.width; ++j) {
            int gray = (gray_image.pixels[i][j].r + gray_image.pixels[i][j].g + gray_image.pixels[i][j].b) / 3;
            gray_image.pixels[i][j] = Pixel(gray, gray, gray);
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Tiempo secuencial: " << duration << " µs" << endl;

    return gray_image;
}

Image GrayScale::parallelGrayScale(Image& img) {
    Image gray_image;
    gray_image.width = img.width;
    gray_image.height = img.height;
    gray_image.pixels = img.pixels;

    auto start = high_resolution_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < gray_image.height; ++i) {
        for (int j = 0; j < gray_image.width; ++j) {
            int gray = (gray_image.pixels[i][j].r + gray_image.pixels[i][j].g + gray_image.pixels[i][j].b) / 3;
            gray_image.pixels[i][j] = Pixel(gray, gray, gray);
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Tiempo paralelo: " << duration << " µs" << endl;

    return gray_image;
}