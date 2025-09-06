#include <ecsengine/Behavior/Node/TransitionTo.h>

#include <ecsengine/Event/SceneTransition.h>


TransitionTo::TransitionTo(entityx::EventManager& events, const uint32_t scene_id, const uint32_t transition_id)
    : m_events(events),
      m_scene_id(scene_id),
      m_transition_id(transition_id),
      m_done(false) {}

bool TransitionTo::execute(const entityx::TimeDelta dt) {
    if (m_done) {
        return true;
    }

    m_events.emit<SceneTransition>(m_scene_id, m_transition_id);
    return m_done = true;
}
