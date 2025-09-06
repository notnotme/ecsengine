#ifndef QUAD_PROGRAM_H
#define QUAD_PROGRAM_H

#include <cstdint>

#include <glad/glad.h>


class QuadProgram final {
private:
    GLuint m_vao;
    GLuint m_program;
    GLint m_screen_size_uniform;
    GLint m_quad_size_uniform;
    GLint m_tint_uniform;

public:
    QuadProgram(const QuadProgram &) = delete;
    QuadProgram &operator=(const QuadProgram &) = delete;
    explicit QuadProgram();

public:
    void create();
    void destroy();

    void setScreenSize(int32_t width, int32_t height) const;
    void setQuadSize(int32_t width, int32_t height) const;
    void setTint(float r, float g, float b, float a) const;

    [[nodiscard]] GLuint getProgram() const;
    [[nodiscard]] GLuint getVAO() const;
};

#endif //QUAD_PROGRAM_H
