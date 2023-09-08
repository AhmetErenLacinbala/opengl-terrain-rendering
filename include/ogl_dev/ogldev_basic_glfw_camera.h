#ifndef BASIC_CAMERA_H
#define BASIC_CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ogldev_math_3d.h"

class BasicCamera
{
public:
    static BasicCamera &GetInstance(int WindowWidth = DEFAULT_WIDTH, int WindowHeight = DEFAULT_HEIGHT);

    void SetPosition(float x, float y, float z);
    void SetPosition(const Vector3f &pos);
    void SetTarget(float x, float y, float z);
    void SetTarget(const Vector3f &target);
    bool OnKeyboard(int Key);
    void OnMouse(int x, int y);
    void OnRender();
    void Init();
    Matrix4f GetProjectionMat() const;

    Matrix4f GetMatrix() const;
    Matrix4f GetViewProjMatrix() const;
    void SetSpeed(float Speed);

private:
    BasicCamera(int WindowWidth, int WindowHeight);
    BasicCamera(const BasicCamera &) = delete;            // Disable the copy constructor
    BasicCamera &operator=(const BasicCamera &) = delete; // Disable the assignment operator

    Vector3f m_pos, m_target, m_up;
    int m_windowWidth, m_windowHeight;

    void Update();
    float m_AngleH;
    float m_AngleV;
    bool m_OnUpperEdge;
    bool m_OnLowerEdge;
    bool m_OnLeftEdge;
    bool m_OnRightEdge;
    Vector2f m_mousePos;
    float m_speed;

    static const int DEFAULT_WIDTH = 800;  // Default width
    static const int DEFAULT_HEIGHT = 600; // Default height
};

#endif // BASIC_CAMERA_H
