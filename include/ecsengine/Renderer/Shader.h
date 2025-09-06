#ifndef SHADER_H
#define SHADER_H

#include <string_view>

#include <glad/glad.h>


GLuint compileShader(GLenum type, std::string_view src);

void checkProgram(GLuint id);


#endif //SHADER_H
