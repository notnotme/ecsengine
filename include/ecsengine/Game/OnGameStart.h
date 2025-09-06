#ifndef ON_GAME_START_H
#define ON_GAME_START_H

#include <functional>

#include "../Asset/AssetManager.h"


using OnGameStart =
    std::function<
        void(AssetManager& assets)
    >;


#endif //ON_GAME_START_H
