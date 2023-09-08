#include <baseTerrain.h>
#include <ogl_dev/ogldev_basic_glfw_camera.h>

void BaseTerrain::Update(float dt) {
    // Insert logic for updating terrain here, if any
}

void BaseTerrain::Render() {
    Matrix4f camMatrix = BasicCamera::GetInstance().GetViewProjMatrix();
    // Now use camMatrix for your rendering logic...
}
