#include <ecsengine/Behavior/Node/SetFriction.h>


SetFriction::SetFriction(const entityx::Entity target, const float x, const float y, const float r)
    : m_target(target),
      m_friction(x, y, r),
      m_is_set(false) {}

bool SetFriction::execute(const entityx::TimeDelta dt) {
    if (m_is_set) {
        return true;
    }

    m_target.replace<Friction>(m_friction);
    return m_is_set = true;
}
