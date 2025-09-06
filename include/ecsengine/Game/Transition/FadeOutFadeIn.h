#ifndef FADE_OUT_FADE_IN_H
#define FADE_OUT_FADE_IN_H

#include <array>
#include <cstdint>

#include <glad/glad.h>
#include <entityx/entityx.h>

#include "../../Asset/AssetManager.h"
#include "../Scene/TransitionScene.h"
#include "../GamePad.h"


class FadeOutFadeIn final : public TransitionScene {
private:
    GLuint m_vertex_buffer;
    std::array<float, 4> m_clear_color;
    float m_duration_ms;

public:
    explicit FadeOutFadeIn(float red, float green, float blue, float alpha, float durationMs);

public:
    void enter(entityx::EventManager &gameEvents, AssetManager& assets, int32_t sceneWidth, int32_t sceneHeight, GLuint outTexture, GLuint inTexture) override;
    void exit(entityx::EventManager &gameEvents, AssetManager& assets) override;
    void update(entityx::EventManager &gameEvents, entityx::TimeDelta dt) override;
    void handleGamePad(entityx::EventManager &gameEvents, const GamePad& oldGamePad, const GamePad &gamePad) override;
};


#endif //FADE_OUT_FADE_IN_H
