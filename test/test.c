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

static int init();
static int shutdown();

int main()
{

    init();

    // Create main buffer
    Buffer* buffer = nasl_buffer_create(800,600);
    // Clear main buffer to a light grey color
    nasl_buffer_clear(buffer, GREY3);

    // Create a sub_buffer
    Buffer* sub_buffer = nasl_buffer_get_subbuffer(buffer, 50, 50, 700, 400);
    nasl_buffer_clear(sub_buffer, BLACK);

    // Draw the C64 palette to the buffer
    int offset = 0;
    for (int palx = 0; palx < 16; palx++)
    {
        for (int j = offset; j < offset + 25; j++)
        {
            for (int i = 0; i < sub_buffer->width; i++)
            {
                nasl_buffer_set_pixel(sub_buffer, i, j, c64_palette[palx]);
            }
        }
        offset += 25;
    }
    // Blit sub_buffer onto the main buffer
    nasl_buffer_blit(buffer, sub_buffer, 50, 50);


    // Main loop
    while(nasl_graphics_running())
    {
        // Event polling
        nasl_graphics_poll_events();
        // Render the main buffer
        nasl_graphics_render(buffer);
        // Swap buffers
        nasl_graphics_present();
    }

    // Destroy the buffers we created
    nasl_buffer_destroy(sub_buffer);
    nasl_buffer_destroy(buffer);

    shutdown();
}

static int init()
{
    nasl_script_init();
    nasl_script_run("assets/scripts/init.bas");

    nasl_graphics_init(800, 600, "nasl test");

    return 1;
}

static int shutdown()
{
    nasl_graphics_shutdown();
    nasl_script_shutdown();

    return 1;
}
