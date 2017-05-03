#ifndef NASLGRAPHICS_H
#define NASLGRAPHICS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int nasl_graphics_init(int width, int height);
int nasl_graphics_shutdown();

int nasl_graphics_running();

void nasl_graphics_poll_events();

void nasl_graphics_present();

#endif /* NASLGRAPHICS_H */
