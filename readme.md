# 🚀 MyOS — A 32-bit Operating System Written in C & Assembly

MyOS is a hobby operating system written from scratch using **C** and **NASM assembly**.
It boots with GRUB, enters protected mode, initializes its own GDT, IDT, ISR/IRQ system, PIT timer, keyboard driver, and a basic heap allocator — all without using any standard library.

This project is designed to be clean, modular, and educational.
Perfect for learning **systems programming**, **computer architecture**, and **how operating systems actually work beneath the surface**.

---

# ✨ Current Features

### 🟦 Boot & Core Startup

- Multiboot-compliant kernel
- GRUB bootloader support
- 32-bit protected mode environment
- Custom linker script
- Complete freestanding C environment (no libc)

### 🟩 Display / Terminal

- VGA text-mode driver
- Scrolling terminal
- Custom printing routines

### 🟧 Descriptor Tables & CPU Setup

- Fully implemented **GDT**
- Fully implemented **IDT**
- CPU exception handlers (**ISR 0–31**)
- Basic interrupt-driven control flow

### 🟨 Hardware Interrupts

- PIC remapping
- IRQ handlers (**IRQ 0–15**)
- Interrupt-driven keyboard support
- Interrupt-driven PIT timer (configurable frequency)

### 🟥 Device Drivers

- Programmable Interval Timer (PIT)
- PS/2 Keyboard driver (scancode set 1)

### 🟪 Memory

- Simple bump allocator (`kmalloc`)
- Kernel heap initialization

---

# 📁 Project Structure

```
myos/
├── boot/
│   └── boot.s              # Multiboot header & entry point
│
├── kernel/
│   ├── kernel.c            # Main kernel entry
│   ├── terminal.c/.h       # VGA terminal driver
│   ├── gdt.c/.h/.s         # Global Descriptor Table
│   ├── idt.c/.h/.s         # Interrupt Descriptor Table
│   ├── isr.c/.h/.s         # CPU exceptions (ISR 0–31)
│   ├── irq.c/.h/.s         # PIC + hardware IRQ handling
│   ├── timer.c/.h          # PIT timer (IRQ0)
│   ├── keyboard.c/.h       # Keyboard driver (IRQ1)
│   ├── memory.c/.h         # Simple heap allocator
│   └── io.h                # Low-level port I/O helpers
│
├── iso/                    # Auto-generated GRUB ISO
├── linker.ld               # Linker script (kernel layout)
└── Makefile                # Build system
```

---

# 🧰 Build Requirements

### Install on Ubuntu / Debian / WSL:

```bash
sudo apt update
sudo apt install build-essential nasm qemu-system-x86 xorriso grub-pc-bin
```

---

# 🛠️ Building & Running

### Build everything:

```bash
make
```

### Run in QEMU:

```bash
make run
```

### Clean build artifacts:

```bash
make clean
```

Output files:

```
kernel.bin   # The finished kernel
myos.iso     # Bootable GRUB ISO
```

---

# 🖥️ What It Looks Like When Running

```
Welcome to MyOS!
Initializing GDT...
Initializing IDT...
Installing ISRs...
Installing IRQs...
Initializing heap...
Installing timer (100Hz)...
Installing keyboard...
Enabling interrupts...
System initialized. Type on your keyboard!
```

Keyboard input will appear directly in the terminal window of QEMU.

---

# 📚 Concepts You Will Learn

### 🔹 Low-Level Architecture

- CPU privilege levels
- Protected mode
- Hardware interrupts
- PIC remapping
- Instruction set fundamentals

### 🔹 Operating System Design

- Kernel initialization flow
- Memory management basics
- Hardware abstraction layers
- Scheduling foundations (timer interrupts)

### 🔹 Systems Programming

- Writing freestanding C code
- NASM assembly routines
- Linker scripts & memory layout
- Bare-metal debugging

---

# 🛤️ Roadmap / Planned Features

| Status | Feature                              |
| ------ | ------------------------------------ |
| 🔜     | Paging (virtual memory)              |
| 🔜     | Improved heap allocator (free lists) |
| 🔜     | Syscall interface                    |
| 🔜     | Simple shell with commands           |
| 🔜     | Basic VFS (Virtual File System)      |
| 🔜     | ATA/IDE disk driver                  |
| 🔜     | Graphics mode + framebuffer driver   |
| 🔜     | User-mode processes                  |

---

# 🤝 Contributing

Pull requests, issues, and suggestions are welcome — especially from people learning OS development.

---

# 📄 License

This project is licensed under the **MIT License** (or your chosen license).

---

# ⭐ If You Like MyOS

Give the repository a **star** — it helps people discover the project and encourages further development!

---
