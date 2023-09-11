#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class BasicCamera {
public:
    BasicCamera();

    void SetPerspective(float fov, float aspect, float nearPlane, float farPlane);
    void SetPosition(const glm::vec3& position);
    void SetLookAt(const glm::vec3& target);
    void Move(const glm::vec3& offset);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    void OnMouse(float x, float y);
    void OnKeyboard(int key);

private:
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;
    glm::mat4 m_projection;

    const float CAMERA_SPEED = 5.0f; 
    const float MOUSE_SENSITIVITY = 0.05f;
};
