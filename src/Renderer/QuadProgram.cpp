#include <ecsengine/Renderer/QuadProgram.h>

#include <ecsengine/Renderer/Shader.h>


static constexpr auto VERTEX_SRC = R"text(
        #version 420 core
        precision lowp float;

        uniform ivec2 u_screen_size;
        uniform ivec2 u_quad_size;
        uniform vec4 u_tint;

        out vec2 v_texture;
        out vec4 v_tint;

        void main() {
            const vec2 tlut[4] = vec2[4] (
                ivec2(0.0, 0.0),
                ivec2(1.0, 0.0),
                ivec2(0.0, 1.0),
                ivec2(1.0, 1.0)
            );

            const vec2 size = vec2(u_quad_size) / vec2(u_screen_size);
            const vec2 plut[4] = vec2[4] (
                vec2(-size.x, -size.y),
                vec2( size.x, -size.y),
                vec2(-size.x,  size.y),
                vec2( size.x,  size.y)
            );

            v_texture = tlut[gl_VertexID];
            v_tint = u_tint;
            gl_Position = vec4(plut[gl_VertexID], 0.0, 1.0);
        }
    )text";

static constexpr auto FRAGMENT_SRC = R"text(
        #version 420 core
        precision lowp float;

        in vec2 v_texture;
        in vec4 v_tint;
        out vec4 o_color;

        layout (binding = 0) uniform sampler2D texture_slot_0;

        void main() {
            o_color = v_tint * texture(texture_slot_0, v_texture);
        }
    )text";

QuadProgram::QuadProgram()
    : m_vao(0),
      m_program(0),
      m_screen_size_uniform(-1),
      m_quad_size_uniform(-1),
      m_tint_uniform(-1) {}

void QuadProgram::create() {
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
    m_screen_size_uniform = glGetUniformLocation(m_program, "u_screen_size");
    m_quad_size_uniform = glGetUniformLocation(m_program, "u_quad_size");
    m_tint_uniform = glGetUniformLocation(m_program, "u_tint");

    // Needs to create and empty vertex array object
    glGenVertexArrays(1, &m_vao);
}

void QuadProgram::destroy() {
    // Delete the VAO and shader
    glDeleteVertexArrays(1, &m_vao);
    glDeleteProgram(m_program);

    m_vao = 0;
    m_program = 0;
    m_screen_size_uniform = -1;
    m_quad_size_uniform = -1;
    m_tint_uniform = -1;
}

void QuadProgram::setScreenSize(const int32_t width, const int32_t height) const {
    glUniform2i(m_screen_size_uniform, width, height);
}

void QuadProgram::setQuadSize(const int32_t width, const int32_t height) const {
    glUniform2i(m_quad_size_uniform, width, height);
}

void QuadProgram::setTint(const float r, const float g, const float b, const float a) const {
    glUniform4f(m_tint_uniform, r, g, b, a);
}

GLuint QuadProgram::getProgram() const {
    return m_program;
}

GLuint QuadProgram::getVAO() const {
    return m_vao;
}
