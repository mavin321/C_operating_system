/* kernel/keyboard.c */
#include "keyboard.h"
#include "irq.h"
#include "io.h"
#include "terminal.h"

// Very minimal US QWERTY scancode set 1 map for letters & digits only:
static unsigned char kbd_scancode_to_ascii[128] = {
    0,  27, '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '\b', /* Backspace */
    '\t',                               /* Tab */
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p', '[', ']', '\n',           /* Enter key */
    0,                                  /* Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k',
    'l', ';', '\'', '`',
    0,                                  /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
    ',', '.', '/', 0,                   /* Right shift */
    '*',
    0,  /* Alt */
    ' ',/* Space bar */
    /* Everything else: 0 */
};

static void keyboard_callback(void)
{
    uint8_t scancode = inb(0x60);

    if (scancode & 0x80) {
        // Key release; ignore
    } else {
        unsigned char c = kbd_scancode_to_ascii[scancode];
        if (c) {
            terminal_putchar(c);
        }
    }
}

void keyboard_install(void)
{
    irq_install_handler(1, keyboard_callback);
}
