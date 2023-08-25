#ifdef WIN32
#include <Windows.h>
#endif
#include <stdio.h>

#include "ogldev_util.h"
#include "ogldev_glfw.h"

static void glfw_lib_init()
{
    if (glfwInit() != 1)
    {
        OGLDEV_ERROR0("Error initializing GLFW");
        exit(1);
    }

    int Major, Minor, Rev;

    glfwGetVersion(&Major, &Minor, &Rev);

    printf("GLFW %d.%d.%d initialized\n", Major, Minor, Rev);
}

static void enable_debug_output()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr); // expection error here
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
}

// Must be done after glfw is initialized!
static void init_glew()
{
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        printf("Error initializing GLEW: %s\n", glewGetErrorString(glewError));
        exit(1);
    }
}

GLFWwindow *glfw_init(int major_ver, int minor_ver, int width, int height, bool is_full_screen, const char *title)
{
    glfw_lib_init();
    GLFWmonitor *monitor = is_full_screen ? glfwGetPrimaryMonitor() : NULL;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    if (major_ver > 0)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    }

    if (minor_ver > 0)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    }

    GLFWwindow *window = glfwCreateWindow(width, height, title, monitor, NULL);

    if (!window)
    {
        const char *description;
        int code = glfwGetError(&description);
        if (description)
        {
            printf("GLFW Error %d: %s\n", code, description);
        }
        OGLDEV_ERROR0("error creating window");
        exit(1);
    }

    glfwMakeContextCurrent(window);

    // Must be done after glfw is initialized!
    init_glew();

    //enable_debug_output(); // expection error. fix here

    glfwSwapInterval(1);
    return window;
}
