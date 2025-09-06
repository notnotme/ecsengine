#ifndef TRANSITION_TO_H
#define TRANSITION_TO_H

#include <cstdint>

#include <entityx/entityx.h>

#include "../Node.h"


class TransitionTo final : public Node {
private:
    entityx::EventManager& m_events;
    uint32_t m_scene_id;
    uint32_t m_transition_id;
    bool m_done;

public:
    explicit TransitionTo(entityx::EventManager& events, uint32_t scene_id, uint32_t transition_id);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<TransitionTo> create(entityx::EventManager& events, const uint32_t scene_id, const uint32_t transition_id) {
        return std::make_unique<TransitionTo>(events, scene_id, transition_id);
    }
};


#endif //TRANSITION_TO_H
