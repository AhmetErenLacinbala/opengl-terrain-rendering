#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() : m_shaderObj(0) {}

Shader::~Shader() {
    if (m_shaderObj) {
        glDeleteShader(m_shaderObj);
    }
}

bool Shader::Load(GLenum shaderType, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening shader file: " << filename << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    const char* shaderSource = content.c_str();

    m_shaderObj = glCreateShader(shaderType);
    if (!m_shaderObj) {
        std::cerr << "Error creating shader of type: " << shaderType << std::endl;
        return false;
    }

    glShaderSource(m_shaderObj, 1, &shaderSource, NULL);
    glCompileShader(m_shaderObj);

    GLint success;
    glGetShaderiv(m_shaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(m_shaderObj, 1024, NULL, infoLog);
        std::cerr << "Error compiling shader from " << filename << ": " << infoLog << std::endl;
        return false;
    }

    return true;
}

GLuint Shader::GetObj() const {
    return m_shaderObj;
}
