#ifndef TEXTURE_UNIT_H
#define TEXTURE_UNIT_H


struct TextureUnit {
    enum Unit {
        UNIT_0,
        UNIT_1,
        UNIT_2,
        UNIT_3,
        UNIT_4,
        UNIT_5,
        // Units used for font (only tint RGB, not A)
        TEXT_0,
        TEXT_1,
        // Use tint only, no texture
        NONE = 1337
    };

    Unit unit;

    explicit TextureUnit(const Unit unit = NONE)
        : unit(unit) {}
};


#endif //TEXTURE_UNIT_H
