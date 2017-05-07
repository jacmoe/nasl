print "Hello Basic!"

import "assets/scripts/test.bas"

src = buffer_create(10,10)
dst = main_buffer

buffer_clear(src, 0x7777FF)

buffer_blit(dst, src, 50, 10)

buffer_destroy(buffer)
