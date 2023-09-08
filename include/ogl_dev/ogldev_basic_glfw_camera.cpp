#include "ogldev_basic_glfw_camera.h";

BasicCamera& BasicCamera::GetInstance(int WindowWidth, int WindowHeight) {
    static BasicCamera instance(WindowWidth, WindowHeight); // Singleton instance
    return instance;
}

BasicCamera::BasicCamera(int WindowWidth, int WindowHeight) {
    m_windowWidth  = WindowWidth;
    m_windowHeight = WindowHeight;
    m_pos          = Vector3f(0.0f, 0.0f, 0.0f);
    m_target       = Vector3f(0.0f, 0.0f, 1.0f);
    m_up           = Vector3f(0.0f, 1.0f, 0.0f);

    Init();
}


void BasicCamera::SetPosition(float x, float y, float z) {
    m_pos.x = x;
    m_pos.y = y;
    m_pos.z = z;
}

void BasicCamera::SetPosition(const Vector3f& pos) {
    SetPosition(pos.x, pos.y, pos.z);
}

void BasicCamera::SetTarget(float x, float y, float z) {
    m_target.x = x;
    m_target.y = y;
    m_target.z = z;
}

void BasicCamera::SetTarget(const Vector3f& target) {
    SetTarget(target.x, target.y, target.z);
}


void BasicCamera::Init() {
    Vector3f HTarget(m_target.x, 0.0, m_target.z);
    HTarget.Normalize();

    float Angle = ToDegree(asin(abs(HTarget.z)));

    if (HTarget.z >= 0.0f) {
        if (HTarget.x >= 0.0f) {
            m_AngleH = 360.0f - Angle;
        } else {
            m_AngleH = 180.0f + Angle;
        }
    } else {
        if (HTarget.x >= 0.0f) {
            m_AngleH = Angle;
        } else {
            m_AngleH = 180.0f - Angle;
        }
    }

    m_AngleV = -ToDegree(asin(m_target.y));
    m_OnUpperEdge = false;
    m_OnLowerEdge = false;
    m_OnLeftEdge  = false;
    m_OnRightEdge = false;
    m_mousePos.x  = m_windowWidth / 2;
    m_mousePos.y  = m_windowHeight / 2;
}

bool BasicCamera::OnKeyboard(int Key) {
    bool CameraChangedPos = false;

    // ... Your OnKeyboard switch-case logic ...

    return CameraChangedPos;
}

void BasicCamera::OnMouse(int x, int y) {
    int DeltaX = x - m_mousePos.x;
    int DeltaY = y - m_mousePos.y;

    m_mousePos.x = x;
    m_mousePos.y = y;

    m_AngleH += (float)DeltaX / 20.0f;
    m_AngleV += (float)DeltaY / 20.0f;

    // ... Your edge-checking logic ...

    Update();
}

void BasicCamera::OnRender() {
    bool ShouldUpdate = false;

    // ... Your edge-based updating logic ...

    if (ShouldUpdate) {
        Update();
    }
}

void BasicCamera::Update() {
    Vector3f Yaxis(0.0f, 1.0f, 0.0f);

    Vector3f View(1.0f, 0.0f, 0.0f);
    View.Rotate(m_AngleH, Yaxis);
    View.Normalize();

    Vector3f U = Yaxis.Cross(View);
    U.Normalize();
    View.Rotate(m_AngleV, U);

    m_target = View;
    m_target.Normalize();

    m_up = m_target.Cross(U);
    m_up.Normalize();
}

Matrix4f BasicCamera::GetMatrix() const {
    Matrix4f CameraTransformation;
    CameraTransformation.InitCameraTransform(m_pos, m_target, m_up);
    return CameraTransformation;
}

Matrix4f BasicCamera::GetViewProjMatrix() const {
    Matrix4f View = GetMatrix();
    Matrix4f Projection = GetProjectionMat();
    Matrix4f ViewProj = Projection * View;
    return ViewProj;
}

void BasicCamera::SetSpeed(float Speed) {
    if (Speed <= 0.0f) {
        printf("Invalid camera speed %f\n", Speed);
        exit(0);
    }
    m_speed = Speed;
}


Matrix4f BasicCamera::GetProjectionMat() const {
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    float aspectRatio = static_cast<float>(m_windowWidth) / m_windowHeight;
    
    Matrix4f projectionMat;
    projectionMat.InitPerspectiveProj(fov, aspectRatio, nearPlane, farPlane);
    return projectionMat;
}