#pragma once

#include <GL/glew.h>
#include "gameObject.h"

class Cube : public GameObject {
private:
    GLuint VBO, VAO, EBO;

    // Vertex data for a cube
   GLfloat vertices[108]; // Assuming 3 coordinates (x, y, z) for each of 24 vertices

    // Indices for the cube vertices
    GLuint indices[36];

public:
    Cube();
    ~Cube();  // Destructor to clean up the buffers
    void Update(float dt) override;
    void Render(const BasicCamera& Camera) override;
};
