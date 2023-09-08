#pragma once
#include <map>
#include <string>
#include "shaderProgram.h"
#include "mesh.h"

class ResourceManager {
private:
    std::map<std::string, ShaderProgram> shaders;
    std::map<std::string, Mesh> meshes;
public:
    ShaderProgram& getShader(const std::string& name);
    Mesh& getMesh(const std::string& name);
};
