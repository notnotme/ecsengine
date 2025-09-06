#ifndef DELAY_H
#define DELAY_H

#include <entityx/entityx.h>

#include "../Node.h"


class Delay final : public Node {
private:
    float m_duration_ms;

public:
    explicit Delay(float durationMs);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<Delay> create(const float durationMs) {
        return std::make_unique<Delay>(durationMs);
    }
};


#endif //DELAY_H
