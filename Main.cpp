#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "Image.h"

using namespace std;

int main() {
    Image img("images/medium.ppm");
    for (const auto& row : img.pixels) {
        for (const auto& pixel : row) {
            std::cout << "(" << pixel.r << ", " << pixel.g << ", " << pixel.b << ") ";
        }
        std::cout << "\n";
    }
    cout << img.width << " " << img.height << "\n";
    return 0;
}