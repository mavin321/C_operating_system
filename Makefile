# Makefile

ISO_DIR = iso
BOOT_DIR = $(ISO_DIR)/boot
GRUB_DIR = $(BOOT_DIR)/grub

CC = gcc
LD = ld
AS = nasm

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
LDFLAGS = -T linker.ld -m elf_i386
ASFLAGS = -f elf32

KERNEL_OBJS = \
    boot/boot.o \
    kernel/kernel.o \
    kernel/terminal.o

all: myos.iso

boot/boot.o: boot/boot.s
	$(AS) $(ASFLAGS) -o $@ $<

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

kernel.bin: $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(KERNEL_OBJS)

$(GRUB_DIR)/grub.cfg:
	mkdir -p $(GRUB_DIR)
	echo 'set default=0'                 >  $(GRUB_DIR)/grub.cfg
	echo 'set timeout=0'                >> $(GRUB_DIR)/grub.cfg
	echo 'menuentry "MyOS" {'           >> $(GRUB_DIR)/grub.cfg
	echo '  multiboot /boot/kernel.bin' >> $(GRUB_DIR)/grub.cfg
	echo '  boot'                       >> $(GRUB_DIR)/grub.cfg
	echo '}'                            >> $(GRUB_DIR)/grub.cfg

myos.iso: kernel.bin $(GRUB_DIR)/grub.cfg
	mkdir -p $(BOOT_DIR)
	cp kernel.bin $(BOOT_DIR)/kernel.bin
	grub-mkrescue -o myos.iso $(ISO_DIR)

run: myos.iso
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -f $(KERNEL_OBJS) kernel.bin myos.iso
	rm -rf $(ISO_DIR)

.PHONY: all clean run
