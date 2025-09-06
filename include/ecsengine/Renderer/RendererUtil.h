#ifndef RENDERER_UTIL_H
#define RENDERER_UTIL_H

#include <cstdint>

#include <glad/glad.h>


[[nodiscard]] GLuint createFramebuffer(GLenum attachment, GLuint texture);

[[nodiscard]] GLuint createUint8Texture(int32_t width, int32_t height, int32_t bpp);

[[nodiscard]] GLuint createUint8Texture(int32_t width, int32_t height, int32_t bpp, GLint repeat);


#endif //RENDERER_UTIL_H
