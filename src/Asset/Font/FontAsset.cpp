#include <ecsengine/Asset/Font/FontAsset.h>

#include <format>
#include <stdexcept>

#include <SDL_ttf.h>


FontAsset::FontAsset()
    : m_texture(0),
      p_font(nullptr) {}

GLuint FontAsset::getTexture() const {
    return m_texture;
}

int32_t FontAsset::getFontHeight() const {
    return TTF_FontHeight(p_font);
}

const Character& FontAsset::getCharacter(const char16_t character) const {
    if (const auto& it = m_character_cache.find(character); it != m_character_cache.end()) {
        return it->second;
    }

    throw std::out_of_range("Character not found: " + std::format("0x{:x}", static_cast<uint8_t>(character)));
}
