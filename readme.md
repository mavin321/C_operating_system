# MyOS – A Tiny 32-bit Operating System in C

MyOS is a hobby 32-bit operating system written in C with a tiny bit of assembly.
It boots via GRUB, runs in QEMU, and writes directly to VGA text memory.

## Features (current)

- Multiboot-compliant kernel
- Custom boot entry in GRUB
- Minimal C runtime (no standard library)
- VGA text-mode terminal with scrolling

## Planned Features

- Global Descriptor Table (GDT)
- Interrupt Descriptor Table (IDT)
- Hardware interrupts (PIT timer, keyboard)
- Simple command-line shell
- Basic memory allocator

## Build & Run

```bash
sudo apt install build-essential nasm qemu-system-x86 xorriso grub-pc-bin
make
make run
```
