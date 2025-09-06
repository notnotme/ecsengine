#include <ecsengine/Behavior/Node/GameEnd.h>

#include <ecsengine/Event/ExitGame.h>


GameEnd::GameEnd(entityx::EventManager& events)
    : m_events(events) {}

bool GameEnd::execute(const entityx::TimeDelta dt) {
    m_events.emit<ExitGame>();
    return true;
}
