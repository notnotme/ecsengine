#ifndef TINT_H
#define TINT_H

#include <cstdint>


struct Tint {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;

    explicit Tint(const uint8_t red = 255, const uint8_t green = 255, const uint8_t blue = 255, const uint8_t alpha = 255)
        : red(red),
          green(green),
          blue(blue),
          alpha(alpha) {
    }
};


#endif //TINT_H
