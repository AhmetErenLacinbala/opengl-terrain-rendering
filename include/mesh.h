#pragma once
#include <vector>
#include <GL/glew.h>
#include <shaderProgram.h>

class Mesh {
private:
    GLuint VAO, VBO, EBO;
    size_t indexCount; // Member to keep track of index count

public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();
    void Draw(const ShaderProgram& program) const;
};
