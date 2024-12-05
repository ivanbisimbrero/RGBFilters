#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "Image.h"
#include "GrayScale.h"

int main() {
    Image img("images/really_large.ppm");
    // for (const auto& row : img.pixels) {
    //     for (const auto& pixel : row) {
    //         std::cout << "(" << pixel.r << ", " << pixel.g << ", " << pixel.b << ") ";
    //     }
    //     std::cout << "\n";
    // }
    // cout << img.width << " " << img.height << "\n";

    GrayScale gs;
    Image gray_img_sequential = gs.sequentialGrayScale(img);
    Image gray_img_parallel = gs.parallelGrayScale(img);
    //gray_img.writeImage("images/small_grayscale.ppm");
    return 0;
}