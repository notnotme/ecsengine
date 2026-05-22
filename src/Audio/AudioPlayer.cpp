#include <ecsengine/Audio/AudioPlayer.h>

#include <fstream>


AudioPlayer::AudioPlayer(entityx::EventManager& gameEvents)
    : m_events(gameEvents),
      m_audio_spec(),
      m_audio_device(0),
      m_music_pattern(0),
      m_music_order(0),
      m_music_row(0),
      m_module(nullptr) {}

void AudioPlayer::create() {
    SDL_AudioSpec wanted_audio_spec;
    wanted_audio_spec.callback = audioCallback;
    wanted_audio_spec.userdata = this;
    wanted_audio_spec.samples = DEFAULT_BUFFER_SIZE;
    wanted_audio_spec.channels = 2;
    wanted_audio_spec.format = AUDIO_F32;
    wanted_audio_spec.freq = DEFAULT_FREQUENCY;

    m_audio_device = SDL_OpenAudioDevice(nullptr, 0, &wanted_audio_spec, &m_audio_spec, 0);
    if (m_audio_device == 0) {
        throw std::runtime_error("Unable to open audio device");
    }

    SDL_PauseAudioDevice(m_audio_device, true);
}

void AudioPlayer::destroy() {
    SDL_PauseAudioDevice(m_audio_device, true);
    SDL_ClearQueuedAudio(m_audio_device);
    SDL_CloseAudioDevice(m_audio_device);

    m_audio_spec = SDL_AudioSpec();
    m_audio_device = 0;
    m_music_pattern.store(0, std::memory_order_relaxed);
    m_music_order.store(0, std::memory_order_relaxed);
    m_music_row.store(0, std::memory_order_relaxed);
    m_module = nullptr;
}

void AudioPlayer::audioCallback(void *userdata, Uint8 *stream, const int32_t len) {
    const auto thiz = static_cast<AudioPlayer*>(userdata);
    const auto audio_spec = thiz->m_audio_spec;
    const auto module = thiz->m_module.get();
    const auto size = static_cast<size_t>(len >> 3);

    memset(stream, 0, len >> 2);
    auto stream_offset = reinterpret_cast<float*>(stream);
    if (const auto reads = module->read_interleaved_stereo(audio_spec.freq, size, stream_offset); reads != size) {
        stream_offset = reinterpret_cast<float*>(&stream[reads]);
        module->read_interleaved_stereo(audio_spec.freq, size - reads, stream_offset);
    }

    const auto pattern = module->get_current_pattern();
    const auto order = module->get_current_order();
    const auto row = module->get_current_row();
    thiz->tick(pattern, order, row);
}

void AudioPlayer::loadMusic(const std::string_view path) {
    SDL_PauseAudioDevice(m_audio_device, true);
    SDL_ClearQueuedAudio(m_audio_device);

    auto file = std::ifstream(path.data(), std::ios::binary);
    m_module = std::make_unique<openmpt::module>(file);
    m_module->ctl_set_boolean("render.resampler.emulate_amiga", true);
    m_module->ctl_set_text("play.at_end", "continue");
    file.close();
}

void AudioPlayer::playMusic() const {
    SDL_PauseAudioDevice(m_audio_device, false);
}

void AudioPlayer::pauseMusic() const {
    SDL_PauseAudioDevice(m_audio_device, true);
}

void AudioPlayer::stopMusic() {
    SDL_PauseAudioDevice(m_audio_device, true);
    SDL_ClearQueuedAudio(m_audio_device);
    m_music_pattern.store(0, std::memory_order_relaxed);
    m_music_order.store(0, std::memory_order_relaxed);
    m_music_row.store(0, std::memory_order_relaxed);
}

int32_t AudioPlayer::getPattern() const {
    return m_music_pattern.load(std::memory_order_relaxed);
}

int32_t AudioPlayer::getOrder() const {
    return m_music_order.load(std::memory_order_relaxed);
}

int32_t AudioPlayer::getRow() const {
    return m_music_row.load(std::memory_order_relaxed);
}

void AudioPlayer::tick(const int32_t pattern, const int32_t order, const int32_t row) {
    auto emit_event = false;
    if (pattern != m_music_pattern.load(std::memory_order_relaxed)) {
        m_music_pattern.store(pattern, std::memory_order_relaxed);
        emit_event = true;
    }

    if (order != m_music_order.load(std::memory_order_relaxed)) {
        m_music_order.store(order, std::memory_order_relaxed);
        emit_event = true;
    }

    if (row != m_music_row.load(std::memory_order_relaxed)) {
        m_music_row.store(row, std::memory_order_relaxed);
        emit_event = true;
    }

    if (emit_event) {
        std::lock_guard lock(m_event_mutex);
        m_event_queue.emplace(pattern, order, row);
    }
}

