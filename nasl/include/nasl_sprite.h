//------------------------------------------------------------------------------
// Sprite sheets
//------------------------------------------------------------------------------
#ifndef NASLSPRITE_H
#define NASLSPRITE_H

#include "nasl_buffer.h"

typedef struct SpriteSheet {
    Buffer **sprites;
    int rows, cols;
    int width, height;
} SpriteSheet;


SpriteSheet nasl_sprite_load(const char *path, int rows, int cols);
Buffer* nasl_sprite_get(SpriteSheet ss, int x, int y);
void nasl_sprite_delete(SpriteSheet ss);

#endif // NASLSPRITE_H