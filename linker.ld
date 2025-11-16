/* linker.ld */

ENTRY(_start)

SECTIONS
{
    /* Load the kernel at 1MB, where GRUB usually places kernels */
    . = 1M;

    .text :
    {
        *(.multiboot)   /* keep multiboot header at the start */
        *(.text*)
    }

    .rodata :
    {
        *(.rodata*)
    }

    .data :
    {
        *(.data*)
    }

    .bss :
    {
        *(.bss*)
        *(COMMON)
    }
}
