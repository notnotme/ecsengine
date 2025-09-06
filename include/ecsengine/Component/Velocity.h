#ifndef VELOCITY_H
#define VELOCITY_H


struct Velocity {
    float x;
    float y;
    float r;

    explicit Velocity(const float x = 0.0f, const float y = 0.0f, const float r = 0.0f)
        : x(x),
          y(y),
          r(r) {}
};


#endif //VELOCITY_H
