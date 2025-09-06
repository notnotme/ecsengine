#ifndef MUSIC_TICK_H
#define MUSIC_TICK_H

#include <cstdint>


struct MusicTick {
    int32_t pattern;
    int32_t order;
    int32_t row;

    explicit MusicTick(const int32_t pattern, const int32_t order, const int32_t row)
        : pattern(pattern),
          order(order),
          row(row) {}
};


#endif //MUSIC_TICK_H
