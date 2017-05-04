#include <stdio.h>
#include <stdlib.h>
#include "script.h"
#include <assert.h>
#include <stdarg.h>

struct mb_interpreter_t *bas;


static void _on_error(struct mb_interpreter_t *s, mb_error_e e, char *m, int p)
{
    if (SE_NO_ERR != e)
    {
        printf("Error : [POS] %d, [CODE] %d, [MESSAGE] %s\n", p, e, m);
    }
}

static int my_print(const char *fmt, ...)
{
    char buf[1024];
    va_list argptr;
    va_start(argptr, fmt);
    vsnprintf(buf, sizeof(buf), fmt, argptr);
    va_end(argptr);
    printf(buf);
    return MB_FUNC_OK;
}

static int sys(struct mb_interpreter_t* s, void** l) {
	int result = MB_FUNC_OK;
	char* arg = 0;

	mb_assert(s && l);

	mb_check(mb_attempt_open_bracket(s, l));

	mb_check(mb_pop_string(s, l, &arg));

	mb_check(mb_attempt_close_bracket(s, l));

	if(arg)
		system(arg);

	return result;
}


static int newline(struct mb_interpreter_t* s, void** l) {
	int result = MB_FUNC_OK;

	mb_assert(s && l);

	mb_check(mb_attempt_func_begin(s, l));

	mb_check(mb_attempt_func_end(s, l));

	putchar('\n');

	return result;
}

void nasl_script_init()
{
    mb_init();
    printf("Running MY-BASIC %s\n", mb_ver_string());
}

void nasl_script_run(char* file)
{
    mb_open(&bas);
    mb_set_error_handler(bas, _on_error);
    mb_set_printer(bas, my_print);
    mb_reg_fun(bas, sys);
    mb_reg_fun(bas, newline);
    mb_load_file(bas, file);
    mb_run(bas);
    mb_close(&bas);
}

void nasl_script_shutdown()
{
    mb_dispose();
    printf("Shutting down MY-BASIC\n");
}
