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

int main()
{
    nasl_script_init();
    nasl_script_run("assets/scripts/init.bas");

    nasl_graphics_init(800,600);

    while(nasl_graphics_running())
    {
        nasl_graphics_poll_events();
        nasl_graphics_present();
    }

    nasl_graphics_shutdown();

    nasl_script_shutdown();

}
