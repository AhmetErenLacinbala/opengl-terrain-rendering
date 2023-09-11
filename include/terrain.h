#ifndef BASETERRAIN_H
#define BASETERRAIN_H

#include "ogl_dev/ogldev_types.h"
#include "ogl_dev/ogldev_basic_glfw_camera.h"
#include "ogl_dev/ogldev_array_2d.h"
#include "triangle_list.h"
#include "terrain_technique.h"
#include "shaderProgram.h"
#include "gameObject.h"
#include "ogl_dev/ogldev_basic_glfw_camera.h"
#include "mesh.h"

class ShaderProgram;
class BasicCamera;


class BaseTerrain : public GameObject {
public:
    BaseTerrain();
    
    void InitTerrain(float WorldScale);
    void GenerateTerrain();
    void Render(const BasicCamera& Camera);
    float GetHeight(int x, int z) const;
    float GetWorldScale() const;
	void Update(float dt){};
        void GenerateTerrainVertices();
    void GenerateTerrainIndices();
    inline size_t GetTerrainSize() const { return m_size; }
     void LoadHeightMapFile(const char* pFilename);
    //void Render() override;

protected:
   

    int m_terrainSize = 0;
    float m_worldScale = 1.0f;
    Array2D<float> m_heightMap;
    TriangleList m_triangleList;
    TerrainTechnique m_terrainTech;
    private:

    size_t m_size;  // Size of the terrain in terms of vertices

    void LoadHeightmap(const char* heightmapFilename);
    private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    int width;       // Width of the terrain grid
    int depth;       // Depth (or length) of the terrain grid
    float* heightmap; 
    Mesh m_terrainMesh;
};

#endif
