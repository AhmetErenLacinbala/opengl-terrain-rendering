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

class ShaderProgram;
class BasicCamera;

class BaseTerrain : public GameObject {
public:
    BaseTerrain(){};
    void InitTerrain(float WorldScale);
    void Render(const BasicCamera& Camera);
    void LoadFromFile(const char* pFilename);
    float GetHeight(int x, int z) const;
    float GetWorldScale() const;
	void Update(float dt){};
    //void Render() override;

protected:
    void LoadHeightMapFile(const char* pFilename);

    int m_terrainSize = 0;
    float m_worldScale = 1.0f;
    Array2D<float> m_heightMap;
    TriangleList m_triangleList;
    TerrainTechnique m_terrainTech;
};

#endif
