#include <ecsengine/Behavior/Node/CreateSprite.h>

#include <ecsengine/Component/TextureUnit.h>
#include <ecsengine/Component/Tint.h>


CreateSprite::CreateSprite(const entityx::Entity target, const float x, const float y, const TextureRegion& region, const TextureUnit::Unit unit)
    : m_target(target),
      m_position(x, y, 0),
      m_size(region.width, region.height),
      m_texture_coordinate(region.texture_s, region.texture_t, region.texture_p, region.texture_q),
      m_texture_unit(unit),
      m_created(false) {}

CreateSprite::CreateSprite(const entityx::Entity target, const float x, const float y, const int16_t width, const int16_t height, const float texture_s, const float texture_t, const float texture_p, const float texture_q, const TextureUnit::Unit unit)
    : m_target(target),
      m_position(x, y, 0),
      m_size(width, height),
      m_texture_coordinate(texture_s, texture_t, texture_p, texture_q),
      m_texture_unit(unit),
      m_created(false) {}

bool CreateSprite::execute(const entityx::TimeDelta dt) {
    if (m_created) {
        return true;
    }

    m_target.assign<Position>(m_position);
    m_target.assign<Size>(m_size);
    m_target.assign<TextureCoordinate>(m_texture_coordinate);
    m_target.assign<TextureUnit>(m_texture_unit);
    m_target.assign<Tint>(255, 255, 255, 255);
    return m_created = true;
}
