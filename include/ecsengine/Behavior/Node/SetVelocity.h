#ifndef SET_VELOCITY_H
#define SET_VELOCITY_H

#include <entityx/entityx.h>

#include "../Node.h"
#include "../../Component/Velocity.h"


class SetVelocity final : public Node {
private:
    entityx::Entity m_target;
    Velocity m_velocity;
    bool m_is_set;

public:
    explicit SetVelocity(entityx::Entity target, float x, float y, float r);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<SetVelocity> create(const entityx::Entity target, const float x, const float y, const float r) {
        return std::make_unique<SetVelocity>(target, x, y, r);
    }
};


#endif //SET_VELOCITY_H
