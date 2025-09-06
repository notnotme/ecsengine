#ifndef SCALE_H
#define SCALE_H


struct Scale {
    float width;
    float height;

    explicit Scale(const float width = 1.0f, const float height = 1.0f)
        : width(width),
          height(height) {}
};


#endif //SCALE_H
