#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.h"
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

#endif // SHADER_PROGRAM_H
