#include <ecsengine/Behavior/Node/ClearBuffer.h>

#include <glad/glad.h>


ClearBuffer::ClearBuffer(const std::array<float, 4>& color)
    : m_color(color) {}

bool ClearBuffer::execute(const entityx::TimeDelta dt) {
    glClearBufferfv(GL_COLOR, 0, m_color.data());
    return true;
}
