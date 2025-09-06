#ifndef FRICTION_H
#define FRICTION_H


struct Friction {
    float x;
    float y;
    float r;

    explicit Friction(const float x = 1.0f, const float y = 1.0f, const float r = 1.0f)
        : x(x),
          y(y),
          r(r) {}
};


#endif //FRICTION_H
