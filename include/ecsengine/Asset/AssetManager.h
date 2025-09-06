#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

#include <entityx/entityx.h>

#include "../Audio/AudioPlayer.h"
#include "../Renderer/QuadProgram.h"
#include "../Renderer/SpriteProgram.h"
#include "Asset.h"
#include "LoadableAsset.h"


class AssetManager final {
private:
    friend class Game;

    std::unordered_map<std::string, std::shared_ptr<Asset>> m_assets;
    std::shared_ptr<AudioPlayer> m_audio_player;
    SpriteProgram m_sprite_program;
    QuadProgram m_quad_program;

private:
    void create();
    void destroy();

public:
    AssetManager(const AssetManager &) = delete;
    AssetManager &operator=(const AssetManager &) = delete;
    explicit AssetManager(entityx::EventManager& gameEvents);

public:
    template <class T = LoadableAsset<>, typename ... Args>
    std::shared_ptr<typename T::BaseType> load(std::string_view path, Args &&... args);

    template <class T = LoadableAsset<>>
    void unload(std::string_view path);

    template <class T = LoadableAsset<>>
    [[nodiscard]] std::shared_ptr<typename T::BaseType> get(std::string_view path);

    [[nodiscard]] const SpriteProgram& getSpriteProgram() const;
    [[nodiscard]] const QuadProgram& getQuadProgram() const;
    [[nodiscard]] std::shared_ptr<AudioPlayer> getAudioPlayer() const;
};


template <class T, typename... Args>
std::shared_ptr<typename T::BaseType> AssetManager::load(const std::string_view path, Args&&... args) {
    if (const auto& it = m_assets.find(path.data()); it != m_assets.end()) {
        return std::static_pointer_cast<typename T::BaseType>(it->second);
    }

    const auto asset = std::make_shared<T>(std::forward<Args>(args)...);
    asset->load(path);
    m_assets[path.data()] = asset;

    return asset;
}

template <class T>
void AssetManager::unload(const std::string_view path) {
    if (const auto& it = m_assets.find(path.data()); it != m_assets.end()) {
        const auto& asset = std::static_pointer_cast<T>(it->second);
        asset->unload();
        m_assets.erase(it);
    }
}

template <class T>
[[nodiscard]] std::shared_ptr<typename T::BaseType> AssetManager::get(const std::string_view path) {
    if (const auto& it = m_assets.find(path.data()); it != m_assets.end()) {
        return std::static_pointer_cast<typename T::BaseType>(it->second);
    }

    throw std::out_of_range("No such file inside in cache: " + std::string(path));
}


#endif //ASSET_MANAGER_H
