; kernel/idt_asm.s
BITS 32

global idt_flush
extern idtp

idt_flush:
    lidt [idtp]
    ret
