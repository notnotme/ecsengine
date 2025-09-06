#ifndef TEXTURe_REGION_H
#define TEXTURe_REGION_H

#include <cstdint>


struct TextureRegion {
    float texture_s;
    float texture_t;
    float texture_p;
    float texture_q;
    int16_t width;
    int16_t height;

    explicit TextureRegion(const float texture_s = 0.0f, const float texture_t = 0.0f, const float texture_p = 1.0f, const float texture_q = 1.0f, const int16_t width = 0, const int16_t height = 0)
        : texture_s(texture_s),
          texture_t(texture_t),
          texture_p(texture_p),
          texture_q(texture_q),
          width(width),
          height(height) {}
};


#endif //TEXTURe_REGION_H
