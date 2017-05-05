#ifndef NASLDRAW_H
#define NASLDRAW_H

#include <stdint.h>
#include "nasl_buffer.h"
#include "nasl_sprite.h"

void nasl_draw_line(Buffer *b, int x0, int y0, int x1, int y1, uint32_t color);
void nasl_draw_text(Buffer *b, SpriteSheet ascii, int x, int y, const char *fmt, ...);

#endif /* NASLDRAW_H */
