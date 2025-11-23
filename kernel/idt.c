/* kernel/idt.c */
#include "idt.h"

struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern void idt_flush(void);

struct idt_entry idt[256];
struct idt_ptr   idtp;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel     = sel;
    idt[num].always0 = 0;
    idt[num].flags   = flags;  // | 0x60 if user-level
}

void idt_install(void)
{
    idtp.limit = sizeof(struct idt_entry) * 256 - 1;
    idtp.base  = (uint32_t)&idt;

    // Clear IDT
    for (int i = 0; i < 256; i++) {
        idt[i].base_lo = 0;
        idt[i].base_hi = 0;
        idt[i].sel     = 0;
        idt[i].always0 = 0;
        idt[i].flags   = 0;
    }

    idt_flush();
}
