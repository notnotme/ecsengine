#include <ecsengine/Behavior/Node/SetTextureUnit.h>


SetTextureUnit::SetTextureUnit(const entityx::Entity target, const TextureUnit::Unit unit)
    : m_target(target),
      m_unit(unit),
      m_is_set(false) {}

bool SetTextureUnit::execute(const entityx::TimeDelta dt) {
    if (m_is_set) {
        return true;
    }

    m_target.replace<TextureUnit>(m_unit);
    return m_is_set = true;
}
