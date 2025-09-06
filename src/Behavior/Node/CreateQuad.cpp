#include <ecsengine/Behavior/Node/CreateQuad.h>

#include <ecsengine/Component/TextureUnit.h>


CreateQuad::CreateQuad(const entityx::Entity target, const float x, const float y, const int16_t width, const int16_t height, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
    : m_target(target),
      m_position(x, y, 0),
      m_size(width, height),
      m_tint(r, g, b, a),
      m_created(false) {}

bool CreateQuad::execute(const entityx::TimeDelta dt) {
    if (m_created) {
        return true;
    }

    m_target.assign<Position>(m_position);
    m_target.assign<Size>(m_size);
    m_target.assign<Tint>(m_tint);
    m_target.assign<TextureUnit>(TextureUnit::NONE);
    return m_created = true;
}
