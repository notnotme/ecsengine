#include <ecsengine/Behavior/Node/BindTexture.h>


BindTexture::BindTexture(const GLuint texture, const TextureUnit::Unit unit)
    : m_texture(texture),
      m_unit(unit) {
    assert(m_unit != TextureUnit::NONE);
}

bool BindTexture::execute(const entityx::TimeDelta dt) {
    glActiveTexture(GL_TEXTURE0 + m_unit);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    return true;
}
