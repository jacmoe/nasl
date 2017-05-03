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

#include "nasl/script.h"
#include "nasl/graphics.h"
#include "nasl/buffer.h"

static int init();
static int shutdown();

int main()
{
    init();

    Buffer* buffer = buffer_create(800,600);
    buffer_clear(buffer, GREY);
    buffer_pixel_set(buffer, 10,10, BUILDRGB(255,255,255));

    while(nasl_graphics_running())
    {
        nasl_graphics_poll_events();
        nasl_graphics_render(buffer);
        nasl_graphics_present();
    }

    buffer_delete(buffer);

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