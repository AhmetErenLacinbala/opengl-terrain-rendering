#include <string.h>
#include <math.h>
#include <stdio.h>
#include <GL/glew.h>
#include <ogl_dev/ogldev_util.h>
#include <ogl_dev/ogldev_basic_glfw_camera.h>
#include <ogl_dev/ogldev_glfw.h>
#include <terrain.h>
#include <cstdlib>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vertexTypes.hpp>

#include "shader.h"
#include "shaderProgram.h"
#include "mesh.h"
#include "gameObject.h"
#include "scene.h"
#include "cube.h"
#include "terrain.h"

#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080


std::vector<Vertex3Tex>     vertices;
std::vector<unsigned int>   indices;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void CursorPosCallback(GLFWwindow* window, double x, double y);

static void MouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode);





class TerrainDemo1 : public GameObject
{

private:
    //Cube m_cube;
    Scene m_scene;

public:

    TerrainDemo1()
    {
    }

    virtual ~TerrainDemo1()
    {
        SAFE_DELETE(m_pGameCamera);
    }


    void Init()
    {
        CreateWindow();
        InitCallbacks();
        InitCamera();
        InitTerrain();
        m_scene.AddObject(&m_terrain);
        //m_scene.AddObject(&m_cube);
        
    }


    void Run()
    {
        printRenderer();
        while (!glfwWindowShouldClose(window)) {
            RenderScene();
            glfwSwapBuffers(window);
            glfwPollEvents();
            updateFPS();
        }
    }


    void RenderScene()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_terrain.Render(*m_pGameCamera);
        m_scene.Render();
    }


    void PassiveMouseCB(int x, int y)
    {
        m_pGameCamera->OnMouse(2*x, 2*y);
    }
    void Update(float dt) override
    {
       
    }

    void Render(const BasicCamera& Camera) override
    {
        RenderScene();
    }
    void KeyboardCB(uint key, int state)
    {
        if (state == GLFW_PRESS) {

            switch (key) {

            case GLFW_KEY_ESCAPE:
            case GLFW_KEY_Q:
                glfwDestroyWindow(window);
                glfwTerminate();
                exit(0);

            case GLFW_KEY_C:
                //m_pGameCamera->Print();
                break;

            case GLFW_KEY_W:
                m_isWireframe = !m_isWireframe;

                if (m_isWireframe) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                } else {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }

                break;
            }
        }

        m_pGameCamera->OnKeyboard(key);
    }


    void MouseCB(int button, int action, int x, int y)
    {
    }


private:
    int frameCount = 0;
    double elapsedTime = 0.0;
    double lastTime = 0.0;
    double fps = 0.0;

    void updateFPS()
    {
        double currentTime = glfwGetTime(); // Get the current time.
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        elapsedTime += deltaTime;
        frameCount++;

        if (elapsedTime >= 1.0)
        {
            fps = double(frameCount) / elapsedTime;
            printf("FPS: %f\n", fps);
            frameCount = 0;
            elapsedTime = 0.0;
        }
    }

    void printRenderer(){
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* version = glGetString(GL_VERSION);
        printf("Renderer: %s\n", renderer);
        printf("OpenGL version: %s\n", version);
    }
    void CreateWindow()
    {
        int minor_ver = 1;
        int major_ver = 4;
        bool is_full_screen = false;
        window = glfw_init(major_ver, minor_ver, WINDOW_WIDTH, WINDOW_HEIGHT, is_full_screen, "terrain rendering");
        glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    }

    void InitCallbacks()
    {
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
    }
    void InitCamera()
    {
        Vector3f Pos(100.0f, 220.0f, -400.0f);
        Vector3f Target(0.0f, -0.25f, 1.0f);
        Vector3f Up(0.0, 1.0f, 0.0f);
        float zFar = 2000.0f;
        float FOV = 45.0f;
        float zNear = 0.1f;
        PersProjInfo persProjInfo = { FOV, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, zNear, zFar };
        m_pGameCamera = &BasicCamera::GetInstance();
    }
    void InitTerrain()
    {
        float WorldScale = 4.0f;
        m_terrain.InitTerrain(WorldScale);
        m_terrain.LoadFromFile("heightmap.save");	
    }

    GLFWwindow* window = NULL;
    BasicCamera* m_pGameCamera = NULL;
    bool m_isWireframe = false;
    BaseTerrain m_terrain;
};

TerrainDemo1* app = NULL;


static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    app->KeyboardCB(key, action);
}


static void CursorPosCallback(GLFWwindow* window, double x, double y)
{
    app->PassiveMouseCB((int)x, (int)y);
}


static void MouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode)
{
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    app->MouseCB(Button, Action, (int)x, (int)y);
}


int main(int argc, char** argv)
{
    setenv("LIBGL_ALWAYS_SOFTWARE", "1", 1);
    app = new TerrainDemo1();

    app->Init();
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    app->Run();
    delete app;

    return 0;
}
