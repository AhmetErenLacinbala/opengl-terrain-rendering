#pragma once
#include <vector>
#include "gameObject.h"

class Scene {
private:
    std::vector<GameObject*> gameObjects;
public:
    void AddObject(GameObject* obj);
    void Update(float dt);
    void Render();
};
