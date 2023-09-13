#include <shader.h>
#include <vector>
#include <iostream>

class ShaderProgram {
private:
    GLuint m_programObj;
    std::vector<GLuint> m_attachedShaders;

public:
    ShaderProgram();
    ~ShaderProgram();

    bool AttachShader(const Shader& shader);
    bool Link();
    void Use() const;
    GLuint GetID() const;
};

ShaderProgram::ShaderProgram() {
    m_programObj = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    for (GLuint shader : m_attachedShaders) {
        glDetachShader(m_programObj, shader);
    }
    glDeleteProgram(m_programObj);
}

bool ShaderProgram::AttachShader(const Shader& shader) {
    glAttachShader(m_programObj, shader.GetObj());
    m_attachedShaders.push_back(shader.GetObj());
    return true;  // You can add error checks if needed
}

bool ShaderProgram::Link() {
    glLinkProgram(m_programObj);

    GLint success;
    glGetProgramiv(m_programObj, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(m_programObj, 1024, NULL, infoLog);
        std::cerr << "Error linking shader program: " << infoLog << std::endl;
        return false;
    }
    return true;
}

void ShaderProgram::Use() const {
    glUseProgram(m_programObj);
}

GLuint ShaderProgram::GetID() const {
    return m_programObj;
}
