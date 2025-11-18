/* kernel/timer.c */
#include "timer.h"
#include "io.h"
#include "irq.h"
#include "terminal.h"

static volatile uint32_t tick = 0;

static void timer_callback(void)
{
    tick++;
    // Uncomment to see spammy ticks:
    // terminal_write_string("Tick\n");
}

uint32_t timer_ticks(void)
{
    return tick;
}

void timer_install(uint32_t frequency)
{
    irq_install_handler(0, timer_callback);

    uint32_t divisor = 1193180 / frequency;

    outb(0x43, 0x36);
    outb(0x40, (uint8_t)(divisor & 0xFF));
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}
