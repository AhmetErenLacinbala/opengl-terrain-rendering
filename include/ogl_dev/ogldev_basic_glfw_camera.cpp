#include <ogl_dev/ogldev_basic_glfw_camera.h>

#include <GLFW/glfw3.h>

BasicCamera::BasicCamera() : m_position(0.0f, 0.0f, 0.0f), m_forward(0.0f, 0.0f, -1.0f), m_up(0.0f, 1.0f, 0.0f) {}

void BasicCamera::SetPerspective(float fov, float aspect, float nearPlane, float farPlane) {
    m_projection = glm::perspective(fov, aspect, nearPlane, farPlane);
}

void BasicCamera::SetPosition(const glm::vec3& position) {
    m_position = position;
}

void BasicCamera::SetLookAt(const glm::vec3& target) {
    m_forward = glm::normalize(target - m_position);
}

void BasicCamera::Move(const glm::vec3& offset) {
    m_position += offset;
}

glm::mat4 BasicCamera::GetViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_forward, m_up);
}

glm::mat4 BasicCamera::GetProjectionMatrix() const {
    return m_projection;
}

void BasicCamera::OnMouse(float x, float y) {
    static bool firstMouse = true;
    static float lastX = 0.0f, lastY = 0.0f;
    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float xOffset = x - lastX;
    float yOffset = lastY - y;
    lastX = x;
    lastY = y;

    xOffset *= MOUSE_SENSITIVITY;
    yOffset *= MOUSE_SENSITIVITY;

    glm::vec3 front;
    front.x = cos(glm::radians(yOffset)) * cos(glm::radians(xOffset));
    front.y = sin(glm::radians(yOffset));
    front.z = cos(glm::radians(yOffset)) * sin(glm::radians(xOffset));
    m_forward = glm::normalize(front);
}

void BasicCamera::OnKeyboard(int key) {
    glm::vec3 direction;

    switch (key) {
        case GLFW_KEY_UP:
            direction += m_forward;
            break;
        case GLFW_KEY_DOWN:
            direction -= m_forward;
            break;
        case GLFW_KEY_LEFT:
            direction -= glm::normalize(glm::cross(m_forward, m_up));
            break;
        case GLFW_KEY_RIGHT:
            direction += glm::normalize(glm::cross(m_forward, m_up));
            break;
        /*case GLFW_KEY_R:
            direction += m_up;
            break;
        case GLFW_KEY_F:
            direction -= m_up;
            break;*/
        default:
            break;
    }

    Move(CAMERA_SPEED * direction);
}
