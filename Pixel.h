#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
    public:
        int r, g, b;
        Pixel();
        Pixel(int r, int g, int b) : r(r), g(g), b(b) {}
};

#endif // PIXEL_H