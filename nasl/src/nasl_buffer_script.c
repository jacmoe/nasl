#include "nasl_buffer.h"
#include "nasl_script.h"

static int _buffer_create(struct mb_interpreter_t* s, void** l);
static int _buffer_destroy(struct mb_interpreter_t* s, void* l);

int nasl_buffer_script_init()
{
    mb_register_func(nasl_script_get_interpreter(), "BUFFER_CREATE", _buffer_create);
    mb_register_func(nasl_script_get_interpreter(), "BUFFER_DESTROY", _buffer_destroy);
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

static int _buffer_destroy(struct mb_interpreter_t* s, void* l)
{
	int result = MB_FUNC_OK;
	Buffer* buf = 0;
	void* up = 0;

	mb_assert(s && l);

	mb_check(mb_attempt_open_bracket(s, l));

	mb_check(mb_pop_usertype(s, l, &up));

	mb_check(mb_attempt_close_bracket(s, l));

	if(!up)
		return MB_FUNC_ERR;

	buf = (Buffer*)up;
    nasl_buffer_destroy(buf);

	return result;
}
