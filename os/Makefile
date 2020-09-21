C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libs/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libs/*.h)
# Syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o} 

# Change this if your cross-compiler is somewhere else
CC = gcc
GDB = gdb
# -g: Use debugging symbols in gcc
CFLAGS = -fno-pie -g -ffreestanding -Wall -Wextra -fno-exceptions -m32

all: os-image.bin

# First rule is run by default
os-image.bin: bootloader/bootloader.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: bootloader/kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ --oformat binary -m elf_i386 -s

# Used for debugging purposes
kernel.elf: bootloader/kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ 

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf32 -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o bootloader/*.bin drivers/*.o bootloader/*.o cpu/*.o libs/*.o
