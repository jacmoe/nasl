#include <stdio.h>

#include "nasl_script.h"

int main()
{
    nasl_script_init();
    printf("hey man\n");
    nasl_script_shutdown();
}
