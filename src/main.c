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

#include "nasl/script.h"
#include "nasl/graphics.h"
#include "nasl/buffer.h"

static int init();
static int shutdown();

int main()
{
    // C64 Color Palette
    uint32_t c64_black =        0       | 0     << 8 |  0   << 16;
    uint32_t c64_white =        255     | 255   << 8 |  255 << 16;
    int32_t c64_red =          136     | 0     << 8 |  0   << 16;
    uint32_t c64_cyan =         170     | 255   << 8 |  238 << 16;
    uint32_t c64_violet =       204     | 68    << 8 |  204 << 16;
    uint32_t c64_green =        0       | 204   << 8 |  85  << 16;
    uint32_t c64_blue =         0       | 0     << 8 |  170 << 16;
    uint32_t c64_yellow =       238     | 238   << 8 |  119 << 16;
    uint32_t c64_orange =       221     | 136   << 8 |  85  << 16;
    uint32_t c64_brown =        102     | 68    << 8 |  0   << 16;
    uint32_t c64_lightred =     255     | 119   << 8 |  119 << 16;
    uint32_t c64_grey1 =        51      | 51    << 8 |  51  << 16;
    uint32_t c64_grey2 =        119     | 119   << 8 |  119 << 16;
    uint32_t c64_lightgreen =   170     | 255   << 8 |  102 << 16;
    uint32_t c64_lightblue =    0       | 136   << 8 |  255 << 16;
    uint32_t c64_grey3 =        187     | 187   << 8 |  187 << 16;

    uint32_t palette[16];
    palette[0] = c64_black;
    palette[1] = c64_white;
    palette[2] = c64_red;
    palette[3] = c64_cyan;
    palette[4] = c64_violet;
    palette[5] = c64_green;
    palette[6] = c64_blue;
    palette[7] = c64_yellow;
    palette[8] = c64_orange;
    palette[9] = c64_brown;
    palette[10] = c64_lightred;
    palette[11] = c64_grey1;
    palette[12] = c64_grey2;
    palette[13] = c64_lightgreen;
    palette[14] = c64_lightblue;
    palette[15] = c64_grey3;

    init();

    // Create main buffer
    Buffer* buffer = nasl_buffer_create(800,600);
    // Clear main buffer to a light grey color
    nasl_buffer_clear(buffer, c64_lightblue);

    // Create a sub_buffer
    Buffer* sub_buffer = nasl_buffer_get_subbuffer(buffer, 50, 50, 700, 400);
    nasl_buffer_clear(sub_buffer, c64_black);
    int palx = 0;
    for (int j = 0; j < sub_buffer->height; j++)
    {
        for (int i = 0; i < sub_buffer->width; i++)
        {
            if(j % 25 == 0)
            {
                palx++;
            }
            if(palx > 16) palx = 0;
            nasl_buffer_set_pixel(sub_buffer, i, j, palette[palx]);
        }
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
