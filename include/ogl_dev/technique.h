#ifndef TECHNIQUE_H
#define TECHNIQUE_H

#include <GL/glew.h>
#include <list>
#include "Shader.h"

class Technique {
public:
    Technique();
    virtual ~Technique();
    
    bool Init();
    bool AddShader(GLenum ShaderType, const char* pFilename);
    bool Finalize();
    void Enable();
    GLint GetUniformLocation(const char* pUniformName);

private:
    std::list<Shader> m_shaders;
    GLuint m_shaderProg;
};

#endif  // TECHNIQUE_H
