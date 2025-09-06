#include <ecsengine/Asset/Texture/TextureLoadable.h>

#include <format>
#include <memory>
#include <stdexcept>

#include <SDL_image.h>

#include <ecsengine/Renderer/RendererUtil.h>


void TextureLoadable::load(const std::string_view path) {
    const auto image = IMG_Load(path.data());
    if (!image) {
        throw std::runtime_error("Failed to load image: " + std::string(IMG_GetError()));
    }

    GLenum format;
    switch (image->format->BytesPerPixel) {
        case 1:
            format = GL_R8;
        break;
        case 3:
            format = GL_RGB;
        break;
        case 4:
            format = GL_RGBA;
        break;
        default:
            throw std::runtime_error("Unsupported image format: " + std::format("0x{:x}", image->format->format));
    }

    m_texture = createUint8Texture(image->w, image->h, image->format->BytesPerPixel);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->w, image->h, format, GL_UNSIGNED_BYTE, image->pixels);

    SDL_FreeSurface(image);
}

void TextureLoadable::unload() {
    glDeleteTextures(1, &m_texture);
    m_texture = 0;
}
