#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <entityx/System.h>


class MovementSystem final : public entityx::System<MovementSystem> {
private:
    static constexpr float EPSILON = 0.001f;

public:
    MovementSystem(const MovementSystem &) = delete;
    MovementSystem &operator=(const MovementSystem &) = delete;
    explicit MovementSystem() = default;

public:
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};


#endif //MOVEMENT_SYSTEM_H
