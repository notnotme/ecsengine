#include <ecsengine/GameWindow.h>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <glad/glad.h>

#include <utility>


GameWindow::GameWindow(const int32_t gameWidth, const int32_t gameHeight, OnGameStart onGameStart, SceneFactory sceneFactory, TransitionFactory transitionFactory)
    : m_sdl_window(nullptr),
      m_sdl_gl_context(nullptr),
      m_game(gameWidth, gameHeight, std::move(onGameStart), std::move(sceneFactory), std::move(transitionFactory)) {}

void GameWindow::create(const std::string_view title, const int32_t width, const int32_t height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0) {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    if (TTF_Init() != 0) {
        throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        throw std::runtime_error("Failed to initialize SDL_Image: " + std::string(IMG_GetError()));
    }

    // Configure the SDL Window to accept OpenGL 4.3 Core context at least
    // We don't need depth and stencil buffer as we do 2d rendering
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
    const auto sdl_window = SDL_CreateWindow(title.data(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);

    if (sdl_window == nullptr) {
        throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
    }

    const auto sdl_gl_context = SDL_GL_CreateContext(sdl_window);
    if (sdl_gl_context == nullptr) {
        throw std::runtime_error("Failed to create OpenGL context");
    }
    
    SDL_GL_MakeCurrent(sdl_window, sdl_gl_context);
    SDL_GL_SetSwapInterval(1);
    gladLoadGL();

    // Setup default OpenGL states, especially for 2d rendering
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_sdl_window = sdl_window;
    m_sdl_gl_context = sdl_gl_context;
    m_game.create(width, height);
}

void GameWindow::show() {
    SDL_ShowWindow(m_sdl_window);

    // Request performance query to calculate dt time later
    const auto performanceQuery = static_cast<float>(SDL_GetPerformanceFrequency());

    SDL_Event event;
    auto lastTime = SDL_GetPerformanceCounter();
    auto is_running = true;

#ifdef __SWITCH__
    const auto game_controller = SDL_GameControllerOpen(0);
#endif

    while (is_running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    is_running = false;
                break;
                case SDL_CONTROLLERBUTTONDOWN:
                    if (event.cbutton.which == 0 && event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
                        is_running = false;
                    }
                break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        is_running = false;
                    }
                break;
                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            m_game.resize(event.window.data1, event.window.data2);
                        break;
                        default:
                        break;
                    }
                break;
                default:
                break;
            }
        }

        // Use performance query to calculate dt time
        const auto currentTime = SDL_GetPerformanceCounter();
        const auto dt = static_cast<float>(currentTime - lastTime) / performanceQuery;
        lastTime = currentTime;

        // Fill gamepad structure for this frame
#ifdef __SWITCH__
        m_gamepad.direction_down = SDL_GameControllerGetButton(game_controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) ? 1.0f : 0.0f;
        m_gamepad.direction_up = SDL_GameControllerGetButton(game_controller, SDL_CONTROLLER_BUTTON_DPAD_UP) ? 1.0f : 0.0f;
        m_gamepad.direction_left = SDL_GameControllerGetButton(game_controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) ? 1.0f : 0.0f;
        m_gamepad.direction_right = SDL_GameControllerGetButton(game_controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ? 1.0f : 0.0f;
        m_gamepad.button_a = SDL_GameControllerGetButton(game_controller, SDL_CONTROLLER_BUTTON_A) != 0;
        m_gamepad.button_b = SDL_GameControllerGetButton(game_controller, SDL_CONTROLLER_BUTTON_B) != 0;
#else
        const auto keys = const_cast<Uint8*>(SDL_GetKeyboardState(nullptr));
        m_gamepad.direction_down = keys[SDL_SCANCODE_DOWN] ? 1.0f : 0.0f;
        m_gamepad.direction_up = keys[SDL_SCANCODE_UP] ? 1.0f : 0.0f;
        m_gamepad.direction_left = keys[SDL_SCANCODE_LEFT] ? 1.0f : 0.0f;
        m_gamepad.direction_right = keys[SDL_SCANCODE_RIGHT] ? 1.0f : 0.0f;
        m_gamepad.button_a = keys[SDL_SCANCODE_LCTRL] != 0;
        m_gamepad.button_b = keys[SDL_SCANCODE_SPACE] != 0;
#endif

        if (!m_game.update(m_gamepad, dt) && is_running) {
            is_running = false;
        }

        SDL_GL_SwapWindow(m_sdl_window);
    }
}

void GameWindow::destroy() {
    m_game.destroy();

    IMG_Quit();
    TTF_Quit();
    SDL_GL_DeleteContext(m_sdl_gl_context);
    SDL_DestroyWindow(m_sdl_window);
    SDL_Quit();

    m_sdl_gl_context = nullptr;
    m_sdl_window = nullptr;
}
