#include <ResourceManager.h>

ShaderProgram& ResourceManager::getShader(const std::string& name) {
    return shaders[name];
}

Mesh& ResourceManager::getMesh(const std::string& name) {
    return meshes[name];
}

// Similarly for set operations and other resource types
