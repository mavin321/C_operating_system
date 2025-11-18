; kernel/isr_asm.s
BITS 32

global isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7
global isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15
global isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23
global isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31

global irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7
global irq8, irq9, irq10, irq11, irq12, irq13, irq14, irq15

extern isr_handler
extern irq_handler

%macro ISR_NOERR 1
isr%1:
    cli
    pusha
    push dword 0       ; error code
    push dword %1      ; interrupt number
    call isr_handler
    add esp, 8
    popa
    sti
    iretd
%endmacro

%macro ISR_ERR 1
isr%1:
    cli
    pusha
    push dword %1      ; interrupt number
    push dword 0       ; dummy error (simplified)
    ; If you want real error codes for these, adjust & decode in C.
    call isr_handler
    add esp, 8
    popa
    sti
    iretd
%endmacro

; For simplicity we treat all as NOERR here:
ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_NOERR 8
ISR_NOERR 9
ISR_NOERR 10
ISR_NOERR 11
ISR_NOERR 12
ISR_NOERR 13
ISR_NOERR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31

%macro IRQ_STUB 2
irq%1:
    cli
    pusha
    push dword 0        ; error code
    push dword %2       ; interrupt number (32+IRQn)
    call irq_handler
    add esp, 8
    popa
    sti
    iretd
%endmacro

IRQ_STUB 0, 32
IRQ_STUB 1, 33
IRQ_STUB 2, 34
IRQ_STUB 3, 35
IRQ_STUB 4, 36
IRQ_STUB 5, 37
IRQ_STUB 6, 38
IRQ_STUB 7, 39
IRQ_STUB 8, 40
IRQ_STUB 9, 41
IRQ_STUB 10, 42
IRQ_STUB 11, 43
IRQ_STUB 12, 44
IRQ_STUB 13, 45
IRQ_STUB 14, 46
IRQ_STUB 15, 47
