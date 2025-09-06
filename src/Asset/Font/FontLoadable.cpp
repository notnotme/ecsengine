#include <ecsengine/Asset/Font/FontLoadable.h>

#include <stdexcept>
#include <limits>

#include <ecsengine/Renderer/RendererUtil.h>


FontLoadable::FontLoadable(const int32_t fontSizePt, const int32_t textureSize, const bool isSolid)
    : m_texture_size(textureSize),
      m_is_solid(isSolid),
      m_font_size(fontSizePt) {}

void FontLoadable::load(const std::string_view path) {
    constexpr auto font_color = SDL_Color(255, 255, 255, 255);
    constexpr auto character_spacing = 1;

    p_font = TTF_OpenFont(path.data(), m_font_size);
    if (p_font == nullptr) {
        throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
    }

    auto blit_area = SDL_Rect(character_spacing, character_spacing, 0, 0);
    auto* texture_data = SDL_CreateRGBSurfaceWithFormat(0, m_texture_size, m_texture_size, 32, SDL_PIXELFORMAT_RGBA32);
    if (!texture_data) {
        throw std::runtime_error("Failed to create texture data for Font: " + std::string(SDL_GetError()));
    }

    const auto font_height = TTF_FontHeight(p_font);
    constexpr auto min_index = std::numeric_limits<uint8_t>::min();
    constexpr auto max_index = std::numeric_limits<uint8_t>::max();
    for(char16_t character=min_index; character<max_index; ++character) {
        SDL_Surface* glyph;
        if (m_is_solid) {
            glyph = TTF_RenderGlyph_Solid(p_font, character, font_color);
        } else {
            glyph = TTF_RenderGlyph_Blended(p_font, character, font_color);
        }

        if (glyph == nullptr) {
            continue;
        }

        blit_area.w = glyph->w;
        blit_area.h = glyph->h;
        if (blit_area.x + blit_area.w + character_spacing > m_texture_size) {
            blit_area.x = character_spacing;
            blit_area.y += font_height + character_spacing;
            if (blit_area.y + font_height + character_spacing >= m_texture_size) {
                throw std::runtime_error("Font texture size is too small: " + std::to_string(m_texture_size));
            }
        }

        SDL_BlitSurface(glyph, nullptr, texture_data, &blit_area);
        SDL_FreeSurface(glyph);

        const auto sprite_width = static_cast<int16_t>(blit_area.w + 1 & ~1);
        const auto sprite_height = static_cast<int16_t>(blit_area.h + 1 & ~1);
        const auto texture_size = static_cast<float>(m_texture_size);
        const auto texture_s = static_cast<float>(blit_area.x) / texture_size;
        const auto texture_t = static_cast<float>(blit_area.y) / texture_size;
        const auto texture_p = static_cast<float>(blit_area.x + sprite_width) / texture_size;
        const auto texture_q = static_cast<float>(blit_area.y + sprite_height) / texture_size;

        m_character_cache.emplace(character,
            Character {
                texture_s,
                texture_t,
                texture_p,
                texture_q,
                sprite_width,
                sprite_height
            }
        );

        blit_area.x += blit_area.w + character_spacing;
    }

    m_texture = createUint8Texture(m_texture_size, m_texture_size, 4);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_texture_size, m_texture_size, GL_RGBA, GL_UNSIGNED_BYTE, texture_data->pixels);
    SDL_FreeSurface(texture_data);
}

void FontLoadable::unload() {
    glDeleteTextures(1, &m_texture);
    m_texture = 0;

    TTF_CloseFont(p_font);
    p_font = nullptr;
}
