#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader();
    ~Shader();

    bool Load(GLenum shaderType, const std::string& filename);
    GLuint GetObj() const;

private:
    GLuint m_shaderObj;
};

#endif // SHADER_H
