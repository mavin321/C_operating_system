/* kernel/graphics.c */
#include "graphics.h"

framebuffer_t fb = {0};

int graphics_init_from_multiboot(multiboot_info_t* mbi)
{
    // Check that framebuffer info is available
    if (!mbi) return -1;

    fb.addr  = (uint32_t*) mbi->framebuffer_addr;
    fb.pitch = mbi->framebuffer_pitch;
    fb.width = mbi->framebuffer_width;
    fb.height = mbi->framebuffer_height;
    fb.bpp   = mbi->framebuffer_bpp;

    if (!fb.addr || fb.bpp != 32) {
        // For now we only support 32-bit ARGB
        return -1;
    }

    return 0;
}

uint32_t gfx_lerp_color(uint32_t c1, uint32_t c2, float t)
{
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    uint8_t a1 = (c1 >> 24) & 0xFF;
    uint8_t r1 = (c1 >> 16) & 0xFF;
    uint8_t g1 = (c1 >> 8) & 0xFF;
    uint8_t b1 = c1 & 0xFF;

    uint8_t a2 = (c2 >> 24) & 0xFF;
    uint8_t r2 = (c2 >> 16) & 0xFF;
    uint8_t g2 = (c2 >> 8) & 0xFF;
    uint8_t b2 = c2 & 0xFF;

    uint8_t a = (uint8_t)(a1 + (a2 - a1) * t);
    uint8_t r = (uint8_t)(r1 + (r2 - r1) * t);
    uint8_t g = (uint8_t)(g1 + (g2 - g1) * t);
    uint8_t b = (uint8_t)(b1 + (b2 - b1) * t);

    return (a << 24) | (r << 16) | (g << 8) | b;
}

void gfx_putpixel(int x, int y, uint32_t color)
{
    if (x < 0 || y < 0 || x >= (int)fb.width || y >= (int)fb.height) return;
    uint32_t* pixel = (uint32_t*)((uint8_t*)fb.addr + y * fb.pitch) + x;
    *pixel = color;
}

void gfx_clear(uint32_t color)
{
    for (uint32_t y = 0; y < fb.height; y++) {
        uint32_t* row = (uint32_t*)((uint8_t*)fb.addr + y * fb.pitch);
        for (uint32_t x = 0; x < fb.width; x++) {
            row[x] = color;
        }
    }
}

void gfx_fill_rect(int x, int y, int w, int h, uint32_t color)
{
    for (int yy = 0; yy < h; yy++) {
        int py = y + yy;
        if (py < 0 || py >= (int)fb.height) continue;

        uint32_t* row = (uint32_t*)((uint8_t*)fb.addr + py * fb.pitch);
        for (int xx = 0; xx < w; xx++) {
            int px = x + xx;
            if (px < 0 || px >= (int)fb.width) continue;
            row[px] = color;
        }
    }
}

/* Helper for rounded corners */
static int inside_circle(int dx, int dy, int r)
{
    return dx*dx + dy*dy <= r*r;
}

void gfx_fill_rounded_rect(int x, int y, int w, int h, int radius, uint32_t color)
{
    if (radius <= 0) {
        gfx_fill_rect(x, y, w, h, color);
        return;
    }

    for (int yy = 0; yy < h; yy++) {
        int py = y + yy;
        if (py < 0 || py >= (int)fb.height) continue;

        for (int xx = 0; xx < w; xx++) {
            int px = x + xx;
            if (px < 0 || px >= (int)fb.width) continue;

            int corner = 0;

            // Top-left corner
            if (xx < radius && yy < radius) {
                int dx = radius - xx;
                int dy = radius - yy;
                if (!inside_circle(dx, dy, radius)) { corner = 1; }
            }
            // Top-right
            else if (xx >= w - radius && yy < radius) {
                int dx = xx - (w - radius - 1);
                int dy = radius - yy;
                if (!inside_circle(dx, dy, radius)) { corner = 1; }
            }
            // Bottom-left
            else if (xx < radius && yy >= h - radius) {
                int dx = radius - xx;
                int dy = yy - (h - radius - 1);
                if (!inside_circle(dx, dy, radius)) { corner = 1; }
            }
            // Bottom-right
            else if (xx >= w - radius && yy >= h - radius) {
                int dx = xx - (w - radius - 1);
                int dy = yy - (h - radius - 1);
                if (!inside_circle(dx, dy, radius)) { corner = 1; }
            }

            if (!corner) {
                gfx_putpixel(px, py, color);
            }
        }
    }
}

/* macOS-like vibrant wallpaper */
void gui_draw_wallpaper(void)
{
    uint32_t stops[] = {
        0xFF0D2B52, // deep indigo
        0xFF2D6CC3, // ocean blue
        0xFF9A3BEA, // violet
        0xFFFF7A18  // warm orange
    };

    for (uint32_t y = 0; y < fb.height; y++) {
        float ty = (float)y / (float)(fb.height ? fb.height : 1);
        float band = ty * 2.5f; // spread vertical transitions
        int idx = (int)band;
        if (idx < 0) idx = 0;
        if (idx > 2) idx = 2;
        float local = band - (float)idx;

        uint32_t base = gfx_lerp_color(stops[idx], stops[idx + 1], local);

        for (uint32_t x = 0; x < fb.width; x++) {
            float tx = (float)x / (float)(fb.width ? fb.width : 1);

            /* subtle diagonal blend to give motion */
            float diag = (tx * 0.35f) + (ty * 0.65f);
            uint32_t color = gfx_lerp_color(base, 0xFFFFFFFF, diag * 0.08f);

            /* soft spotlight near top-left */
            float dx = tx - 0.3f;
            float dy = ty - 0.25f;
            float dist2 = dx * dx + dy * dy;
            if (dist2 < 0.06f) {
                float glow = (0.06f - dist2) / 0.06f;
                color = gfx_lerp_color(color, 0x80FFFFFF, glow * 0.5f);
            }

            uint32_t* pixel = (uint32_t*)((uint8_t*)fb.addr + y * fb.pitch) + x;
            *pixel = color;
        }
    }
}

/* macOS-like dark gradient desktop with overlay */
void gui_draw_desktop(void)
{
    gui_draw_wallpaper();

    /* slight vignette on edges for depth */
    for (uint32_t y = 0; y < fb.height; y++) {
        float ty = (float)y / (float)(fb.height ? fb.height : 1);
        for (uint32_t x = 0; x < fb.width; x++) {
            float tx = (float)x / (float)(fb.width ? fb.width : 1);
            float edge = (tx < 0.05f || tx > 0.95f || ty < 0.05f || ty > 0.95f) ? 0.12f : 0.0f;
            if (edge > 0.0f) {
                uint32_t* pixel = (uint32_t*)((uint8_t*)fb.addr + y * fb.pitch) + x;
                *pixel = gfx_lerp_color(*pixel, 0xFF000000, edge);
            }
        }
    }
}

/* Simple frosted-glass menu bar */
void gui_draw_menu_bar(void)
{
    int h = 32;
    uint32_t bar = 0xCCF6F7F9;
    uint32_t highlight = 0xFFFFFFFF;
    gfx_fill_rect(0, 0, (int)fb.width, h, bar);
    gfx_fill_rect(0, h - 1, (int)fb.width, 1, gfx_lerp_color(bar, 0xFFB0B0B0, 0.25f));
    gfx_fill_rect(0, 0, (int)fb.width, 1, highlight);
}

/* macOS-style Dock */
void gui_draw_dock(void)
{
    int w = (int)(fb.width * 0.6f);
    int h = 80;
    int x = (int)((fb.width - w) / 2);
    int y = (int)(fb.height - h - 20);

    uint32_t dock_color = 0xCC2C2C2E; // semi-opaque macOS-like dark

    gfx_fill_rounded_rect(x, y, w, h, 20, dock_color);

    // Simple "apps" blocks
    int icon_size = 48;
    int padding = 16;
    int count = 5;
    int total_width = count * icon_size + (count - 1) * padding;
    int start_x = x + (w - total_width) / 2;
    int icon_y = y + (h - icon_size) / 2;

    uint32_t colors[5] = {
        0xFF34C759, // green
        0xFF0A84FF, // blue
        0xFFFF9F0A, // orange
        0xFFFF375F, // pink/red
        0xFFBF5AF2  // purple
    };

    for (int i = 0; i < count; i++) {
        int ix = start_x + i * (icon_size + padding);
        gfx_fill_rounded_rect(ix, icon_y, icon_size, icon_size, 12, colors[i]);
    }
}

/* macOS-style window with title bar & traffic lights */
void gui_draw_macos_window(int x, int y, int w, int h)
{
    uint32_t body = 0xFFF5F5F7;   // light gray macOS window body
    uint32_t title = 0xFFD0D0D3;  // title bar

    int radius = 10;
    int title_height = 28;

    // Window body (minus title bar)
    gfx_fill_rounded_rect(x, y + title_height, w, h - title_height, radius, body);

    // Title bar (slightly overlapping)
    gfx_fill_rounded_rect(x, y, w, title_height + radius, radius, title);

    // Traffic light buttons
    int cx = x + 16;
    int cy = y + 10;
    int r = 6;

    // We approximate circles with small filled squares here (for simplicity)
    gfx_fill_rounded_rect(cx - r, cy - r, 2*r, 2*r, r, 0xFFFF605C); // red
    gfx_fill_rounded_rect(cx - r + 20, cy - r, 2*r, 2*r, r, 0xFFFFBD44); // yellow
    gfx_fill_rounded_rect(cx - r + 40, cy - r, 2*r, 2*r, r, 0xFF28C840); // green
}
