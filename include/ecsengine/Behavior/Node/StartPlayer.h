#ifndef START_PLAYER_H
#define START_PLAYER_H

#include <memory>

#include <entityx/entityx.h>

#include "../../Audio/AudioPlayer.h"
#include "../Node.h"


class StartPlayer final : public Node {
private:
    std::shared_ptr<AudioPlayer> m_player;
    bool m_started;

public:
    explicit StartPlayer(const std::shared_ptr<AudioPlayer> &player);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<StartPlayer> create(const std::shared_ptr<AudioPlayer>& player) {
        return std::make_unique<StartPlayer>(player);
    }
};


#endif //START_PLAYER_H
