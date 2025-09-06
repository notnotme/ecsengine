#ifndef GRAVITY_H
#define GRAVITY_H


struct Gravity {
    float x;
    float y;

    explicit Gravity(const float x = 0.0f, const float y = 0.0f)
        : x(x),
          y(y) {}
};


#endif //GRAVITY_H
