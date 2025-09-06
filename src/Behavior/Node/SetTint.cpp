#include <ecsengine/Behavior/Node/SetTint.h>


SetTint::SetTint(const entityx::Entity target, const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha)
    : m_target(target),
      m_tint(red, green, blue, alpha),
      m_is_set(false) {}

bool SetTint::execute(const entityx::TimeDelta dt) {
    if (m_is_set) {
        return true;
    }

    m_target.replace<Tint>(m_tint);
    return m_is_set = true;
}
