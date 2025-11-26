; boot/boot.s — Multiboot header + entry point, NASM syntax

BITS 32

SECTION .multiboot
align 4

MAGIC     equ 0x1BADB002
FLAGS     equ (1<<0) | (1<<1) | (1<<2)   ; align, mem info, framebuffer request
CHECKSUM  equ -(MAGIC + FLAGS)

dd MAGIC
dd FLAGS
dd CHECKSUM

; Framebuffer request (Multiboot video mode)
dd 0              ; mode_type: 0 = linear graphics framebuffer
dd 1024           ; width
dd 768            ; height
dd 32             ; bits per pixel

SECTION .text
global _start
extern kernel_main

_start:
    ; On Multiboot, GRUB enters here with:
    ;  EAX = multiboot magic
    ;  EBX = pointer to multiboot info struct

    cli

    push ebx        ; arg1: multiboot info pointer
    push eax        ; arg0: magic
    call kernel_main

.hang:
    hlt
    jmp .hang
