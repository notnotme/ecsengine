#include <ecsengine/Asset/Texture/TextureAsset.h>


TextureAsset::TextureAsset()
    : m_texture(0) {}

GLuint TextureAsset::getTexture() const {
  return m_texture;
}

