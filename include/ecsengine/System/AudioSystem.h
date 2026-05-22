#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include <entityx/System.h>

#include "../Audio/AudioPlayer.h"


class AudioSystem final : public entityx::System<AudioSystem> {
private:
    std::shared_ptr<AudioPlayer> m_player;

public:
    AudioSystem(const AudioSystem &) = delete;
    AudioSystem &operator=(const AudioSystem &) = delete;
    explicit AudioSystem(std::shared_ptr<AudioPlayer> player);

public:
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};


#endif //AUDIO_SYSTEM_H
