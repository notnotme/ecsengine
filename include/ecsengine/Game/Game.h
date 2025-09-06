#ifndef GAME_H
#define GAME_H

#include <memory>
#include <optional>
#include <cstdint>

#include <entityx/entityx.h>

#include "../Asset/AssetManager.h"
#include "../Event/ExitGame.h"
#include "../Event/SceneTransition.h"
#include "Scene/GameScene.h"
#include "Scene/TransitionFactory.h"
#include "Scene/SceneFactory.h"
#include "Scene/TransitionHolder.h"
#include "GamePad.h"
#include "OnGameStart.h"


class Game final : public entityx::Receiver<Game> {
private:
    const int32_t m_game_width;
    const int32_t m_game_height;

    std::unique_ptr<GameScene> m_scene;
    std::optional<SceneTransition> m_transition;
    std::optional<TransitionHolder> m_transition_holder;
    entityx::EventManager m_events;
    AssetManager m_assets;
    GamePad m_old_gamepad;
    OnGameStart m_on_game_start;
    SceneFactory m_scene_factory;
    TransitionFactory m_transition_factory;
    int32_t m_window_width;
    int32_t m_window_height;
    bool m_is_running;

public:
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    explicit Game(int32_t gameWidth, int32_t gameHeight, OnGameStart onGameStart, SceneFactory sceneFactory, TransitionFactory transitionFactory);

public:
    void create(int32_t windowWidth, int32_t windowHeight);
    void resize(int32_t windowWidth, int32_t windowHeight);
    void destroy();

    void receive(const SceneTransition& event);
    void receive(const ExitGame& event);

    [[nodiscard]] bool update(const GamePad &gamePad, entityx::TimeDelta dt);
};


#endif //GAME_H
