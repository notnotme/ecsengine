#ifndef TRANSITION_SCENE_H
#define TRANSITION_SCENE_H

#include <entityx/entityx.h>
#include <glad/glad.h>

#include "../../Asset/AssetManager.h"
#include "../../Event/BehaviorEnd.h"
#include "../GamePad.h"
#include "Scene.h"


class TransitionScene : public Scene, public entityx::Receiver<TransitionScene> {
protected:
    bool m_is_finished;

public:
    explicit TransitionScene();

public:
    virtual void enter(entityx::EventManager& gameEvents, AssetManager &assets, int32_t sceneWidth, int32_t sceneHeight, GLuint outTexture, GLuint inTexture);
    virtual void exit(entityx::EventManager& gameEvents, AssetManager &assets);
    virtual void update(entityx::EventManager& gameEvents, entityx::TimeDelta dt) = 0;
    virtual void handleGamePad(entityx::EventManager& gameEvents, const GamePad& oldGamePad, const GamePad& gamePad) = 0;

    void receive(const BehaviorEnd& event);
    bool isFinished() const;
};


#endif //TRANSITION_SCENE_H
