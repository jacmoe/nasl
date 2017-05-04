#include <stdio.h>

#include "nasl_script.h"
#include "nasl_color.h"

int main()
{
    nasl_script_init();
    printf("Printing colors:\n");
    printf("YELLOW : %#08x\n", YELLOW);
    printf("c64_palette[7] : %#08x\n", c64_palette[7]);
    nasl_script_shutdown();
}
