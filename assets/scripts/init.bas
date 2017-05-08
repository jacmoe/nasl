import "constants.bas"

' Create a blit buffer from main buffer
blitbuf = sub_buffer(main_buffer, 10,10, 100, 100)

' Clear blit buffer to orange
buffer_clear(blitbuf, ORANGE)

' Draw a cross hair
for pix = 10 to 13
    buffer_set_pixel(blitbuf, pix, pix, BROWN)
next pix
offset = 13
for pix = 10 to 13
    buffer_set_pixel(blitbuf, pix, offset, BROWN)
    offset = offset - 1
next pix

' Print a color from a pixel
print "Pixel : ", buffer_get_pixel(blitbuf, 10, 10), "!";

' Blit buffer to main buffer
buffer_blit(main_buffer, blitbuf, 50, 10)

' Destroy blit buffer
buffer_destroy(blitbuf)
