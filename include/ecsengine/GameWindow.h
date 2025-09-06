#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <cstdint>
#include <string_view>

#include <SDL.h>

#include "Game/Game.h"
#include "Game/Scene/SceneFactory.h"
#include "Game/Scene/TransitionFactory.h"
#include "Game/GamePad.h"
#include "Game/OnGameStart.h"


class GameWindow final {
private:
    SDL_Window *m_sdl_window;
    SDL_GLContext m_sdl_gl_context;
    Game m_game;
    GamePad m_gamepad;

public:
    GameWindow(const GameWindow &) = delete;
    GameWindow &operator=(const GameWindow &) = delete;
    explicit GameWindow(int32_t gameWidth, int32_t gameHeight, OnGameStart onGameStart, SceneFactory sceneFactory, TransitionFactory transitionFactory);

public:
    void create(std::string_view title, int32_t width, int32_t height);
    void show();
    void destroy();
};


#endif //GAME_WINDOW_H
