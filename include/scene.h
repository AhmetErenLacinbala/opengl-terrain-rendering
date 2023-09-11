#pragma once
#include <vector>
#include "gameObject.h"

class Scene {
private:
    std::vector<GameObject*> gameObjects;
    BasicCamera m_camera;
    
public:
    void AddObject(GameObject* obj);
    void Update(float dt);
    void Render();
    BasicCamera& GetCamera() { return m_camera; }
};
