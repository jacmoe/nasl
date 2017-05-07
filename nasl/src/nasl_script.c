#include "nasl_script.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

static struct mb_interpreter_t* bas = 0;

static void _on_error(struct mb_interpreter_t* s, mb_error_e e, char* m, char* f, int p, unsigned short row, unsigned short col, int abort_code) {
	mb_unrefvar(s);
	mb_unrefvar(p);

	if(e != SE_NO_ERR) {
		if(f) {
			if(e == SE_RN_WRONG_FUNCTION_REACHED) {
				printf(
					"Error:\n    Ln %d, Col %d in Func: %s\n    Code %d, Abort Code %d\n    Message: %s.\n",
					row, col, f,
					e, abort_code,
					m
				);
			} else {
				printf(
					"Error:\n    Ln %d, Col %d in File: %s\n    Code %d, Abort Code %d\n    Message: %s.\n",
					row, col, f,
					e, e == SE_EA_EXTENDED_ABORT ? abort_code - MB_EXTENDED_ABORT : abort_code,
					m
				);
			}
		} else {
			printf(
				"Error:\n    Ln %d, Col %d\n    Code %d, Abort Code %d\n    Message: %s.\n",
				row, col,
				e, e == SE_EA_EXTENDED_ABORT ? abort_code - MB_EXTENDED_ABORT : abort_code,
				m
			);
		}
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

static int _on_import(struct mb_interpreter_t* s, const char* p)
{
/*	if(!importing_dirs)
		return MB_FUNC_ERR;

	if(!_try_import(s, p))
		return MB_FUNC_ERR;
*/
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
    mb_open(&bas);
    mb_set_error_handler(bas, _on_error);
    mb_set_printer(bas, my_print);
    mb_reg_fun(bas, sys);
    mb_reg_fun(bas, newline);
    printf("*** MY-BASIC %s ***\n", mb_ver_string());
}

struct mb_interpreter_t* nasl_script_get_interpreter()
{
    return bas;
}

void nasl_script_run(char* file)
{
    mb_load_file(bas, file);
    mb_run(bas);
}

void nasl_script_shutdown()
{
    mb_close(&bas);
    mb_dispose();
    printf("*** MY-BASIC Shutdown ***\n");
}
