#pragma once

#include <stdbool.h>

void pspgu_renderer_begin(int *pixels, int width, int height);
bool pspgu_renderer_gouraud(int x0, int y0, int x1, int y1, int x2, int y2, int color0, int color1, int color2, int alpha);
bool pspgu_renderer_flat(int x0, int y0, int x1, int y1, int x2, int y2, int color, int alpha);
void pspgu_renderer_fallback(void);
void pspgu_renderer_end(void);
