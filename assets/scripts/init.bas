'/*
'*   This file is part of the
'* ███╗   ██╗ █████╗ ███████╗██╗     
'* ████╗  ██║██╔══██╗██╔════╝██║     
'* ██╔██╗ ██║███████║███████╗██║     
'* ██║╚██╗██║██╔══██║╚════██║██║     
'* ██║ ╚████║██║  ██║███████║███████╗
'* ╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚══════╝
'*   project : https://github.com/jacmoe/nasl
'*
'*   Copyright 2017 Jacob Moen
'*
'*/
import "constants.bas"

' Create a blit buffer from main buffer
blitbuf = sub_buffer(main_buffer(), 10,10, 30, 30)

' Clear blit buffer to orange
buffer_clear(blitbuf, ORANGE)

' Draw a cross hair
for pix = 10 to 13
    buffer_set_pixel(blitbuf, pix, pix, GREY1)
next pix
offset = 13
for pix = 10 to 13
    buffer_set_pixel(blitbuf, pix, offset, GREY1)
    offset = offset - 1
next pix

' Draw some lines
draw_line(blitbuf, 1, 5, 9, 1, RED)
draw_line(blitbuf, 9, 1, 1, 20, RED)
draw_line(blitbuf, 1, 20, 20, 20, RED)
draw_line(blitbuf, 20, 15, 20, 25, VIOLET)

' Blit buffer to main buffer
buffer_blit(main_buffer(), blitbuf, 50, 10)
' Destroy blit buffer
buffer_destroy(blitbuf)

' Load an image
image = image_load("assets/textures/sprite.png")
' Blit the image to main buffer
buffer_blit(main_buffer(), image, 220, 50)
' Destroy image buffer
buffer_destroy(image)

' Create ascii sprite
ascii = sprite_load("assets/fonts/ascii.png", 16, 16)
' Print some text
draw_text(main_buffer(), ascii, 120, 90, "BASIC!!")
' Delete ascii sprite
sprite_delete(ascii)

while graphics_running()
    graphics_poll_events()
    graphics_render(main_buffer())
    graphics_present()
wend
