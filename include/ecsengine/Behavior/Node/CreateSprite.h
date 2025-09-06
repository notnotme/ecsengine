#ifndef CREATE_SPRITE_H
#define CREATE_SPRITE_H

#include <cstdint>

#include <entityx/entityx.h>

#include "../../Asset/SpriteSheet/TextureRegion.h"
#include "../../Component/Position.h"
#include "../../Component/Size.h"
#include "../../Component/TextureUnit.h"
#include "../../Component/TextureCoordinate.h"
#include "../Node.h"


class CreateSprite final : public Node {
private:
    entityx::Entity m_target;
    Position m_position;
    Size m_size;
    TextureCoordinate m_texture_coordinate;
    TextureUnit m_texture_unit;
    bool m_created;

public:
    explicit CreateSprite(entityx::Entity target, float x, float y, const TextureRegion& region, TextureUnit::Unit unit);
    explicit CreateSprite(entityx::Entity target, float x, float y, int16_t width, int16_t height, float texture_s, float texture_t, float texture_p, float texture_q, TextureUnit::Unit unit);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<CreateSprite> create(const entityx::Entity target, const float x, const float y, const TextureRegion& region, const TextureUnit::Unit unit) {
        return std::make_unique<CreateSprite>(target, x, y, region, unit);
    }

    [[nodiscard]] static std::unique_ptr<CreateSprite> create(const entityx::Entity target, const float x, const float y, const int16_t width, const int16_t height, const float texture_s, const float texture_t, const float texture_p, const float texture_q, const TextureUnit::Unit unit) {
        return std::make_unique<CreateSprite>(target, x, y, width, height, texture_s, texture_t, texture_p, texture_q, unit);
    }
};


#endif //CREATE_SPRITE_H
