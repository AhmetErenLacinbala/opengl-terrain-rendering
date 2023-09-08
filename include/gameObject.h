#pragma once

#include <ogl_dev/ogldev_basic_glfw_camera.h>

class GameObject {
public:
    virtual void Update(float dt) = 0;
    virtual void Render(const BasicCamera& Camera) = 0;
};
