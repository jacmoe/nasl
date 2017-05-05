#include "nasl_draw.h"
#include <stdlib.h> // for abs
#include <stdarg.h> // for va_start, etc.


// Doom's version of Bresenham
void nasl_draw_line(Buffer *b, int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = x1 - x0;
    int ax = 2 * abs(dx);
    int sx = dx < 0 ? -1 : 1;

    int dy = y1 - y0;
    int ay = 2 * abs(dy);
    int sy = dy < 0 ? -1 : 1;

    int x = x0;
    int y = y0;

    if (ax > ay) {
        int d = ay - ax / 2;
        while (1) {
            nasl_buffer_set_pixel(b, x, y, color);
            if (x == x1) return;

            if (d >= 0) {
                y += sy;
                d -= ax;
            }
            x += sx;
            d += ay;
        }
    } else {
        int d = ax - ay / 2;
        while (1) {
            nasl_buffer_set_pixel(b, x, y, color);
            if (y == y1) return;

            if (d >= 0) {
                x += sx;
                d -= ay;
            }
            y += sy;
            d += ax;
        }
    }
}

void nasl_draw_text(Buffer *b, SpriteSheet ascii, int x, int y, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char text[128] = "";
    vsnprintf(text, 128, fmt, args);

    va_end(args);

    for (int i = 0; i < strlen(text); i++) {
        unsigned char c = text[i];

        int xx = c % 16;
        int yy = c / 16;

        Buffer *bitmap = nasl_sprite_get(ascii, xx, yy);

        nasl_buffer_blit(b, bitmap, x + i * 8, y);
    }
}
