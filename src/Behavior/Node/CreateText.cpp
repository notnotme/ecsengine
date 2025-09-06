#include <ecsengine/Behavior/Node/CreateText.h>

#include <cmath>

#include <ecsengine/Component/Position.h>
#include <ecsengine/Component/Size.h>
#include <ecsengine/Component/TextureCoordinate.h>


CreateText::CreateText(entityx::EntityManager& entities, std::vector<entityx::Entity>& target, const std::shared_ptr<FontAsset>& font, const float x, const float y, const std::u16string_view text, const TextureUnit::Unit unit)
    : m_entities(entities),
      m_font(font),
      m_target(target),
      m_position_x(x),
      m_position_y(y),
      m_text(text),
      m_unit(unit),
      m_created(false) {
    const auto reserve = text.length();
    m_target.reserve(m_target.size() + reserve);
}

CreateText::CreateText(entityx::EntityManager& entities, std::vector<entityx::Entity>& target, const std::shared_ptr<FontAsset>& font, const float x, const float y, const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha, const std::u16string_view text, const TextureUnit::Unit unit)
    : m_entities(entities),
      m_font(font),
      m_target(target),
      m_tint(red, green, blue, alpha),
      m_position_x(x),
      m_position_y(y),
      m_text(text),
      m_unit(unit),
      m_created(false) {
    m_target.reserve(text.length());
}

bool CreateText::execute(const entityx::TimeDelta dt) {
    if (m_created) {
        return true;
    }

    auto pen_position_x = m_position_x;
    const auto pen_position_y = m_position_y;
    for (const auto letter : m_text) {
        const auto& character = m_font->getCharacter(letter);
        const auto character_width = static_cast<float>(character.width);
        const auto character_height = static_cast<float>(character.height);
        const auto half_character_width = character_width / 2.0f;
        const auto half_character_height = character_height / 2.0f;
        auto position_x = pen_position_x + half_character_width;
        auto position_y = pen_position_y + half_character_height;
        if (letter == ' ') {
            pen_position_x += character_width;
            continue;
        }

        auto &sprite = m_target.emplace_back(m_entities.create());
        sprite.assign<Position>(position_x, position_y, 0);
        sprite.assign<Size>(character.width, character.height);
        sprite.assign<TextureUnit>(m_unit);
        sprite.assign<Tint>(m_tint);
        sprite.assign<TextureCoordinate>(character.texture_s, character.texture_t, character.texture_p, character.texture_q);
        pen_position_x += character_width;
    }

    return m_created = true;
}
