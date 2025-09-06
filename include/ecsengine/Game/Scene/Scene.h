#ifndef SCENE_H
#define SCENE_H

#include <cstdint>

#include <entityx/entityx.h>
#include <glad/glad.h>


class Scene {
private:
    friend class Game;

    GLuint m_framebuffer;
    GLuint m_texture;
    int32_t m_scene_width;
    int32_t m_scene_height;

private:
    void create(int32_t sceneWidth, int32_t sceneHeight);
    void destroy();

protected:
    entityx::EventManager m_events;
    entityx::EntityManager m_entities;
    entityx::SystemManager m_systems;

public:
    Scene(const Scene &);
    Scene &operator=(const Scene &) = delete;
    explicit Scene();
    virtual ~Scene() = default;

public:
    void bindFramebuffer() const;
    GLuint getTexture() const;
};


#endif //SCENE_H
