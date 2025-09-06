#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <entityx/System.h>


class MovementSystem final : public entityx::System<MovementSystem> {
public:
    explicit MovementSystem() = default;

public:
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};


#endif //MOVEMENT_SYSTEM_H
