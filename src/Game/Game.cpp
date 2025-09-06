#include <ecsengine/Game/Game.h>

#include <cmath>
#include <utility>

#include <ecsengine/Renderer/QuadProgram.h>


Game::Game(const int32_t gameWidth, const int32_t gameHeight, OnGameStart onGameStart, SceneFactory sceneFactory, TransitionFactory transitionFactory)
    : m_game_width(gameWidth),
      m_game_height(gameHeight),
      m_assets(m_events),
      m_on_game_start(std::move(onGameStart)),
      m_scene_factory(std::move(sceneFactory)),
      m_transition_factory(std::move(transitionFactory)),
      m_window_width(0),
      m_window_height(0),
      m_is_running(true) {
    assert(m_on_game_start);
    assert(m_scene_factory);
    assert(m_transition_factory);
}

void Game::create(const int32_t windowWidth, const int32_t windowHeight) {
    assert(windowWidth > 0 && windowHeight > 0);
    m_assets.create();
    m_on_game_start(m_assets);

    m_events.subscribe<ExitGame>(*this);
    m_events.subscribe<SceneTransition>(*this);

    m_window_width = windowWidth;
    m_window_height = windowHeight;
    m_scene = m_scene_factory(0);
    m_scene->create(m_game_width, m_game_height);
    m_scene->enter(m_events, m_assets, m_game_width, m_game_height);
}

void Game::destroy() {
    m_assets.destroy();

    m_events.unsubscribe<ExitGame>(*this);
    m_events.unsubscribe<SceneTransition>(*this);

    if (m_transition_holder.has_value()) {
        m_transition_holder->transition_scene->exit(m_events, m_assets);
        m_transition_holder->transition_scene->destroy();
        m_transition_holder->next_scene->exit(m_events, m_assets);
        m_transition_holder->next_scene->destroy();
        m_transition_holder.reset();
    }

    m_scene->exit(m_events, m_assets);
    m_scene->destroy();

    m_window_width = 0;
    m_window_height = 0;
    m_is_running = false;
}

void Game::resize(const int32_t windowWidth, const int32_t windowHeight) {
    m_window_width = windowWidth;
    m_window_height = windowHeight;
}

bool Game::update(const GamePad &gamePad, const entityx::TimeDelta dt) {
    if (m_transition.has_value()) {
        const auto scene_id = m_transition->scene_id;
        const auto transition_id = m_transition->transition_id;
        auto next_scene = m_scene_factory(scene_id);
        next_scene->create(m_game_width, m_game_height);
        next_scene->enter(m_events, m_assets, m_game_width, m_game_height);

        const auto scene_texture = m_scene->getTexture();
        const auto next_scene_texture = next_scene->getTexture();
        auto transition = m_transition_factory(transition_id);
        transition->create(m_game_width, m_game_height);
        transition->enter(m_events, m_assets, m_game_width, m_game_height, scene_texture, next_scene_texture);

        m_transition_holder.emplace(TransitionHolder(std::move(next_scene), std::move(transition)));
        m_transition.reset();
    }

    GLuint scene_texture;
    if (m_transition_holder.has_value()) {
        if (m_transition_holder->transition_scene->isFinished()) {
            m_scene->exit(m_events, m_assets);
            m_scene->destroy();
            m_scene = std::move(m_transition_holder->next_scene);

            m_transition_holder->transition_scene->exit(m_events, m_assets);
            m_transition_holder->transition_scene->destroy();
            m_transition_holder.reset();
            scene_texture = m_scene->getTexture();
        } else {
            m_scene->update(m_events, dt);

            m_transition_holder->next_scene->update(m_events, dt);
            m_transition_holder->transition_scene->handleGamePad(m_events, m_old_gamepad, gamePad);
            m_transition_holder->transition_scene->update(m_events, dt);
            scene_texture = m_transition_holder->transition_scene->getTexture();
        }
    } else {
        m_scene->handleGamePad(m_events, m_old_gamepad, gamePad);
        m_scene->update(m_events, dt);
        scene_texture = m_scene->getTexture();
    }

    const auto ratio_width = std::ceil(std::max(1, m_window_width / m_game_width));
    const auto ratio_height = std::ceil(std::max(1, m_window_height / m_game_height));
    const auto ratio = static_cast<int32_t>(ratio_width > ratio_height ? ratio_height : ratio_width);
    const auto& quad_program = m_assets.getQuadProgram();
    constexpr auto clear_color = std::array{ 0.0f, 0.0f, 0.0f, 1.0f };

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_window_width, m_window_height);
    glScissor(0, 0, m_window_width, m_window_height);
    glClearBufferfv(GL_COLOR, 0, clear_color.data());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene_texture);

    glUseProgram(quad_program.getProgram());
    quad_program.setScreenSize(m_window_width, m_window_height);
    quad_program.setQuadSize(m_game_width * ratio, m_game_height * ratio);
    quad_program.setTint(1.0f, 1.0f, 1.0f, 1.0f);

    glBindVertexArray(quad_program.getVAO());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_old_gamepad = gamePad;
    return m_is_running;
}

void Game::receive(const SceneTransition &event) {
    if (m_transition.has_value()) {
        throw std::logic_error("Scene Transition already in place");
    }

    m_transition.emplace(event);
}

void Game::receive(const ExitGame& event) {
    (void) event;
    if (!m_is_running) {
        throw std::logic_error("Not currently running");
    }

    m_is_running = false;
}
