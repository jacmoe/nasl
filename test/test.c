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

#include <SDL.h>
#include <SDL_image.h>

static void init();
static void shutdown();

int main()
{

    init();

    int buffer_width = 320;
    int buffer_height = 240;

    // Create main buffer
    Buffer* buffer = nasl_buffer_create(buffer_width, buffer_height);
    // Clear main buffer to a blue color
    nasl_buffer_clear(buffer, GREY1);
    nasl_draw_text(buffer, 20, 220, WHITE, "This is a font that is rendered!!");
    nasl_buffer_set_mainbuffer(buffer);

    int running = 1;

    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            nasl_graphics_render(buffer);
            nasl_graphics_present();
            if(event.type == SDL_QUIT)
                running = 0;
        }
    }

    // Destroy the buffers we created
    nasl_buffer_destroy(buffer);

    shutdown();
}

static void init()
{
    nasl_script_init();
    nasl_script_set_import_dirs("assets/scripts");
    
    nasl_graphics_script_init();
    nasl_buffer_script_init();
    nasl_draw_script_init();
    nasl_image_script_init();
    nasl_color_script_init();
    nasl_sprite_script_init();

    nasl_graphics_init(320, 240, "nasl test", 0, 2);
}

static void shutdown()
{
    nasl_graphics_shutdown();
    nasl_script_shutdown();
}
