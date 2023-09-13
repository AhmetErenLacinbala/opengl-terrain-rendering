#include <ResourceManager.h>

ShaderProgram& ResourceManager::getShader(const std::string& name) {
    return shaders[name];
}

Mesh& ResourceManager::getMesh(const std::string& name) {
    auto it = meshes.find(name);
if (it != meshes.end()) {
    return it->second;
} else {
    printf("mesh is not found\n");
}
}

// Similarly for set operations and other resource types
