#include <ecsengine/Renderer/SpriteProgram.h>

#include <cstddef>

#include <ecsengine/Renderer/Shader.h>
#include <ecsengine/Renderer/SpriteVertex.h>


static constexpr auto VERTEX_SRC = R"text(
    #version 420 core
    precision lowp float;

    layout (location = 0) in vec2 a_size;
    layout (location = 1) in vec4 a_texture;
    layout (location = 2) in vec4 a_tint;
    layout (location = 3) in float a_rotation;
    layout (location = 4) in vec2 a_translation;
    layout (location = 5) in float a_slot;
    uniform mat4 u_matrix;

    out vec4 v_tint;
    out vec2 v_texture;
    flat out int v_slot;

    void main() {
        const ivec2 tlut[4] = ivec2[4] (
            ivec2(2, 1),
            ivec2(0, 1),
            ivec2(2, 3),
            ivec2(0, 3)
        );

        const vec2 plut[4] = vec2[4] (
            vec2( 0.5, -0.5),
            vec2(-0.5, -0.5),
            vec2( 0.5,  0.5),
            vec2(-0.5,  0.5)
        );

        mat3 rotate_mat = mat3 (
            cos(a_rotation), -sin(a_rotation), 0.0,
            sin(a_rotation), cos(a_rotation), 0.0,
            0.0, 0.0, 1.0
        );

        mat3 translate_mat = mat3 (
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            a_translation.x, a_translation.y, 0.0
        );

        vec3 transformed = translate_mat * rotate_mat * vec3(plut[gl_VertexID] * a_size, 1.0);
        gl_Position = u_matrix * vec4(transformed, 1.0);

        // This value equals SpriteSystem::UV_SCALE
        const float UV_SCALE = 256.0f;

        v_texture = vec2(a_texture[tlut[gl_VertexID].x], a_texture[tlut[gl_VertexID].y]) / UV_SCALE;
        v_tint = a_tint;
        v_slot = int(a_slot);
    }
)text";

static constexpr auto FRAGMENT_SRC = R"text(
    #version 420 core
    precision lowp float;

    in vec4 v_tint;
    in vec2 v_texture;
    flat in int v_slot;

    out vec4 o_color;

    layout (binding = 0) uniform sampler2D texture_slot_0;
    layout (binding = 1) uniform sampler2D texture_slot_1;
    layout (binding = 2) uniform sampler2D texture_slot_2;
    layout (binding = 3) uniform sampler2D texture_slot_3;
    layout (binding = 4) uniform sampler2D texture_slot_4;
    layout (binding = 5) uniform sampler2D texture_slot_5;
    layout (binding = 6) uniform sampler2D texture_slot_6;
    layout (binding = 7) uniform sampler2D texture_slot_7;

    void main() {
        float texel_alpha = 0.0;
        switch (v_slot) {
        case 0: o_color = v_tint * texture(texture_slot_0, v_texture); break;
        case 1: o_color = v_tint * texture(texture_slot_1, v_texture); break;
        case 2: o_color = v_tint * texture(texture_slot_2, v_texture); break;
        case 3: o_color = v_tint * texture(texture_slot_3, v_texture); break;
        case 4: o_color = v_tint * texture(texture_slot_4, v_texture); break;
        case 5: o_color = v_tint * texture(texture_slot_5, v_texture); break;
        case 6:
            texel_alpha = texture(texture_slot_6, v_texture).r * v_tint.a;
            o_color = vec4(v_tint.rgb, texel_alpha);
        break;
        case 7:
            texel_alpha = texture(texture_slot_7, v_texture).r * v_tint.a;
            o_color = vec4(v_tint.rgb, texel_alpha);
        break;
        default: o_color = v_tint;
        }
    }
)text";

SpriteProgram::SpriteProgram()
    : m_vao(0),
      m_program(0),
      m_matrix_uniform(-1) {}

void SpriteProgram::create() {
    // Create the fragment and vertex shader
    const auto fragment_shader = compileShader(GL_FRAGMENT_SHADER, FRAGMENT_SRC);
    const auto vertex_shader = compileShader(GL_VERTEX_SHADER, VERTEX_SRC);
    m_program = glCreateProgram();

    // Link the shaders to the program
    glAttachShader(m_program, fragment_shader);
    glAttachShader(m_program, vertex_shader);
    glLinkProgram(m_program);

    // Delete the shaders and check the program
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    checkProgram(m_program);

    // Get uniforms
    m_matrix_uniform = glGetUniformLocation(m_program, "u_matrix");

    // Create the vertex array object
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glEnableVertexAttribArray(0);
    glVertexAttribFormat(0, 2, GL_SHORT, GL_FALSE, offsetof(SpriteVertex, width));
    glVertexAttribBinding(0, 0);
    glVertexBindingDivisor(0, 1);

    glEnableVertexAttribArray(1);
    glVertexAttribFormat(1, 4, GL_SHORT, GL_FALSE, offsetof(SpriteVertex, texture_s));
    glVertexAttribBinding(1, 0);
    glVertexBindingDivisor(1, 1);

    glEnableVertexAttribArray(2);
    glVertexAttribFormat(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(SpriteVertex, tint_r));
    glVertexAttribBinding(2, 0);
    glVertexBindingDivisor(2, 1);

    glEnableVertexAttribArray(3);
    glVertexAttribFormat(3, 1, GL_FLOAT, GL_FALSE, offsetof(SpriteVertex, rotation));
    glVertexAttribBinding(3, 0);
    glVertexBindingDivisor(3, 1);

    glEnableVertexAttribArray(4);
    glVertexAttribFormat(4, 2, GL_FLOAT, GL_FALSE, offsetof(SpriteVertex, translation_x));
    glVertexAttribBinding(4, 0);
    glVertexBindingDivisor(4, 1);

    glEnableVertexAttribArray(5);
    glVertexAttribFormat(5, 1, GL_UNSIGNED_BYTE, GL_FALSE, offsetof(SpriteVertex, slot));
    glVertexAttribBinding(5, 0);
    glVertexBindingDivisor(5, 1);
}

void SpriteProgram::destroy() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteProgram(m_program);

    m_vao = 0;
    m_program = 0;
    m_matrix_uniform = -1;
}

void SpriteProgram::setMatrix(const float* matrix) const {
    glUniformMatrix4fv(m_matrix_uniform, 1, GL_TRUE, matrix);
}

GLuint SpriteProgram::getProgram() const {
    return m_program;
}

GLuint SpriteProgram::getVAO() const {
    return m_vao;
}

GLuint SpriteProgram::createVertexBuffer(const uint32_t capacity) {
    const auto buffer_size = static_cast<GLsizeiptr>(sizeof(SpriteVertex) * capacity);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_DYNAMIC_DRAW);

    return buffer;
}
