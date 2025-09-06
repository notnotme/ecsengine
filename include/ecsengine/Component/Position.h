#ifndef POSITION_H
#define POSITION_H

#include <cstdint>


struct Position {
    float x;
    float y;
    int32_t z_index;

    explicit Position(const float x = 0.0f, const float y = 0.0f, const int32_t zIndex = 0)
        : x(x),
          y(y),
          z_index(zIndex) {}
};


#endif //POSITION_H
