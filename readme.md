# 🚀 MyOS — A 32-bit Operating System Written in C

MyOS is a hobby operating system written from scratch using **C** and **NASM assembly**, built to teach low-level programming, operating-system architecture, memory management, hardware interaction, and bootloading concepts.

This project is designed to be clean, educational, and fully modular — ideal for learning OS development and showcasing on GitHub.

---

## ✨ Features (Current)

✔ **Multiboot-compliant kernel**
✔ **Boots via GRUB**
✔ **32-bit protected mode**
✔ **VGA text-mode terminal**
✔ **Custom screen output system**
✔ **Simple scrolling terminal**
✔ **Fully freestanding C code (no libc)**
✔ **Builds into a bootable ISO**
✔ **Runs on QEMU/VirtualBox/Bochs**

---

## 🏗️ Project Structure

```
myos/
├── Makefile          # Build system
├── linker.ld         # Kernel linker script
├── boot/
│   └── boot.s        # Multiboot header + entry assembly
└── kernel/
    ├── kernel.c      # Kernel entry point
    ├── terminal.c    # VGA text-mode terminal driver
    └── terminal.h
```

---

## 🔧 Build Requirements

Install the required tools:

### On Ubuntu / Debian / WSL:

```bash
sudo apt update
sudo apt install build-essential nasm qemu-system-x86 xorriso grub-pc-bin
```

---

## 🛠️ Build Instructions

Compile everything:

```bash
make
```

Run the OS in QEMU:

```bash
make run
```

Clean the build:

```bash
make clean
```

After building, you will get:

```
myos.iso   # Bootable OS image
kernel.bin
```

---

## 🖥️ What MyOS Does Right Now

When booted, MyOS:

- switches into 32-bit protected mode (via GRUB)
- clears the screen
- prints custom kernel messages
- uses a custom VGA driver for text output
- supports newline + scroll

Typical screen output:

```
Welcome to MyOS!
You just booted your own operating system written in C.

Next steps:
 - Implement GDT and IDT
 - Handle hardware interrupts (timer, keyboard)
 - Add a simple shell
```

---

## 📚 Learning Goals

This project teaches:

### 🔹 Low-Level Software Engineering

- Memory layout
- Linker scripts
- Bootloaders & multiboot
- Writing freestanding C code

### 🔹 Hardware Concepts

- VGA text mode buffer at 0xB8000
- CPU privilege modes
- Protected mode initialization

### 🔹 OS Fundamentals

- Kernel startup flow
- Terminal drivers
- Bare-metal programming
- Hand-crafted build system

---

## 🛤️ Roadmap / Planned Features

| Status | Feature                              |
| ------ | ------------------------------------ |
| 🔜     | Global Descriptor Table (GDT)        |
| 🔜     | Interrupt Descriptor Table (IDT)     |
| 🔜     | CPU exception handlers               |
| 🔜     | PIC remapping                        |
| 🔜     | Timer (PIT) driver                   |
| 🔜     | Keyboard driver                      |
| 🔜     | Simple interactive shell             |
| 🔜     | Paging + virtual memory              |
| 🔜     | Basic memory allocator (malloc/free) |

---

## 🤝 Contributing

Contributions, pull requests, and feature suggestions are always welcome — especially if you're also learning OSDev.

---

## 📄 License

This project is open-source under the **MIT License** (or specify your own).

---

## ⭐ If You Like This Project

Give the repository a **star** on GitHub — it helps others discover it and motivates more development!

---.
