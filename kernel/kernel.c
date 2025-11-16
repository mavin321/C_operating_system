/* kernel/kernel.c */
#include <stddef.h>
#include <stdint.h>
#include "terminal.h"

void kernel_main(void) {
    terminal_initialize();

    terminal_write_string("Welcome to MyOS!\n");
    terminal_write_string("You just booted your own operating system written in C.\n\n");

    terminal_write_string("Next steps:\n");
    terminal_write_string(" - Implement GDT and IDT\n");
    terminal_write_string(" - Handle hardware interrupts (timer, keyboard)\n");
    terminal_write_string(" - Add a simple shell\n");
}
