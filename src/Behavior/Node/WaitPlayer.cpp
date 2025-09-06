#include <ecsengine/Behavior/Node/WaitPlayer.h>


WaitPlayer::WaitPlayer(const std::shared_ptr<AudioPlayer> &player, const int32_t pattern, const int32_t order, int32_t const row)
    : m_player(player),
      m_pattern(pattern),
      m_order(order),
      m_row(row),
      m_reached(false) {}

bool WaitPlayer::execute(const entityx::TimeDelta dt) {
    if (m_reached) {
        return true;
    }

    const auto pattern = m_player->getPattern();
    const auto order = m_player->getOrder();
    const auto row = m_player->getRow();

    // std::cout << pattern << " " << order << " " << row << std::endl;

    return m_reached = pattern == m_pattern && order == m_order && row == m_row;
}
