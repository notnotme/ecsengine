#ifndef CREATE_TEXT_H
#define CREATE_TEXT_H

#include <cstdint>
#include <string>

#include <entityx/entityx.h>

#include "../../Asset/Font/FontAsset.h"
#include "../../Component/TextureUnit.h"
#include "../../Component/Tint.h"
#include "../Node.h"


class CreateText final : public Node {
private:
    entityx::EntityManager& m_entities;
    std::shared_ptr<FontAsset> m_font;
    std::vector<entityx::Entity>& m_target;
    Tint m_tint;
    float m_position_x;
    float m_position_y;
    std::u16string m_text;
    TextureUnit::Unit m_unit;
    bool m_created;

public:
    explicit CreateText(entityx::EntityManager& entities, std::vector<entityx::Entity>& target, const std::shared_ptr<FontAsset>& font, float x, float y, std::u16string_view text, TextureUnit::Unit unit);
    explicit CreateText(entityx::EntityManager& entities, std::vector<entityx::Entity>& target, const std::shared_ptr<FontAsset>& font, float x, float y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, std::u16string_view text, TextureUnit::Unit unit);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<CreateText> create(entityx::EntityManager& entities, std::vector<entityx::Entity>& target, const float x, const float y, const std::shared_ptr<FontAsset>& font, std::u16string_view text, const TextureUnit::Unit unit) {
        return std::make_unique<CreateText>(entities, target, font, x, y, text, unit);
    }

    [[nodiscard]] static std::unique_ptr<CreateText> create(entityx::EntityManager& entities, std::vector<entityx::Entity>& target, const float x, const float y, const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha, const std::shared_ptr<FontAsset>& font, std::u16string_view text, const TextureUnit::Unit unit) {
        return std::make_unique<CreateText>(entities, target, font, x, y, red, green, blue, alpha, text, unit);
    }
};

#endif //CREATE_TEXT_H
