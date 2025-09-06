#include <ecsengine/Behavior/Node/FadeIn.h>

#include <cmath>

#include <ecsengine/Component/Tint.h>


FadeIn::FadeIn(const entityx::Entity target, const float durationMs)
    : m_target(target),
      m_duration_ms(durationMs),
      m_value(0) {}

bool FadeIn::execute(const entityx::TimeDelta dt) {
    if (m_value == 255) {
        return true;
    }

    const auto step = 255.0f / (m_duration_ms / 1000.0f) * dt;
    m_value += step;
    if (m_value > 255.0f) {
        m_value = 255.0f;
    }

    const auto color_threshold = static_cast<uint8_t>(std::round(m_value));
    if (auto tint = m_target.component<Tint>(); tint->alpha < color_threshold) {
        tint->alpha = color_threshold;
    }

    return m_value == 255;
}
