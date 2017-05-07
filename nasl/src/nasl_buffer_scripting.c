#include "nasl_buffer.h"
#include "nasl_script.h"

static int _buffer_create(struct mb_interpreter_t* s, void** l);

int nasl_buffer_scripting_init()
{
    mb_register_func(nasl_script_get_interpreter(), "SCRIPT_INIT", _buffer_create);
    return 1;
}

static int _buffer_create(struct mb_interpreter_t* s, void** l)
{
	int result = MB_FUNC_OK;
	Buffer* buf = 0;
    int width;
    int height;

	mb_assert(s && l);

	mb_check(mb_attempt_open_bracket(s, l));

	mb_check(mb_pop_int(s, l, &width));

	mb_check(mb_pop_int(s, l, &height));

	mb_check(mb_attempt_close_bracket(s, l));

	if(!width || !height) {
		result = MB_FUNC_ERR;

		goto _exit;
	}

	buf = nasl_buffer_create(width, height);
	if(!buf) {
		result = MB_FUNC_ERR;

		goto _exit;
	}

_exit:
	mb_check(mb_push_usertype(s, l, (void*)buf));

	return result;
}
