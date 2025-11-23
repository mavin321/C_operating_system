; kernel/gdt_asm.s
BITS 32

global gdt_flush
extern gdtp

gdt_flush:
    lgdt [gdtp]

    mov ax, 0x10       ; data segment selector (index 2)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:flush_cs  ; far jump to reload CS (code seg selector index 1)

flush_cs:
    ret
