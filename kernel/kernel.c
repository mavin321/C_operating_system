/* kernel/kernel.c */
#include <stddef.h>
#include <stdint.h>
#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "timer.h"
#include "keyboard.h"
#include "memory.h"
#include "multiboot.h"
#include "graphics.h"

static inline void enable_interrupts(void) {
    __asm__ volatile ("sti");
}

void kernel_main(uint32_t magic, uint32_t mbi_addr)
{
    (void) magic; // ignore for now if you want

    multiboot_info_t* mbi = (multiboot_info_t*)mbi_addr;

    // Initialize text terminal first (for debugging/logging)
    terminal_initialize();
    terminal_write_string("Welcome to MyOS!\n");
    terminal_write_string("Switching to graphics (macOS-style GUI)...\n");

    // Initialize GDT, IDT, ISRs, IRQs, heap, timer, keyboard as before
    terminal_write_string("Initializing GDT...\n");
    gdt_install();

    terminal_write_string("Initializing IDT...\n");
    idt_install();

    terminal_write_string("Installing ISRs...\n");
    isr_install();

    terminal_write_string("Installing IRQs...\n");
    irq_install();

    terminal_write_string("Initializing heap...\n");
    kheap_init();

    terminal_write_string("Installing timer (100Hz)...\n");
    timer_install(100);

    terminal_write_string("Installing keyboard...\n");
    keyboard_install();

    terminal_write_string("Enabling interrupts...\n");
    enable_interrupts();

    // Initialize graphics from Multiboot framebuffer info
    if (graphics_init_from_multiboot(mbi) == 0) {
        terminal_write_string("Graphics initialized. Drawing macOS-style desktop...\n");

        gui_draw_desktop();
        gui_draw_menu_bar();
        gui_draw_dock();
        gui_draw_macos_window(200, 150, 600, 400);
    } else {
        terminal_write_string("Failed to initialize graphics. Staying in text mode.\n");
    }

    terminal_write_string("System initialized.\n");

    while (1) {
        __asm__ volatile("hlt");
    }
}
