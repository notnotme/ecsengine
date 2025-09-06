#ifndef SET_FRICTION_H
#define SET_FRICTION_H

#include <entityx/entityx.h>

#include "../Node.h"
#include "../../Component/Friction.h"


class SetFriction final : public Node {
private:
    entityx::Entity m_target;
    Friction m_friction;
    bool m_is_set;

public:
    explicit SetFriction(entityx::Entity target, float x, float y, float r);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<SetFriction> create(const entityx::Entity target, const float x, const float y, const float r) {
        return std::make_unique<SetFriction>(target, x, y, r);
    }
};


#endif //SET_FRICTION_H
