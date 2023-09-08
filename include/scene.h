#pragma once
#include <vector>
#include "GameObject.h"

class Scene {
private:
    std::vector<GameObject*> gameObjects;
public:
    void AddObject(GameObject* obj);
    void Update(float dt);
    void Render();
};
