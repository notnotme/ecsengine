#include <ecsengine/Behavior/Node/SetVelocity.h>


SetVelocity::SetVelocity(const entityx::Entity target, const float x, const float y, const float r)
    : m_target(target),
      m_velocity(x, y, r),
      m_is_set(false) {}

bool SetVelocity::execute(const entityx::TimeDelta dt) {
    if (m_is_set) {
        return true;
    }

    m_target.replace<Velocity>(m_velocity);
    return m_is_set = true;
}
