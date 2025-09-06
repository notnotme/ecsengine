#include <ecsengine/Game/Scene/Scene.h>

#include <ecsengine/Renderer/RendererUtil.h>


Scene::Scene()
    : m_framebuffer(0),
      m_texture(0),
      m_scene_width(0),
      m_scene_height(0),
      m_entities(m_events),
      m_systems(m_entities, m_events) {
}

void Scene::create(const int32_t sceneWidth, const int32_t sceneHeight) {
    m_scene_width = sceneWidth;
    m_scene_height = sceneHeight;
    m_texture = createUint8Texture(sceneWidth, sceneHeight, 3, GL_CLAMP_TO_EDGE);
    m_framebuffer = createFramebuffer(GL_COLOR_ATTACHMENT0, m_texture);
}

void Scene::destroy() {
    glDeleteTextures(1, &m_texture);
    m_texture = 0;

    glDeleteFramebuffers(1, &m_framebuffer);
    m_framebuffer = 0;
}

void Scene::bindFramebuffer() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glViewport(0, 0, m_scene_width, m_scene_height);
    glScissor(0, 0, m_scene_width, m_scene_height);
}

GLuint Scene::getTexture() const {
    return m_texture;
}
