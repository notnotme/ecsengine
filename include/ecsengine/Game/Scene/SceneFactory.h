#ifndef SCENE_FACTORY_H
#define SCENE_FACTORY_H

#include <functional>
#include <memory>
#include <cstdint>

#include "GameScene.h"


using SceneFactory =
    std::function<
        std::unique_ptr<GameScene>(uint32_t sceneId)
    >;


#endif //SCENE_FACTORY_H
