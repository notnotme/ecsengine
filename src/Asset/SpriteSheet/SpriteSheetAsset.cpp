#include <ecsengine/Asset/SpriteSheet/SpriteSheetAsset.h>

#include <stdexcept>


const TextureRegion& SpriteSheetAsset::getTextureRegion(const std::string_view name) const {
    const auto* name_to_find = name.data();

    if (const auto &region = m_sprites.find(name_to_find); region != m_sprites.end()) {
        return region->second;
    }

    throw std::out_of_range("TextureRegion not found: " + std::string(name));
}
