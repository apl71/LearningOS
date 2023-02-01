# Automatically generate lists of sources using wildcards .
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

CC = ${HOME}/opt/cross/bin/i686-elf-gcc
AS = nasm
LD = ${HOME}/opt/cross/bin/i686-elf-ld

# Convert the *. c filenames to *. o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Default build target
all: os-image

run: all
	qemu-system-i386 -drive file=os-image,format=raw -no-reboot

debug: all
	qemu-system-i386 -drive file=os-image,format=raw -s -S -no-reboot -d int,pcall,cpu_reset

# This is the actual disk image that the computer loads
# which is the combination of our compiled bootsector and kernel
# Padding to 10KB to prevent disk read error on qemu
os-image: boot/boot.bin kernel.bin
	cat $^ > os-image && truncate -s 10KB os-image

# This builds the binary of our kernel from two object files :
# - the kernel_entry , which jumps to main () in our kernel
# - the compiled C kernel
kernel.bin: kernel/kernel_entry.o kernel/isr.o kernel/pic.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

# Generic rule for compiling C code to an object file
# For simplicity , we C files depend on all header files .
%.o: %.c ${HEADERS}
	${CC} -ffreestanding -ggdb -O0 -c $< -o $@

# Assemble the kernel_entry .
%.o: %.asm
	${AS} $< -f elf -o $@

%.bin: %.asm
	${AS} $< -f bin -I './boot/' -o $@

clean:
	rm -fr *.bin *.dis *.o os-image
	rm -fr kernel/*.o boot/*.bin drivers/*.o