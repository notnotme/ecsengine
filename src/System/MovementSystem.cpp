#include <ecsengine/System/MovementSystem.h>

#include <cmath>

#include <ecsengine/Component/Friction.h>
#include <ecsengine/Component/Gravity.h>
#include <ecsengine/Component/Velocity.h>
#include <ecsengine/Component/Position.h>
#include <ecsengine/Component/Rotation.h>


void MovementSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, const entityx::TimeDelta dt) {
    entities.entities_with_components<Velocity, Friction>().each([&](entityx::Entity entity, Velocity &velocity, Friction &friction) {
        velocity.x *= std::pow(friction.x, dt);
        if (std::abs(velocity.x) < EPSILON) {
            velocity.x = 0.0f;
        }

        velocity.y *= std::pow(friction.y, dt);
        if (std::abs(velocity.y) < EPSILON) {
            velocity.y = 0.0f;
        }

        velocity.r *= std::pow(friction.r, dt);
        if (std::abs(velocity.r) < EPSILON) {
            velocity.r = 0.0f;
        }
    });

    entities.entities_with_components<Gravity, Velocity>().each([&](entityx::Entity entity, const Gravity &gravity, Velocity &velocity) {
        velocity.x += gravity.x * dt;
        velocity.y += gravity.y * dt;
    });

    entities.entities_with_components<Position, Velocity>().each([&](entityx::Entity entity, Position &position, Velocity &velocity) {
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        if (auto rotation = entity.component<Rotation>()) {
            rotation->angle += velocity.r * dt;
        }
    });
}
