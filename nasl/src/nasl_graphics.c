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

static char *ReadFile(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "Coudn't read file: '%s'\n", path);
    }

    fseek(f, 0, SEEK_END);
    size_t fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = malloc(fsize + 1);
    fread(buf, fsize, 1, f);
    buf[fsize] = '\0';

    fclose(f);

    return buf;
}


static GLuint CompileShaderProgram() {
    char *vertexSource = ReadFile("assets/shaders/vertex.glsl");
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar **)&vertexSource, NULL);
    glCompileShader(vertexShader);
    free(vertexSource);

    char *fragmentSource = ReadFile("assets/shaders/frag.glsl");
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const GLchar **)&fragmentSource, NULL);
    glCompileShader(fragmentShader);
    free(fragmentSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}


static GLuint BuildQuad(GLuint shaderProgram) {
    GLfloat vertices[] = {
        // Vertex coord  Texture coord
        1,  1,           1, 0,
        -1,  1,          0, 0,
        1, -1,           1, 1,
        -1, -1,          0, 1
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex attributes
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
            0);
    glEnableVertexAttribArray(posAttrib);

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
            (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(texAttrib);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}


static GLuint BuildTexture(int width, int height) {
    GLuint tex;

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}


static void InitOpenGL(int width, int height) {
    GLuint shaderProgram = CompileShaderProgram();
    GLuint quad_vao = BuildQuad(shaderProgram);
    GLuint tex = BuildTexture(width, height);

    glUseProgram(shaderProgram);
    glBindVertexArray(quad_vao);
    glBindTexture(GL_TEXTURE_2D, tex);
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
            width, height,
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
    InitOpenGL(width, height);
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

static uint32_t get_time()
{
    return 1000 * glfwGetTime();
}

uint32_t nasl_graphics_render(Buffer *buf)
{
    uint32_t start = get_time();

    glTexSubImage2D(
            GL_TEXTURE_2D,              // target
            0,                          // level of detail
            0, 0,                       // xoffset, yoffset
            buf->width, buf->height,    // width, height
            GL_RGBA, GL_UNSIGNED_BYTE,  // format, type
            buf->pixels                 // pixels
            );
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    return get_time() - start;
}


void nasl_graphics_present()
{
    glfwSwapBuffers(window);
}

void nasl_graphics_poll_events()
{
    glfwPollEvents();
}
