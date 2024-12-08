#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
    public:
        int r, g, b;
        Pixel();
        Pixel(int r, int g, int b) : r(r), g(g), b(b) {}
        Pixel& operator=(const Pixel& other) {
            if (this != &other) {
                this->r = other.r;
                this->g = other.g;
                this->b = other.b;
            }
            return *this;
        }
};

#endif // PIXEL_H