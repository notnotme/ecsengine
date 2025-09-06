#ifndef SPRITE_SYSTEM_H
#define SPRITE_SYSTEM_H

#include <array>
#include <cstdint>

#include <entityx/System.h>

#include "../Renderer/SpriteProgram.h"


class SpriteSystem final : public entityx::System<SpriteSystem> {
private:
    const SpriteProgram& m_program;
    const GLuint m_vertex_buffer;
    const uint32_t m_capacity;
    const bool m_sort_enabled;
    const int32_t m_surface_width;
    const int32_t m_surface_height;

    std::array<float, 16> m_orthogonal;

public:
    explicit SpriteSystem(const SpriteProgram &spriteProgram, GLuint vertexBuffer, uint32_t bufferSize, bool enableSort, int32_t surfaceWidth, int32_t surfaceHeight);

public:
    void configure(entityx::EntityManager &entities, entityx::EventManager &events) override;
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};


#endif //SPRITE_SYSTEM_H
