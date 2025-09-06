#include <ecsengine/Game/Transition/FadeOutFadeIn.h>

#include <ecsengine/Behavior/ParallelNode.h>
#include <ecsengine/Behavior/SequenceNode.h>
#include <ecsengine/Behavior/Node/BindTexture.h>
#include <ecsengine/Behavior/Node/FadeIn.h>
#include <ecsengine/Behavior/Node/FadeOut.h>
#include <ecsengine/Behavior/Node/ClearBuffer.h>
#include <ecsengine/Behavior/Node/CreateSprite.h>
#include <ecsengine/Component/TextureUnit.h>
#include <ecsengine/System/BehaviorSystem.h>
#include <ecsengine/System/SpriteSystem.h>


FadeOutFadeIn::FadeOutFadeIn(const float red, const float green, const float blue, const float alpha, const float durationMs)
    : m_vertex_buffer(0),
      m_clear_color({red, green, blue, alpha}),
      m_duration_ms(durationMs) {}

void FadeOutFadeIn::enter(entityx::EventManager &gameEvents, AssetManager &assets, const int32_t sceneWidth, const int32_t sceneHeight, const GLuint outTexture, const GLuint inTexture) {
    TransitionScene::enter(gameEvents, assets, sceneWidth, sceneHeight, outTexture, inTexture);

    constexpr auto sprites_capacity = 1;
    const auto& sprite_program = assets.getSpriteProgram();
    const auto half_scene_width = static_cast<float>(sceneWidth) / 2.0f;
    const auto half_scene_height = static_cast<float>(sceneHeight) / 2.0f;
    const auto scene_width = static_cast<int16_t>(sceneWidth);
    const auto scene_height = static_cast<int16_t>(sceneHeight);
    m_vertex_buffer = SpriteProgram::createVertexBuffer(sprites_capacity);

    const auto fading_entity = m_entities.create();
    auto behavior = SequenceNode::create(
            CreateSprite::create(fading_entity, half_scene_width, half_scene_height, scene_width, scene_height, 0.0f, 1.0f, 1.0f, 0.0f, TextureUnit::UNIT_0),
            ParallelNode::create(
                ClearBuffer::create(m_clear_color),
                SequenceNode::create(
                    ParallelNode::create(
                        BindTexture::create(outTexture, TextureUnit::UNIT_0),
                        FadeOut::create(fading_entity, m_duration_ms)
                    ),
                    ParallelNode::create(
                        BindTexture::create(inTexture, TextureUnit::UNIT_0),
                        FadeIn::create(fading_entity, m_duration_ms)
                    )
                )
            )
        );

    m_systems.add<BehaviorSystem>(std::move(behavior));
    m_systems.add<SpriteSystem>(sprite_program, m_vertex_buffer, sprites_capacity, false, sceneWidth, sceneHeight);
    m_systems.configure();
}

void FadeOutFadeIn::exit(entityx::EventManager &gameEvents, AssetManager &assets) {
    TransitionScene::exit(gameEvents, assets);

    glDeleteBuffers(1, &m_vertex_buffer);
    m_vertex_buffer = 0;
}

void FadeOutFadeIn::update(entityx::EventManager &gameEvents, const entityx::TimeDelta dt) {
    bindFramebuffer();
    m_systems.update<BehaviorSystem>(dt);
    m_systems.update<SpriteSystem>(dt);
}

void FadeOutFadeIn::handleGamePad(entityx::EventManager &gameEvents, const GamePad &oldGamePad, const GamePad &gamePad) {
    if (gamePad.button_b && !oldGamePad.button_b) {
        m_is_finished = true;
    }
}
