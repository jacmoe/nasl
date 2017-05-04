#include "color.h"

uint32_t color_scale(uint32_t c, double intensity)
{
    uint8_t red = GETR(c);
    uint8_t green = GETG(c);
    uint8_t blue = GETB(c);

    red *= intensity;
    green *= intensity;
    blue *= intensity;

    return BUILDRGB(red, green, blue);
}
