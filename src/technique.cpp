#include <stdio.h>
#include <string.h>

#include <ogl_dev/ogldev_util.h>
#include <ogl_dev/technique.h>

Technique::Technique()
{
    m_shaderProg = 0;
}


Technique::~Technique() {
    if (m_shaderProg != 0) {
        glDeleteProgram(m_shaderProg);
        m_shaderProg = 0;
    }
}


bool Technique::Init()
{
    m_shaderProg = glCreateProgram();

    if (m_shaderProg == 0) {
        fprintf(stderr, "Error creating shader program\n");
        return false;
    }

    return true;
}

bool Technique::AddShader(GLenum ShaderType, const char* pFilename) {
    Shader shader;
    if (!shader.Load(ShaderType, pFilename)) {
        return false;
    }
    m_shaders.push_back(shader);
    glAttachShader(m_shaderProg, shader.GetObj());
    return true;
}


// After all the shaders have been added to the program call this function
// to link and validate the program.
bool Technique::Finalize()
{
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(m_shaderProg);

    glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &Success);
        if (Success == 0) {
                glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
                fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        return false;
        }

    glValidateProgram(m_shaderProg);
    glGetProgramiv(m_shaderProg, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
    }

    for (ShaderObjList::iterator it = m_shaderObjList.begin() ; it != m_shaderObjList.end() ; it++) {
        glDeleteShader(*it);
    }

    m_shaderObjList.clear();

    return GLCheckError();
}


void Technique::Enable()
{
    glUseProgram(m_shaderProg);
}


GLint Technique::GetUniformLocation(const char* pUniformName)
{
    GLuint Location = glGetUniformLocation(m_shaderProg, pUniformName);
    if (Location == INVALID_UNIFORM_LOCATION) {
        fprintf(stderr, "Warning! Unable to get the location of uniform '%s'\n", pUniformName);
    }
    return Location;
}
