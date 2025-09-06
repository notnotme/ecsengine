#include <ecsengine/Game/Scene/TransitionScene.h>


TransitionScene::TransitionScene()
    : m_is_finished(false) {}

void TransitionScene::enter(entityx::EventManager &gameEvents, AssetManager &assets, int32_t sceneWidth, int32_t sceneHeight, GLuint outTexture, GLuint inTexture) {
    m_events.subscribe<BehaviorEnd>(*this);
}

void TransitionScene::exit(entityx::EventManager &gameEvents, AssetManager &assets) {
    m_events.unsubscribe<BehaviorEnd>(*this);
}

bool TransitionScene::isFinished() const {
    return m_is_finished;
}

void TransitionScene::receive(const BehaviorEnd &event) {
    (void) event;
    m_is_finished = true;
}
