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

static inline void enable_interrupts(void) {
    __asm__ volatile ("sti");
}

void kernel_main(void) {
    terminal_initialize();

    terminal_write_string("Welcome to MyOS!\n");
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

    terminal_write_string("System initialized. Type on your keyboard!\n");

    while (1) {
        __asm__ volatile("hlt");
    }
}
