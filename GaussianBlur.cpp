#include "GaussianBlur.h"
#include <cmath>
#include <omp.h>

GaussianBlur::GaussianBlur() {
    this->width = 0;
    this->height = 0;
    this->pixels = vector<vector<Pixel> >();
}

GaussianBlur::GaussianBlur(Image& image) {
    this->width = image.width;
    this->height = image.height;
    this->pixels = image.pixels;
}

void GaussianBlur::sequentialFilterCreation(double GKernel[][5]) {
    // Initialise the standard deviation to 1.0
    double sigma = 1.0;
    double s = 2.0 * sigma * sigma;

    // Sum is for normalization 
    double sum = 0.0;

    // Generate 5x5 kernel
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            double r = sqrt(x * x + y * y);
            GKernel[x + 2][y + 2] = (exp(-(r * r) / s)) / (M_PI * s);
            sum += GKernel[x + 2][y + 2];
        }
    }

    // Normalise the Kernel
    // Make sure the values of the Kernel add up to 1
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            GKernel[i][j] /= sum;
        }
    }
}

vector<vector<Pixel> > GaussianBlur::sequentialConvolution(double GKernel[][5], int iterations) {
    vector<vector<Pixel> > new_pixels(height, vector<Pixel>(width));
    int i, j, m, n, mm, nn;
    double val_r, val_g, val_b;

    // Copy the pixels to the new_pixels matrix
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            new_pixels[i][j] = pixels[i][j];
        }
    }

    // Iterate over the number of iterations
    for (int it = 0; it < iterations; ++it) {
        // Iterate over the image
        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                val_r = 0.0;
                val_g = 0.0;
                val_b = 0.0;
                // Iterate over the Gaussian kernel
                for (m = -2; m <= 2; ++m) {
                    mm = i + m;
                    for (n = -2; n <= 2; ++n) {
                        nn = j + n;
                        if (mm >= 0 && mm < height && nn >= 0 && nn < width) {
                            val_r += new_pixels[mm][nn].r * GKernel[m + 2][n + 2];
                            val_g += new_pixels[mm][nn].g * GKernel[m + 2][n + 2];
                            val_b += new_pixels[mm][nn].b * GKernel[m + 2][n + 2];
                        }
                    }
                }
                new_pixels[i][j].r = val_r;
                new_pixels[i][j].g = val_g;
                new_pixels[i][j].b = val_b;
            }
        }
        pixels = new_pixels;
    }

    return new_pixels;
}

void GaussianBlur::parallelFilterCreation(double GKernel[][5]) {
    // Initialise the standard deviation to 1.0
    double sigma = 1.0;
    double s = 2.0 * sigma * sigma;

    // Sum is for normalization 
    double sum = 0.0;

    // Generate 5x5 kernel
    #pragma omp parallel for collapse(2) reduction(+:sum)
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            double r = sqrt(x * x + y * y);
            GKernel[x + 2][y + 2] = (exp(-(r * r) / s)) / (M_PI * s);
            sum += GKernel[x + 2][y + 2];
        }
    }

    // Normalise the Kernel
    // Make sure the values of the Kernel add up to 1
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            GKernel[i][j] /= sum;
        }
    }
}

vector<vector<Pixel> > GaussianBlur::parallelConvolution(double GKernel[][5], int iterations) {
    vector<vector<Pixel> > new_pixels(height, vector<Pixel>(width));
    int i, j, m, n, mm, nn;
    double val_r, val_g, val_b;

    // Copy the pixels to the new_pixels matrix
    #pragma omp parallel for
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            new_pixels[i][j] = pixels[i][j];
        }
    }

    // Iterate over the number of iterations
    for (int it = 0; it < iterations; ++it) {
        // Iterate over the image
        #pragma omp parallel for private(val_r, val_g, val_b, m, n, mm, nn)
        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                val_r = 0.0;
                val_g = 0.0;
                val_b = 0.0;
                // Iterate over the Gaussian kernel
                for (m = -2; m <= 2; ++m) {
                    mm = i + m;
                    for (n = -2; n <= 2; ++n) {
                        nn = j + n;
                        if (mm >= 0 && mm < height && nn >= 0 && nn < width) {
                            val_r += new_pixels[mm][nn].r * GKernel[m + 2][n + 2];
                            val_g += new_pixels[mm][nn].g * GKernel[m + 2][n + 2];
                            val_b += new_pixels[mm][nn].b * GKernel[m + 2][n + 2];
                        }
                    }
                }
                new_pixels[i][j].r = val_r;
                new_pixels[i][j].g = val_g;
                new_pixels[i][j].b = val_b;
            }
        }
        swap(pixels, new_pixels);
    }

    return new_pixels;
}