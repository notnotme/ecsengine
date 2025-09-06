#ifndef FONT_ASSET_H
#define FONT_ASSET_H

#include <cstdint>
#include <unordered_map>

#include <glad/glad.h>
#include <SDL_ttf.h>

#include "../Asset.h"
#include "Character.h"


class FontAsset : public Asset {
protected:
    std::unordered_map<char16_t, Character> m_character_cache;
    GLuint m_texture;
    TTF_Font *p_font;

protected:
    explicit FontAsset();

public:
    [[nodiscard]] GLuint getTexture() const;
    [[nodiscard]] int32_t getFontHeight() const;
    [[nodiscard]] const Character& getCharacter(char16_t character) const;
};


#endif //FONT_ASSET_H
