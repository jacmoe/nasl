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

    SpriteSheet ascii = nasl_sprite_load("assets/fonts/ascii.png", 16, 16);

    // Create main buffer
    Buffer* buffer = nasl_buffer_create(buffer_width, buffer_height);
    // Clear main buffer to a blue color
    nasl_buffer_clear(buffer, BLUE);
    nasl_buffer_set_mainbuffer(buffer);

    int pal_offset = (buffer_width / 5) / 2;
    int pal_width = (buffer_width - (pal_offset * 2)) / 4;
    int pal_height = (buffer_height - (pal_offset * 2)) / 4;

    // Create a sub_buffer
    Buffer* sub_buffer = nasl_buffer_create(pal_width,pal_height);

    // Draw a palette by blitting 16 different sub_buffers into the main buffer
    int col = 0;
    int row = pal_offset;
    for(int buf = 0; buf < 16; buf++)
    {
        nasl_buffer_clear(sub_buffer, c64_palette[buf]);
        nasl_buffer_blit(buffer, sub_buffer, pal_offset + (pal_width * col), row);
        col++;
        if(col % 4 == 0)
        {
            col = 0;
            row += pal_height;
        }
    }

    // Draw a test line ..
    nasl_draw_line(buffer, 50, 50, 200, 40, RED);

    // Draw some text ..
    nasl_draw_text(buffer, ascii, 100, 70, "Hello World!!");

    // load an image ..
    Buffer* image_buffer = nasl_image_load("assets/textures/ceil.png");
    nasl_buffer_blit(buffer, image_buffer, 10, 40);
    image_buffer = nasl_image_load("assets/textures/floor.png");
    nasl_buffer_blit(buffer, image_buffer, 50, 80);
    image_buffer = nasl_image_load("assets/textures/wall.png");
    nasl_buffer_blit(buffer, image_buffer, 100, 120);
    nasl_buffer_destroy(image_buffer);

    // Run script for the main loop
    nasl_script_run("assets/scripts/init.bas");

    // Destroy the buffers we created
    nasl_buffer_destroy(sub_buffer);
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
