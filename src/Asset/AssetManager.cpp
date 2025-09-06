#include <ecsengine/Asset/AssetManager.h>


AssetManager::AssetManager(entityx::EventManager& gameEvents)
    : m_audio_player(std::make_unique<AudioPlayer>(gameEvents)) {}

void AssetManager::create() {
    m_quad_program.create();
    m_sprite_program.create();
    m_audio_player->create();
}

void AssetManager::destroy() {
    m_quad_program.destroy();
    m_sprite_program.destroy();
    m_audio_player->destroy();
}

const SpriteProgram & AssetManager::getSpriteProgram() const {
    return m_sprite_program;
}

const QuadProgram & AssetManager::getQuadProgram() const {
    return m_quad_program;
}

std::shared_ptr<AudioPlayer> AssetManager::getAudioPlayer() const {
    return m_audio_player;
}
