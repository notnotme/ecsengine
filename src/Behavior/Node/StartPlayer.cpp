#include <ecsengine/Behavior/Node/StartPlayer.h>


StartPlayer::StartPlayer(const std::shared_ptr<AudioPlayer> &player)
    : m_player(player),
      m_started(false) {}

bool StartPlayer::execute(const entityx::TimeDelta dt) {
    if (m_started) {
        return true;
    }

    m_player->playMusic();
    return m_started = true;
}
