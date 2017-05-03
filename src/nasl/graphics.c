#include "graphics.h"

static GLFWwindow *window = NULL;

int nasl_graphics_init(int width, int height)
{
    glfwInit();

    /* Compute window resolution from the main monitor's */
    //const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    //const int width = mode->width / 2;
    //const int height = mode->height / 2;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create window and OpenGL context
    window = glfwCreateWindow(width, height, "engine", NULL, NULL);
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);

    // Disable cursor
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Init GLEW
    glewExperimental = GL_TRUE;
    glewInit();
    return 0;
}

int nasl_graphics_shutdown()
{
    glfwTerminate();
    return 0;
}

int nasl_graphics_running()
{
    return !glfwWindowShouldClose(window);
}

void nasl_graphics_present()
{
    glfwSwapBuffers(window);
}

void nasl_graphics_poll_events()
{
    glfwPollEvents();
}
