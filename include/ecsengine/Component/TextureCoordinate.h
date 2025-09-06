#ifndef TEXTURE_COORDINATE_H
#define TEXTURE_COORDINATE_H


struct TextureCoordinate {
    float s;
    float t;
    float p;
    float q;

    explicit TextureCoordinate(const float s = 0.0f, const float t = 0.0f, const float p = 1.0f, const float q = 1.0f)
        : s(s),
          t(t),
          p(p),
          q(q) {}
};


#endif //TEXTURE_COORDINATE_H
