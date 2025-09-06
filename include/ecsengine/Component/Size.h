#ifndef SIZE_H
#define SIZE_H

#include <cstdint>


struct Size {
    int16_t width;
    int16_t height;

    explicit Size(const int16_t width = 0, const int16_t height = 0)
        : width(width),
          height(height) {}
};


#endif //SIZE_H
