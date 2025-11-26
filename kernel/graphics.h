/* kernel/graphics.h */
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include "multiboot.h"

typedef struct {
    uint32_t* addr;
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint32_t bpp;
} framebuffer_t;

extern framebuffer_t fb;

/* Initialize framebuffer from multiboot info */
int graphics_init_from_multiboot(multiboot_info_t* mbi);

/* Basic drawing */
void gfx_clear(uint32_t color);
void gfx_putpixel(int x, int y, uint32_t color);
void gfx_fill_rect(int x, int y, int w, int h, uint32_t color);
void gfx_fill_rounded_rect(int x, int y, int w, int h, int radius, uint32_t color);
uint32_t gfx_lerp_color(uint32_t c1, uint32_t c2, float t);

/* macOS-like desktop elements */
void gui_draw_desktop(void);
void gui_draw_wallpaper(void);
void gui_draw_menu_bar(void);
void gui_draw_dock(void);
void gui_draw_macos_window(int x, int y, int w, int h);

#endif /* GRAPHICS_H */
