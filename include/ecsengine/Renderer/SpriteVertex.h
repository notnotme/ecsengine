#ifndef SPRITE_VERTEX_H
#define SPRITE_VERTEX_H

#include <cstdint>


struct SpriteVertex {
    float rotation;
    float translation_x;
    float translation_y;
    int16_t texture_s;
    int16_t texture_t;
    int16_t texture_p;
    int16_t texture_q;
    int16_t width;
    int16_t height;
    uint8_t tint_r;
    uint8_t tint_g;
    uint8_t tint_b;
    uint8_t tint_a;
    uint8_t slot;
    uint8_t pad[3];
};


#endif //SPRITE_VERTEX_H
