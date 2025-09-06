#ifndef FADE_IN_H
#define FADE_IN_H

#include <entityx/entityx.h>

#include "../Node.h"


class FadeIn final : public Node {
private:
    entityx::Entity m_target;
    float m_duration_ms;
    float m_value;

public:
    explicit FadeIn(entityx::Entity target, float durationMs);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<FadeIn> create(const entityx::Entity target, const float durationMs) {
        return std::make_unique<FadeIn>(target, durationMs);
    }
};


#endif //FADE_IN_H
