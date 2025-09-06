#ifndef BEHAVIOR_SYSTEM_H
#define BEHAVIOR_SYSTEM_H

#include <entityx/System.h>

#include "../Behavior/Node.h"


class BehaviorSystem final : public entityx::System<BehaviorSystem> {
private:
    std::unique_ptr<Node> m_behavior;
    bool m_succeed;

public:
    explicit BehaviorSystem(std::unique_ptr<Node> behavior);

public:
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};


#endif //BEHAVIOR_SYSTEM_H
