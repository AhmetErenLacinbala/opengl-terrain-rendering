#include "mesh.h"

void Mesh::CheckOpenGLError(const char* functionName) const
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        printf("OpenGL error after %s: %d\n", functionName, err);
    }
}

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
    indexCount = indices.size(); // Store the index count

    CheckOpenGLError("Start of Mesh Constructor");

    glGenVertexArrays(1, &VAO);
    CheckOpenGLError("glGenVertexArrays");

    glGenBuffers(1, &VBO);
    CheckOpenGLError("glGenBuffers for VBO");

    glGenBuffers(1, &EBO);
    CheckOpenGLError("glGenBuffers for EBO");

    glBindVertexArray(VAO);
    CheckOpenGLError("glBindVertexArray");

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    CheckOpenGLError("glBindBuffer for VBO");

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    CheckOpenGLError("glBufferData for VBO");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    CheckOpenGLError("glBindBuffer for EBO");

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    CheckOpenGLError("glBufferData for EBO");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    CheckOpenGLError("glVertexAttribPointer");

    glEnableVertexAttribArray(0);
    CheckOpenGLError("glEnableVertexAttribArray");

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    CheckOpenGLError("glBindBuffer to unbind VBO");

    glBindVertexArray(0);
    CheckOpenGLError("End of Mesh Constructor");
}


Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    CheckOpenGLError("glDeleteVertexArrays");

    glDeleteBuffers(1, &VBO);
    CheckOpenGLError("glDeleteBuffers for VBO");

    glDeleteBuffers(1, &EBO);
    CheckOpenGLError("glDeleteBuffers for EBO");
}

void Mesh::Draw(const ShaderProgram& program) const {
    program.Use();
    CheckOpenGLError("ShaderProgram Use");

    glBindVertexArray(VAO);
    CheckOpenGLError("glBindVertexArray for xwraw");

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    CheckOpenGLError("glDrawElements");

    glBindVertexArray(0);
    CheckOpenGLError("glBindVertexArray to unbind after Draw");
}
