BOOT_DIR := ./src/bootloader
BOOT_SRCFILE := $(BOOT_DIR)/boot.s
BUILD_DIR := ./build
BOOT_OBJFILE := $(BUILD_DIR)/boot.o

KERNEL_OBJFILE := $(BUILD_DIR)/kernel_asm.o
KERNEL_SRCFILE := ./src/kernel.s
KERNEL_BINFILE := ./bin/kernel.bin

OS_BINFILE = ./bin/os.bin

GENERATED_FILES := $(BOOT_OBJFILE) $(KERNEL_OBJFILE) $(KERNEL_BINFILE) $(OS_BINFILE)
INTERMEDIAT_FILES := ./build/kernelfull.o

INCLUDES = -I./src
KERNEL_CFILES_OBJS = ./build/kernel.o
KERNEL_CFILES = ./src/kernel.c
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce \
		-fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label \
		-Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

DISPLAY_CHAR_PRINT_SRC = ./src/display/char_print.c
DISPLAY_CHAR_PRINT_OBJ = ./build/display/char_print.o
DISPLAY_OBJ_FILES =  $(DISPLAY_CHAR_PRINT_OBJ)

MEMORY_SRC = ./src/memory/memory.c
MEMORY_OBJ = ./build/memory/memory.o
MEMORY_OBJ_FILES =  $(MEMORY_OBJ)

IDT_C_SRC = ./src/idt/idt.c
IDT_C_OBJ = ./build/idt/idt.o
IDT_ASM_SRC = ./src/idt/idt.s
IDT_ASM_OBJ = ./build/idt/idt_asm.o
IDT_OBJ_FILES =  $(IDT_C_OBJ) $(IDT_ASM_OBJ)


IO_ASM_SRC = ./src/io/io.s
IO_ASM_OBJ = ./build/io/io.o
IO_OBJ_FILES = $(IO_ASM_OBJ)

PIC_SRC = ./src/8259_PIC/pic.c
PIC_OBJ = ./build/8259_PIC/pic.o
PIC_OBJ_FILES = $(PIC_OBJ)


GENERATED_FILES += $(KERNEL_CFILES_OBJS) $(DISPLAY_OBJ_FILES) $(MEMORY_OBJ_FILES) $(IDT_OBJ_FILES) $(IO_OBJ_FILES) $(PIC_OBJ_FILES)

KERNEL_OBJECT_FILES_TO_GET_BIN := $(KERNEL_OBJFILE) $(KERNEL_CFILES_OBJS) \
	$(DISPLAY_OBJ_FILES) $(MEMORY_OBJ_FILES) $(IDT_OBJ_FILES) \
	$(IO_OBJ_FILES) $(PIC_OBJ_FILES)# for now

all: build_folder_setup $(BOOT_OBJFILE) $(KERNEL_BINFILE)
	rm -f $(OS_BINFILE)
	dd if=$(BOOT_OBJFILE) of=$(OS_BINFILE)
	dd seek=1 conv=sync if=$(KERNEL_BINFILE) of=$(OS_BINFILE) bs=512
	# dd if=$(KERNEL_BINFILE) bs=512 >> $(OS_BINFILE)

	dd if=/dev/zero bs=512 count=100 >> $(OS_BINFILE)

$(KERNEL_BINFILE): $(KERNEL_OBJECT_FILES_TO_GET_BIN)
	i686-elf-ld -g -relocatable $(KERNEL_OBJECT_FILES_TO_GET_BIN) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T./src/linker.ld  -o $@ -ffreestanding -O0 -nostdlib ./build/kernelfull.o

$(BOOT_OBJFILE): $(BOOT_SRCFILE)
	nasm -f bin $< -o $@

$(KERNEL_OBJFILE): $(KERNEL_SRCFILE)
	nasm -f elf $< -o $@

$(KERNEL_CFILES_OBJS): $(KERNEL_CFILES)
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99   -c $< -o $@

$(DISPLAY_CHAR_PRINT_OBJ): $(DISPLAY_CHAR_PRINT_SRC)
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99   -c $< -o $@

$(MEMORY_OBJ): $(MEMORY_SRC)
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99   -c $< -o $@

$(IDT_C_OBJ): $(IDT_C_SRC)
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99   -c $< -o $@

$(IDT_ASM_OBJ): $(IDT_ASM_SRC)
	nasm -f elf $< -o $@

$(IO_ASM_OBJ): $(IO_ASM_SRC)
	nasm -f elf $< -o $@

$(PIC_OBJ): $(PIC_SRC)
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99   -c $< -o $@

run: $(BOOT_OBJFILE)
	qemu-system-x86_64 -hda $<

debug: $(BOOT_OBJFILE)
	qemu-system-x86_64 -S -s -hda $(BOOT_OBJFILE)

build_folder_setup:
	mkdir -p build
	mkdir -p bin
	mkdir -p build/io
	mkdir -p build/display
	mkdir -p build/idt
	mkdir -p build/memory
	mkdir -p build/8259_PIC

re: clean all

clean:
	rm -f $(GENERATED_FILES) $(INTERMEDIAT_FILES)
