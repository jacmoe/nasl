#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "buffer.h"
#include "color.h"

Buffer *buffer_create(int width, int height)
{
    Buffer *b = malloc(sizeof(Buffer));

    b->width = width;
    b->height = height;

    b->pixels = malloc(sizeof(uint32_t) * width * height);
    memset(b->pixels, 0, sizeof(uint32_t) * width * height);

    return b;
}

void buffer_clear(Buffer *b, uint32_t color)
{
    for (int i = 0; i < b->width * b->height; i++)
    {
        b->pixels[i] = color;
    }
}

uint32_t buffer_pixel_get(Buffer *b, int x, int y)
{
    return b->pixels[y * b->width + x];
}

Buffer *buffer_get_subbuffer(Buffer *buf, int x, int y, int width, int height)
{
    assert(x + width <= buf->width);
    assert(y + height <= buf->height);

    Buffer *b = buffer_create(width, height);

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            buffer_pixel_set(b, i, j, buffer_pixel_get(buf, x + i, y + j));
        }
    }

    return b;
}

void buffer_blit(Buffer *dest, Buffer *src, int x, int y)
{
    assert(x + src->width <= dest->width);
    assert(y + src->height <= dest->height);

    for (int j = 0; j < src->height; j++)
    {
        for (int i = 0; i < src->width; i++)
        {
            uint32_t src_pixel = buffer_pixel_get(src, i, j);
            if (src_pixel != TRANSPARENT)
            {
                buffer_pixel_set(dest, i + x, j + y, src_pixel);
            }
        }
    }
}

void buffer_delete(Buffer *buf)
{
    free(buf->pixels);
    free(buf);
}
