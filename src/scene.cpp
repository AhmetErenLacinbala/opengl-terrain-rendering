#include <scene.h>

void Scene::AddObject(GameObject* obj) {
    gameObjects.push_back(obj);
}

void Scene::Update(float dt) {
    for (auto& obj : gameObjects) {
        obj->Update(dt);
    }
}

void Scene::Render() {
    BasicCamera& globalCamera = BasicCamera::GetInstance();
    for (auto& obj : gameObjects) {
        obj->Render(globalCamera);
    }
}
