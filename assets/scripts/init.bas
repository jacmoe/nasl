import "constants.bas"

src = buffer_create(10,10)

buffer_clear(src, ORANGE)

buffer_blit(main_buffer, src, 50, 10)

buffer_destroy(src)
