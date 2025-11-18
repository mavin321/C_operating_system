/* kernel/irq.c */
#include "irq.h"
#include "idt.h"
#include "io.h"

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

static irq_handler_t irq_routines[16] = { 0 };

void irq_install_handler(int irq, irq_handler_t handler)
{
    if (irq < 16)
        irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
    if (irq < 16)
        irq_routines[irq] = 0;
}

static void irq_remap(void)
{
    // Remap PIC:
    // Master PIC: command 0x20, data 0x21
    // Slave PIC : command 0xA0, data 0xA1
    outb(0x20, 0x11);
    io_wait();
    outb(0xA0, 0x11);
    io_wait();

    outb(0x21, 0x20); // Master offset 0x20 (32)
    io_wait();
    outb(0xA1, 0x28); // Slave offset 0x28 (40)
    io_wait();

    outb(0x21, 0x04);
    io_wait();
    outb(0xA1, 0x02);
    io_wait();

    outb(0x21, 0x01);
    io_wait();
    outb(0xA1, 0x01);
    io_wait();

    // Mask interrupts
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void irq_install(void)
{
    irq_remap();

    idt_set_gate(32, (uint32_t)irq0,  0x08, 0x8E);
    idt_set_gate(33, (uint32_t)irq1,  0x08, 0x8E);
    idt_set_gate(34, (uint32_t)irq2,  0x08, 0x8E);
    idt_set_gate(35, (uint32_t)irq3,  0x08, 0x8E);
    idt_set_gate(36, (uint32_t)irq4,  0x08, 0x8E);
    idt_set_gate(37, (uint32_t)irq5,  0x08, 0x8E);
    idt_set_gate(38, (uint32_t)irq6,  0x08, 0x8E);
    idt_set_gate(39, (uint32_t)irq7,  0x08, 0x8E);
    idt_set_gate(40, (uint32_t)irq8,  0x08, 0x8E);
    idt_set_gate(41, (uint32_t)irq9,  0x08, 0x8E);
    idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
    idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
    idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
    idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
    idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
    idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);
}

void irq_handler(uint32_t int_no, uint32_t err_code)
{
    (void)err_code;

    int irq = int_no - 32;

    if (irq >= 0 && irq < 16) {
        if (irq_routines[irq]) {
            irq_routines[irq]();
        }
    }

    // Send EOI to PICs
    if (int_no >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
}
