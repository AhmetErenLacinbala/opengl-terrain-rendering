#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <string.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "terrain.h"

//#define DEBUG_PRINT

class TerrainShaderProgram : public ShaderProgram {
public:
    bool Init(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        Shader vertexShader, fragmentShader;
        
        if (!vertexShader.Load(GL_VERTEX_SHADER, vertexShaderPath) || 
            !fragmentShader.Load(GL_FRAGMENT_SHADER, fragmentShaderPath)) {
            return false;
        }
        
        AttachShader(vertexShader);
        AttachShader(fragmentShader);
        
        if (!Link()) {
            return false;
        }

        return true;
    }

};

void BaseTerrain::InitTerrain(float WorldScale)
{
    if (!m_terrainTech.Init()) {
        printf("Error initializing tech\n");
        exit(0);
    }

    m_worldScale = WorldScale;
}




BaseTerrain::BaseTerrain() {
    LoadHeightmap("./heightmap.save");
    GenerateTerrain();
}

void BaseTerrain::LoadHeightmap(const char* heightmapFilename) {
    int fileSize = 0;
    char* data = ReadBinaryFile("heightmap.save", fileSize);
    
    // Assuming each height value is represented as a float
    m_size = fileSize / sizeof(float);
    
    float* heightValues = reinterpret_cast<float*>(data);
    // Now you can use heightValues to populate the terrain heights

    // Don't forget to delete the memory after using
    delete[] data;
}

void BaseTerrain::GenerateTerrain() {
    
    // Use m_size and any loaded data to generate the vertices and indices
    GenerateTerrainVertices();
    GenerateTerrainIndices();
    
    m_terrainMesh = Mesh(vertices, indices);
}
void BaseTerrain::LoadHeightMapFile(const char* pFilename)
{
    int FileSize = 0;
    unsigned char* p = (unsigned char*)ReadBinaryFile("heightmap.save", FileSize);

    if (FileSize % sizeof(float) != 0) {
        printf("%s:%d - '%s' does not contain an whole number of floats (size %d)\n", __FILE__, __LINE__, "heightmap.save", FileSize);
        exit(0);
    }

    m_terrainSize = (int)sqrtf((float)FileSize / (float)sizeof(float));

    printf("Terrain size %d\n", m_terrainSize);

    if ((m_terrainSize * m_terrainSize) != (FileSize / sizeof(float))) {
        printf("%s:%d - '%s' does not contain a square height map - size %d\n", __FILE__, __LINE__, "heightmap.save", FileSize);
        exit(0);
    }

    m_heightMap.InitArray2D(m_terrainSize, m_terrainSize, (float*)p);
}

void BaseTerrain::Render(const BasicCamera& Camera) {
    TerrainShaderProgram terrainShader;

    if (!terrainShader.Init("terrain.vs", "terrain.fs")) {
        std::cerr << "Error initializing shaders." << std::endl;
        return;
    }
    
    // Set shader parameters here if any, like uniforms, before rendering
    
    m_terrainMesh.Draw(terrainShader);
}




float BaseTerrain::GetHeight(int x, int z) const {
    return m_heightMap.Get(x, z);
}

float BaseTerrain::GetWorldScale() const {
    return m_worldScale;
}

// GenerateTerrainVertices
void BaseTerrain::GenerateTerrainVertices() {
    const float scale = 1.0f;  // Adjust this to scale the terrain size

    // Clear the existing vertices
    vertices.clear();

    // Loop through each grid cell
    for (int z = 0; z < depth; z++) {
        for (int x = 0; x < width; x++) {
            // X, Y, Z coordinates
            float fx = x * scale;
            float fz = z * scale;
            float fy = heightmap[z * width + x] * scale;

            // Add the vertex position to the list
            vertices.push_back(fx);
            vertices.push_back(fy);
            vertices.push_back(fz);
        }
    }
}

void BaseTerrain::GenerateTerrainIndices() {
    // Clear the existing indices
    indices.clear();

    // Loop through each grid cell
    for (int z = 0; z < depth - 1; z++) {
        for (int x = 0; x < width - 1; x++) {
            // Get indices of vertices for this cell
            int topLeft = z * width + x;
            int topRight = topLeft + 1;
            int bottomLeft = (z + 1) * width + x;
            int bottomRight = bottomLeft + 1;

            // Add two triangles to make the quad
            // Triangle 1
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            // Triangle 2
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
}
