#include <stdbool.h>
#include <stdint.h>

#include "pspgu_renderer.h"

#ifdef __PSP__
#include <malloc.h>
#include <pspgu.h>
#include <pspkernel.h>

#include "../pix3d.h"

#define PSPGU_LIST_SIZE (256 * 1024)
#define PSPGU_VERTEX_COUNT 32766
#define PSPGU_TARGET_OFFSET ((void *)0x00088000)
#define PSPGU_TARGET_CPU ((uint32_t *)0x04088000)
#define PSPGU_STRIDE 512

typedef struct {
    uint32_t color;
    float x;
    float y;
    float z;
} GuVertex;

extern Pix3D _Pix3D;

static void *gu_list;
static GuVertex *vertices;
static int vertex_count;
static int *target_pixels;
static int target_width;
static int target_height;
static bool initialized;
static bool active;

static uint32_t pspgu_color(int rgb, int alpha) {
    uint32_t r = (uint32_t)(rgb >> 16) & 0xff;
    uint32_t g = (uint32_t)(rgb >> 8) & 0xff;
    uint32_t b = (uint32_t)rgb & 0xff;
    uint32_t a = (uint32_t)(256 - alpha);
    if (a > 255) {
        a = 255;
    }
    return (a << 24) | (b << 16) | (g << 8) | r;
}

static void pspgu_start_list(void) {
    sceGuStart(GU_DIRECT, gu_list);
}

static void pspgu_flush_vertices(bool wait) {
    if (vertex_count == 0) {
        return;
    }
    sceKernelDcacheWritebackRange(vertices, vertex_count * (int)sizeof(*vertices));
    sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D, vertex_count, NULL, vertices);
    vertex_count = 0;
    if (wait) {
        sceGuFinish();
        sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);
    }
}

static void pspgu_copy_target(void) {
    if (!target_pixels) {
        return;
    }
    for (int y = 0; y < target_height; y++) {
        const uint32_t *src = PSPGU_TARGET_CPU + y * PSPGU_STRIDE;
        int *dst = target_pixels + y * target_width;
        for (int x = 0; x < target_width; x++) {
            uint32_t p = src[x];
            dst[x] = (int)(((p & 0xff) << 16) | (p & 0xff00) | ((p >> 16) & 0xff));
        }
    }
}

static void pspgu_queue_vertex(int x, int y, int rgb, int alpha) {
    GuVertex *v = &vertices[vertex_count++];
    v->color = pspgu_color(rgb, alpha);
    v->x = (float)x;
    v->y = (float)y;
    v->z = 0.0f;
}

static void pspgu_queue_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int c0, int c1, int c2, int alpha) {
    if (!active) {
        return;
    }
    if (vertex_count > PSPGU_VERTEX_COUNT - 3) {
        pspgu_flush_vertices(true);
        pspgu_start_list();
    }
    pspgu_queue_vertex(x0, y0, c0, alpha);
    pspgu_queue_vertex(x1, y1, c1, alpha);
    pspgu_queue_vertex(x2, y2, c2, alpha);
}

void pspgu_renderer_begin(int *pixels, int width, int height) {
    if (!pixels || width <= 0 || height <= 0 || width > PSPGU_STRIDE || height > 272) {
        return;
    }
    if (!initialized) {
        gu_list = memalign(16, PSPGU_LIST_SIZE);
        vertices = memalign(16, PSPGU_VERTEX_COUNT * sizeof(*vertices));
        if (!gu_list || !vertices) {
            free(gu_list);
            free(vertices);
            gu_list = NULL;
            vertices = NULL;
            return;
        }
        sceGuInit();
        initialized = true;
    }

    target_pixels = pixels;
    target_width = width;
    target_height = height;
    vertex_count = 0;
    pspgu_start_list();
    sceGuDrawBufferList(GU_PSM_8888, PSPGU_TARGET_OFFSET, PSPGU_STRIDE);
    sceGuOffset(2048 - width / 2, 2048 - height / 2);
    sceGuViewport(2048, 2048, width, height);
    sceGuScissor(0, 0, width, height);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuDisable(GU_DEPTH_TEST);
    sceGuDisable(GU_CULL_FACE);
    sceGuDisable(GU_TEXTURE_2D);
    sceGuShadeModel(GU_SMOOTH);
    sceGuEnable(GU_BLEND);
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
    sceGuClearColor(0xff000000);
    sceGuClear(GU_COLOR_BUFFER_BIT);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);
    active = true;
}

bool pspgu_renderer_gouraud(int x0, int y0, int x1, int y1, int x2, int y2, int color0, int color1, int color2, int alpha) {
    if (!active) {
        return false;
    }
    pspgu_queue_triangle(x0, y0, x1, y1, x2, y2,
                         _Pix3D.palette[color0 & 0xffff],
                         _Pix3D.palette[color1 & 0xffff],
                         _Pix3D.palette[color2 & 0xffff], alpha);
    return true;
}

bool pspgu_renderer_flat(int x0, int y0, int x1, int y1, int x2, int y2, int color, int alpha) {
    if (!active) {
        return false;
    }
    pspgu_queue_triangle(x0, y0, x1, y1, x2, y2, color, color, color, alpha);
    return true;
}

void pspgu_renderer_fallback(void) {
    if (!active) {
        return;
    }
    pspgu_flush_vertices(true);
    pspgu_copy_target();
    active = false;
}

void pspgu_renderer_end(void) {
    if (!active) {
        return;
    }
    pspgu_flush_vertices(true);
    pspgu_copy_target();
    active = false;
    target_pixels = NULL;
}

#else
void pspgu_renderer_begin(int *pixels, int width, int height) {(void)pixels; (void)width; (void)height;}
bool pspgu_renderer_gouraud(int x0, int y0, int x1, int y1, int x2, int y2, int color0, int color1, int color2, int alpha) {
    (void)x0; (void)y0; (void)x1; (void)y1; (void)x2; (void)y2; (void)color0; (void)color1; (void)color2; (void)alpha; return false;
}
bool pspgu_renderer_flat(int x0, int y0, int x1, int y1, int x2, int y2, int color, int alpha) {
    (void)x0; (void)y0; (void)x1; (void)y1; (void)x2; (void)y2; (void)color; (void)alpha; return false;
}
void pspgu_renderer_fallback(void) {}
void pspgu_renderer_end(void) {}
#endif
