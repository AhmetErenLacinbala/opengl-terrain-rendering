#pragma once
#include <vector>
#include <GL/glew.h>
#include <shaderProgram.h>

class Mesh {
private:
    GLuint VAO, VBO, EBO;
    size_t indexCount; // Member to keep track of index count
    void CheckOpenGLError(const char* functionName) const;

public:
     Mesh() : indexCount(0), VAO(0), VBO(0), EBO(0) {} // Added default constructor

    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices); 
    ~Mesh();
    void Draw(const ShaderProgram& program) const;
};
