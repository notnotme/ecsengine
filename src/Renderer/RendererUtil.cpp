#include <ecsengine/Renderer/RendererUtil.h>

#include <stdexcept>


GLuint createUint8TextureInternal(const int32_t width, const int32_t height, const int32_t bpp) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    switch (bpp) {
        case 1:
            glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8, width, height);
        break;
        case 3:
            glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
        break;
        case 4:
            glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
        break;
        default:
            throw std::runtime_error("Unsupported texture format");
    }

    return texture;
}

GLuint createFramebuffer(const GLenum attachment, const GLuint texture) {
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture, 0);
    return framebuffer;
}

GLuint createUint8Texture(const int32_t width, const int32_t height, const int32_t bpp) {
    const auto texture = createUint8TextureInternal(width, height, bpp);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return texture;
}

GLuint createUint8Texture(const int32_t width, const int32_t height, const GLint bpp, const GLint repeat) {
    const auto texture = createUint8TextureInternal(width, height, bpp);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return texture;
}
