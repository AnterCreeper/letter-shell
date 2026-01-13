CCOPT=-Os --target=sodium16 -mllvm -sodium-pair-spillrestore -fPIC
PREFIX=/home/hp/llvm-project/llvm/build/bin
CC=$(PREFIX)/clang
LD=$(PREFIX)/ld.lld

all : mkdir out

out : libc.o shell.o shell_ext.o shell_cmd_list.o main.o shell_port.o
	$(LD) -o build/out -T link.ld \
	build/crt.o build/vsnprintf.o build/string.o build/divsi.o build/divhi.o build/ashlsi3.o \
	build/shell.o build/shell_ext.o build/shell_cmd_list.o \
	build/main.o build/shell_port.o
	$(PREFIX)/llvm-objcopy build/out -O binary build/firmware.bin
	./coegen-x86_64 -b 16 -f xilinx build/firmware.bin > build/firmware.coe

libc.o : ./libc/crt.S ./libc/vsnprintf.c ./libc/string.c ./libc/divsi.c ./libc/divhi.c ./libc/ashlsi3.c
	$(CC) $(CCOPT) -c ./libc/crt.S -o build/crt.o
	$(CC) $(CCOPT) -c ./libc/vsnprintf.c -I ./ -I ./libc -o build/vsnprintf.o
	$(CC) $(CCOPT) -c ./libc/string.c -I ./ -I ./libc -o build/string.o
	$(CC) $(CCOPT) -c ./libc/divsi.c -I ./ -I ./libc -o build/divsi.o
	$(CC) $(CCOPT) -c ./libc/divhi.c -I ./ -I ./libc -o build/divhi.o
	$(CC) $(CCOPT) -c ./libc/ashlsi3.c -I ./ -I ./libc -o build/ashlsi3.o

shell.o : ../../src/shell.c ../../src/shell.h shell_cfg.h
	$(CC) $(CCOPT) -c ../../src/shell.c -I ./ -I ./libc -I ../../src -o build/shell.o

shell_ext.o : ../../src/shell_ext.c ../../src/shell_ext.h ../../src/shell.h shell_cfg.h
	$(CC) $(CCOPT) -c ../../src/shell_ext.c -I ./ -I ./libc -I ../../src -o build/shell_ext.o

shell_cmd_list.o : ../../src/shell_cmd_list.c ../../src/shell.h shell_cfg.h
	$(CC) $(CCOPT) -c ../../src/shell_cmd_list.c -I ./ -I ./libc -I ../../src -o build/shell_cmd_list.o

main.o : main.c shell_port.h
	$(CC) $(CCOPT) -c main.c -I ./ -I ./libc -I ../../src -o build/main.o

shell_port.o : shell_port.c ../../src/shell.h
	$(CC) $(CCOPT) -c shell_port.c -I ./ -I ./libc -I ../../src -o build/shell_port.o

.PHONY : all clean mkdir
clean :
	-rm -r build

mkdir :
	if [ ! -d "build" ]; then (mkdir build) fi
