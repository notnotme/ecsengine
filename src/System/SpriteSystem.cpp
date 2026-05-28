#include <ecsengine/System/SpriteSystem.h>

#include <cmath>
#include <execution>

#include <glad/glad.h>

#include <ecsengine/Component/Position.h>
#include <ecsengine/Component/Rotation.h>
#include <ecsengine/Component/Scale.h>
#include <ecsengine/Component/Size.h>
#include <ecsengine/Component/Tint.h>
#include <ecsengine/Component/TextureCoordinate.h>
#include <ecsengine/Component/TextureUnit.h>
#include <ecsengine/Renderer/SpriteVertex.h>


SpriteSystem::SpriteSystem(const SpriteProgram &spriteProgram, const GLuint vertexBuffer, const uint32_t bufferSize, const bool enableSort, const int32_t surfaceWidth, const int32_t surfaceHeight)
    : m_program(spriteProgram),
      m_vertex_buffer(vertexBuffer),
      m_capacity(bufferSize),
      m_sort_enabled(enableSort),
      m_surface_width(surfaceWidth),
      m_surface_height(surfaceHeight),
      m_orthogonal() {
    m_cache.reserve(bufferSize);
}

void SpriteSystem::configure(entityx::EntityManager &entities, entityx::EventManager &events) {
    // Initialize the orthogonal matrix
    constexpr auto left = 0.0f;
    constexpr auto top = 0.0f;
    constexpr auto near = 0.0f;
    constexpr auto far = 1.0f;
    const auto right = static_cast<float>(m_surface_width);
    const auto bottom = static_cast<float>(m_surface_height);
    // Calculate the new orthogonal matrice
    m_orthogonal[0] = 2.0f / (right - left);
    m_orthogonal[3] = -(right + left) / (right - left);
    m_orthogonal[5] = 2.0f / (top - bottom);
    m_orthogonal[7] = -(top + bottom) / (top - bottom);
    m_orthogonal[10] = -2.0f / (far - near);
    m_orthogonal[11] = -(far + near) / (far - near);
    m_orthogonal[15] = 1.0f;
}

void SpriteSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, const entityx::TimeDelta dt) {
    // Get a view of all entities we want to render
    const auto view = entities.entities_with_components<Position, Size, TextureUnit>();
    const auto sprite_count = static_cast<GLsizei>(std::distance(view.begin(), view.end()));

    if (m_cache.size() > m_capacity) {
        throw std::runtime_error("SpriteSystem buffer size is too small");
    }

    // Copy all entities into the cached Vector to be able to sort them by z_index and vectorize the copy to buffer loop
    m_cache.resize(sprite_count);
    std::copy(view.begin(), view.end(), m_cache.begin());

    if (m_sort_enabled) {
        // Eventually sort if needed
        std::sort(std::execution::par_unseq, m_cache.begin(), m_cache.end(),
                  [](entityx::Entity a, entityx::Entity b) {
                      const auto &a_position_z = a.component<Position>()->z_index;
                      const auto &b_position_z = b.component<Position>()->z_index;
                      return a_position_z < b_position_z;
                  });
    }

    // Calculate mapping size and map the buffer to local memory
    const auto total_map_size = static_cast<GLsizeiptr>(sprite_count * sizeof(SpriteVertex));

    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    const auto raw_buffer_data = glMapBufferRange(GL_ARRAY_BUFFER, 0, total_map_size,
                                                GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT |
                                                GL_MAP_FLUSH_EXPLICIT_BIT);

    // Copy all the sprites using a vectorized loop
    const auto buffer_data = static_cast<SpriteVertex*>(raw_buffer_data);
    std::for_each(std::execution::par_unseq, m_cache.begin(), m_cache.end(),
                  [&](entityx::Entity &entity) {
                      const auto index = std::distance(m_cache.data(), &entity);
                      auto &vertex = buffer_data[index];

                      const auto &position = entity.component<Position>();
                      vertex.translation_x = static_cast<int16_t>(std::round(position->x));
                      vertex.translation_y = static_cast<int16_t>(std::round(position->y));

                      const auto &size = entity.component<Size>();
                      if (const auto &scale = entity.component<Scale>()) {
                          const auto scaled_width = static_cast<float>(size->width) * scale->width;
                          const auto scaled_height = static_cast<float>(size->height) * scale->height;
                          vertex.width = static_cast<int16_t>(scaled_width);
                          vertex.height = static_cast<int16_t>(scaled_height);
                      } else {
                          vertex.width = size->width;
                          vertex.height = size->height;
                      }

                      const auto &texture_slot = entity.component<TextureUnit>();
                      vertex.slot = texture_slot->unit;

                      if (texture_slot->unit != TextureUnit::NONE) {
                          if (const auto &texture_coord = entity.component<TextureCoordinate>()) {
                              vertex.texture_s = static_cast<int16_t>(std::round(texture_coord->s * UV_SCALE));
                              vertex.texture_t = static_cast<int16_t>(std::round(texture_coord->t * UV_SCALE));
                              vertex.texture_p = static_cast<int16_t>(std::round(texture_coord->p * UV_SCALE));
                              vertex.texture_q = static_cast<int16_t>(std::round(texture_coord->q * UV_SCALE));
                          } else {
                              vertex.texture_s = 0;
                              vertex.texture_t = 0;
                              vertex.texture_p = UV_SCALE;
                              vertex.texture_q = UV_SCALE;
                          }
                      }

                      if (const auto &tint = entity.component<Tint>()) {
                          vertex.tint_r = tint->red;
                          vertex.tint_g = tint->green;
                          vertex.tint_b = tint->blue;
                          vertex.tint_a = tint->alpha;
                      } else {
                          vertex.tint_r = 255;
                          vertex.tint_g = 255;
                          vertex.tint_b = 255;
                          vertex.tint_a = 255;
                      }

                      // FIXME: Use M_PIf when available (using old toolchain with the Nintendo Switch)
                      constexpr auto m_pif = static_cast<float>(M_PI);
                      if (const auto &rotation = entity.component<Rotation>()) {
                          vertex.rotation = rotation->angle * m_pif / 180.0f;
                      } else {
                          vertex.rotation = 0.0f;
                      }
                  });

    // Flush and unmap the sprites buffer
    glFlushMappedBufferRange(GL_ARRAY_BUFFER, 0, total_map_size);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    // Bind SpriteProgram and set projection matrix
    glUseProgram(m_program.getProgram());
    m_program.setMatrix(m_orthogonal.data());

    // Finally bind the VAO, set the buffer, and render all sprites
    glBindVertexArray(m_program.getVAO());
    glBindVertexBuffer(0, m_vertex_buffer, 0, sizeof(SpriteVertex));
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, sprite_count);
}
