/*
*   This file is part of the
* ███╗   ██╗ █████╗ ███████╗██╗     
* ████╗  ██║██╔══██╗██╔════╝██║     
* ██╔██╗ ██║███████║███████╗██║     
* ██║╚██╗██║██╔══██║╚════██║██║     
* ██║ ╚████║██║  ██║███████║███████╗
* ╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚══════╝
*   project : https://github.com/jacmoe/nasl
*
*   Copyright 2017 Jacob Moen
*
*/
#include "nasl_graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL_image.h>

static SDL_Window* window = NULL;
static SDL_GLContext glcontext;

// Flags
static int resizef;

static const char *vertexSource = "#version 330 core\n"
"\n"
"in vec2 position;\n"
"in vec2 texcoord;\n"
"\n"
"out vec3 Color;\n"
"out vec2 Texcoord;\n"
"\n"
"void main() {\n"
"    Texcoord = texcoord;\n"
"    gl_Position = vec4(position, 0.0, 1.0);\n"
"}";

static const char *fragmentSource = "#version 330 core\n"
"\n"
"in vec2 Texcoord;\n"
"\n"
"out vec4 outColor;\n"
"\n"
"uniform sampler2D tex;\n"
"\n"
"void main() {\n"
"    outColor = texture(tex, Texcoord);\n"
"}";

static void error_callback(int e, const char *d)
{
    printf("Error %d: %s\n", e, d);
}

void framebuffer_size_callback(SDL_Window* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


SDL_Window* nasl_graphics_get_window()
{
    return window;
}


int HandleResize(void *userdata, SDL_Event *ev) {
    if (ev->type == SDL_WINDOWEVENT) {
        if (ev->window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            resizef = 1;
        }
    }

    return 0;  // Ignored
}

int nasl_graphics_init(int width, int height, const char* title, int fullscreen, int scalefactor)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    // Core-Profile OpenGL 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Create window and OpenGL Context
    window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width * scalefactor, height * scalefactor,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
            );

    glcontext = SDL_GL_CreateContext(window);

    // Handle resize events
    SDL_AddEventWatch(HandleResize, NULL);

    // Disable vsync
    SDL_GL_SetSwapInterval(0);

    // Init GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Quad vertices ...
    float vertices[] = {
        // Position   Texcoords
        -1,  1,   0, 0,  // Top-left
        1,  1,   1, 0,  // Top-right
        1, -1,   1, 1,  // Bottom-right
        -1, -1,   0, 1,  // Bottom-left
    };

    // ... elements ...
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0,
    };

    // ... and texture
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, NULL);

    // Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertex Buffer Object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Element Buffer Object
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
            GL_STATIC_DRAW);

    // Shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Vertex attributes
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
            4 * sizeof(float), 0);

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
            4 * sizeof(float), (void *)(2 * sizeof(float)));

    // Clear with black
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    return 0;
}

int nasl_graphics_shutdown()
{
    SDL_GL_DeleteContext(glcontext);
    IMG_Quit();
    SDL_Quit();
    return 0;
}

int nasl_graphics_running()
{
    return 1;//!glfwWindowShouldClose(window);
}

static uint32_t get_time()
{
    return SDL_GetTicks();
}

uint32_t nasl_graphics_render(Buffer *buf)
{
    uint32_t start = get_time();

    if (resizef) {
        resizef = 0;

        int winwidth, winheight;
        SDL_GetWindowSize(window, &winwidth, &winheight);

        glViewport(0, 0, winwidth, winheight);
    }

    glTexSubImage2D(
            GL_TEXTURE_2D,
            0, 0,
            0,
            buf->width, buf->height,
            GL_RGBA, GL_UNSIGNED_BYTE,
            buf->pixels
            );

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return get_time() - start;
}


void nasl_graphics_present()
{
    SDL_GL_SwapWindow(window);
}

void nasl_graphics_poll_events()
{
    //glfwPollEvents();
}
