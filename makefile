# Automatically generate lists of sources using wildcards .
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

CC = ${HOME}/opt/cross-i686/bin/i686-elf-gcc
AS = nasm
LD = ${HOME}/opt/cross-i686/bin/i686-elf-ld

# Convert the *. c filenames to *. o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Default build target
all: disk.img

run: all
	qemu-system-i386 -m 512 -drive file=disk.img,format=raw -no-reboot

debug: all
	qemu-system-i386 -m 512 -drive file=disk.img,format=raw -s -S -no-reboot -d int,pcall,cpu_reset

# This is the actual disk image that the computer loads
# which is the combination of our compiled bootsector and kernel
disk.img: boot/boot.bin kernel.bin
	dd if=/dev/zero of=$@ bs=1024 count=1440 && \
	dd if=$< of=$@ conv=notrunc && \
	dd if=$(word 2,$^) of=$@ bs=512 seek=1 conv=notrunc
# cat $^ > os-image && truncate -s 10KB os-image

# This builds the binary of our kernel from two object files :
# - the kernel_entry , which jumps to main () in our kernel
# - the compiled C kernel
kernel.bin: kernel/kernel_entry.o kernel/isr.o kernel/pic.o kernel/memory.o ${OBJ}
	${LD} -o $@ -Ttext 0x500 $^ --oformat binary

# Generic rule for compiling C code to an object file
# For simplicity , we C files depend on all header files .
%.o: %.c ${HEADERS}
	${CC} -ffreestanding -ggdb -O0 -mgeneral-regs-only -c $< -o $@

# Assemble the kernel_entry .
%.o: %.asm
	${AS} $< -f elf -o $@

%.bin: %.asm
	${AS} $< -f bin -I './boot/' -o $@

clean:
	rm -fr *.bin *.dis *.o disk.img
	rm -fr kernel/*.o boot/*.bin drivers/*.o