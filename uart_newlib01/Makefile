ARMGNU ?= arm-none-eabi
ARMGNU ?= arm-linux-gnueabi

LIBC = $(shell dirname $(shell $(ARMGNU)-gcc -print-file-name=libc.a))
LIBGCC = $(shell dirname $(shell $(ARMGNU)-gcc -print-file-name=libgcc.a))

LIB = -L $(LIBC) -L $(LIBGCC)

AARCH = -march=armv5t
AOPS = --warn --fatal-warnings $(AARCH)
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding $(AARCH)

notmain.bin :  strap.o notmain.o memmap newlib.o
	$(ARMGNU)-ld strap.o notmain.o newlib.o -T memmap -o notmain.elf $(LIB) -lc -lgcc
	$(ARMGNU)-objdump -D notmain.elf > notmain.list
	$(ARMGNU)-objcopy notmain.elf -O binary notmain.bin

strap.o : strap.s
	$(ARMGNU)-as $(AOPS) strap.s -o strap.o

notmain.o : notmain.c
	$(ARMGNU)-gcc -c $(COPS) notmain.c -o notmain.o

newlib.o : newlib.c
	$(ARMGNU)-gcc $(COPS) -c $(COPS) newlib.c -o newlib.o

.PHONY : clean
clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.bin
	rm -f *.list

.PHONY : sim
sim : notmain.bin
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel notmain.bin

.PHONY : gdbserver
gdbserver : notmain.bin
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel notmain.bin -S -s

.PHONY : gdb
gdb : notmain.bin
	$(ARMGNU)-gdb -ex 'target remote :1234' -ex 'b notmain' notmain.elf

.PHONY : astyle
astyle :
	find . -name '*.c' | xargs astyle --style=kr --pad-oper --pad-comma --pad-header --unpad-paren
