#ifndef WAIT_PLAYER_H
#define WAIT_PLAYER_H

#include <memory>

#include <entityx/entityx.h>

#include "../../Audio/AudioPlayer.h"
#include "../Node.h"


class WaitPlayer final : public Node {
private:
    std::shared_ptr<AudioPlayer> m_player;
    int32_t m_pattern;
    int32_t m_order;
    int32_t m_row;
    bool m_reached;

public:
    explicit WaitPlayer(const std::shared_ptr<AudioPlayer> &player, int32_t pattern, int32_t order, int32_t row);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<WaitPlayer> create(const std::shared_ptr<AudioPlayer>& player, const int32_t pattern, const int32_t order, int32_t const row) {
        return std::make_unique<WaitPlayer>(player, pattern, order, row);
    }
};


#endif //WAIT_PLAYER_H
