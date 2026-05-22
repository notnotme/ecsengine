#include <ecsengine/System/AudioSystem.h>

#include <queue>
#include <mutex>

#include "ecsengine/Event/MusicTick.h"


AudioSystem::AudioSystem(std::shared_ptr<AudioPlayer> player)
    : m_player(std::move(player)) {}

void AudioSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, const entityx::TimeDelta dt) {
    std::queue<MusicTick> local_queue;
    {
        std::lock_guard lock(m_player->m_event_mutex);
        if (!m_player->m_event_queue.empty()) {
            local_queue = std::move(m_player->m_event_queue);
            m_player->m_event_queue = std::queue<MusicTick>();
        }
    }

    while (!local_queue.empty()) {
        events.emit(local_queue.front());
        local_queue.pop();
    }
}
