#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <entityx/entityx.h>

#include "../../Asset/AssetManager.h"
#include "../GamePad.h"
#include "Scene.h"


class GameScene : public Scene {
public:
    explicit GameScene() = default;

public:
    virtual void enter(entityx::EventManager& gameEvents, AssetManager &assets, int32_t sceneWidth, int32_t sceneHeight) = 0;
    virtual void exit(entityx::EventManager& gameEvents, AssetManager &assets) = 0;
    virtual void update(entityx::EventManager& gameEvents, entityx::TimeDelta dt) = 0;
    virtual void handleGamePad(entityx::EventManager& gameEvents, const GamePad& oldGamePad, const GamePad& gamePad) = 0;
};


#endif //GAME_SCENE_H
