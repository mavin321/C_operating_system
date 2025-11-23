; boot/boot.s — NASM syntax Multiboot header + entry point

BITS 32

SECTION .multiboot
align 4

MAGIC     equ 0x1BADB002
FLAGS     equ 1<<0 | 1<<1
CHECKSUM  equ -(MAGIC + FLAGS)

dd MAGIC
dd FLAGS
dd CHECKSUM

SECTION .text
global _start
extern kernel_main

_start:
    cli
    call kernel_main

.hang:
    hlt
    jmp .hang
