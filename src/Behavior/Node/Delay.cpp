#include <ecsengine/Behavior/Node/Delay.h>


Delay::Delay(const float durationMs)
    : m_duration_ms(durationMs) {}

bool Delay::execute(const entityx::TimeDelta dt) {
    if (m_duration_ms == 0) {
        return true;
    }

    m_duration_ms -= dt * 1000.0f;
    if (m_duration_ms < 0) {
        m_duration_ms = 0;
    }

    return m_duration_ms == 0;
}
