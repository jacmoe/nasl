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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "nasl_script.h"
#include "nasl_graphics.h"
#include "nasl_buffer.h"
#include "nasl_draw.h"
#include "nasl_sprite.h"
#include "nasl_image.h"

static int init();
static int shutdown();
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{

    init();

    int buffer_width = 320;
    int buffer_height = 240;

    // Create main buffer
    Buffer* buffer = nasl_buffer_create(buffer_width, buffer_height);
    // Clear main buffer to a blue color
    nasl_buffer_clear(buffer, BLUE);
    nasl_buffer_set_mainbuffer(buffer);

    // Draw some fancy text
    nasl_draw_text(buffer, 20, 200, WHITE, FONT_SMALL, "Some grand text!");

    // Run script for the main loop
    nasl_script_run("assets/scripts/init.bas");

    // Destroy the buffers we created
    nasl_buffer_destroy(buffer);

    shutdown();
}

static int init()
{
    nasl_script_init();
    nasl_script_set_import_dirs("assets/scripts");
    
    nasl_graphics_script_init();
    nasl_buffer_script_init();
    nasl_draw_script_init();
    nasl_image_script_init();
    nasl_color_script_init();
    nasl_sprite_script_init();

    nasl_graphics_init(320, 240, "nasl test", 0, 3);

    glfwSetKeyCallback(nasl_graphics_get_window(), key_callback);

    return 1;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static int shutdown()
{
    nasl_graphics_shutdown();
    nasl_script_shutdown();

    return 1;
}
