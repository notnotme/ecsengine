#include <ecsengine/System/BehaviorSystem.h>

#include <ecsengine/Event/BehaviorEnd.h>


BehaviorSystem::BehaviorSystem(std::unique_ptr<Node> behavior)
    : m_behavior(std::move(behavior)),
      m_succeed(false) {}

void BehaviorSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, const entityx::TimeDelta dt) {
    if (m_succeed) {
        return;
    }

    m_succeed = m_behavior->execute(dt);
    if (m_succeed) {
        events.emit<BehaviorEnd>();
    }
}
