#include "Image.h"

Image::Image() : width(0), height(0) {}

Image::Image(const string& filename) {
    readImage(filename);
}

void Image::readImage(const string& filename) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Could not open file");
    }

    string line;

    getline(file, line);
    if (line != "P3") {
        throw runtime_error("Unsupported PPM format (only P3 is supported)");
    }

    while (getline(file, line)) {
        if (line[0] == '#') {
            continue;
        } else {
            break;
        }
    }

    istringstream header_stream(line);
    int width, height;
    header_stream >> width >> height;

    file >> line;
    int max_value = stoi(line);

    vector<vector<Pixel> > pixel_matrix(height, vector<Pixel>(width));
    int r, g, b;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (!(file >> r >> g >> b)) {
                throw runtime_error("Invalid PPM data");
            }
            pixel_matrix[i][j] = Pixel(r, g, b);
        }
    }

    this->width = width;
    this->height = height;
    this->pixels = pixel_matrix;
}

void Image::writeImage(const string& filename) {
    if (pixels.empty() || pixels[0].empty()) {
        throw runtime_error("Image has no pixel data to write");
    }
    ofstream file(filename);
    if (!file) {
        throw runtime_error("Could not open file for writing");
    }
    
    int max_value = 0;
    for (const auto& row : pixels) {
        for (const auto& pixel : row) {
            int max_rgb = std::max(pixel.r, std::max(pixel.g, pixel.b));
            max_value = std::max(max_value, max_rgb);

        }
    }
    file << "P3\n";
    file << width << " " << height << "\n";
    file << max_value << "\n";
    for (const auto& row : pixels) {
        for (const auto& pixel : row) {
            file << pixel.r << " " << pixel.g << " " << pixel.b << " ";
        }
        file << "\n";
    }
    file.close();
}