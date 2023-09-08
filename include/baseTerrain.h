#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include "ShaderProgram.h"

class BaseTerrain : public GameObject {
private:
    Mesh terrainMesh;
    ShaderProgram terrainShader;
public:
    BaseTerrain(const Mesh& mesh, const ShaderProgram& shader);
    void Update(float dt) override;
    void Render() override;
};
