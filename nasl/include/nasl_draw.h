#ifndef NASLDRAW_H
#define NASLDRAW_H

#include <stdint.h>
#include "nasl_buffer.h"

void nasl_draw_line(Buffer *b, int x0, int y0, int x1, int y1, uint32_t color);

#endif /* NASLDRAW_H */
