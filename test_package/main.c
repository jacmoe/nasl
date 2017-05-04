#include <stdio.h>

#include "nasl_script.h"

int main()
{
    nasl_script_init();
    printf("hey man\n");
    printf("%#08x\n", GREY3);
    nasl_script_shutdown();
}
