#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <atomic>
#include <cstdint>
#include <memory>
#include <queue>
#include <mutex>
#include <string_view>

#include <entityx/entityx.h>
#include <libopenmpt/libopenmpt.hpp>
#include <SDL.h>

#include "../Event/MusicTick.h"


class AudioPlayer final {
private:
    friend class AssetManager;
    friend class AudioSystem;

    static constexpr int32_t DEFAULT_FREQUENCY = 48000;
    static constexpr uint16_t DEFAULT_BUFFER_SIZE = 1024;

    entityx::EventManager& m_events;
    SDL_AudioSpec m_audio_spec;
    SDL_AudioDeviceID m_audio_device;
    std::atomic<int32_t> m_music_pattern;
    std::atomic<int32_t> m_music_order;
    std::atomic<int32_t> m_music_row;
    std::queue<MusicTick> m_event_queue;
    std::mutex m_event_mutex;
    std::unique_ptr<openmpt::module> m_module;

private:
    static void audioCallback(void* userdata, Uint8* stream, int32_t len);
    void create();
    void destroy();
    void tick(int32_t pattern, int32_t order, int32_t row);

public:
    AudioPlayer(const AudioPlayer &) = delete;
    AudioPlayer &operator=(const AudioPlayer &) = delete;
    explicit AudioPlayer(entityx::EventManager& gameEvents);

public:
    void loadMusic(std::string_view path);
    void playMusic() const;
    void pauseMusic() const;
    void stopMusic();

    [[nodiscard]] int32_t getPattern() const;
    [[nodiscard]] int32_t getOrder() const;
    [[nodiscard]] int32_t getRow() const;
};


#endif //AUDIO_PLAYER_H
