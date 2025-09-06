#ifndef FADE_OUT_H
#define FADE_OUT_H

#include <entityx/entityx.h>

#include "../Node.h"


class FadeOut final : public Node {
private:
    entityx::Entity m_target;
    float m_duration_ms;
    float m_value;

public:
    explicit FadeOut(entityx::Entity target, float durationMs);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<FadeOut> create(const entityx::Entity target, const float durationMs) {
        return std::make_unique<FadeOut>(target, durationMs);
    }
};


#endif //FADE_OUT_H
