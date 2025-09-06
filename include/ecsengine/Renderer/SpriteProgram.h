#ifndef SPRITE_PROGRAM_H
#define SPRITE_PROGRAM_H

#include <glad/glad.h>


class SpriteProgram final {
private:
    GLuint m_vao;
    GLuint m_program;
    GLint m_matrix_uniform;

public:
    SpriteProgram(const SpriteProgram &) = delete;
    SpriteProgram &operator=(const SpriteProgram &) = delete;
    explicit SpriteProgram();

public:
    void create();
    void destroy();

    void setMatrix(const float *matrix) const;
    [[nodiscard]] GLuint getProgram() const;
    [[nodiscard]] GLuint getVAO() const;

    [[nodiscard]] static GLuint createVertexBuffer(uint32_t capacity);
};


#endif //SPRITE_PROGRAM_H
