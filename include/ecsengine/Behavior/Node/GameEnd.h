#ifndef GAME_END_H
#define GAME_END_H

#include <entityx/entityx.h>

#include "../Node.h"


class GameEnd final : public Node {
private:
    entityx::EventManager& m_events;

public:
    explicit GameEnd(entityx::EventManager& events);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<GameEnd> create(entityx::EventManager& events) {
        return std::make_unique<GameEnd>(events);
    }
};


#endif //GAME_END_H
