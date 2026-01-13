CCOPT=-Os --target=sodium16 -mllvm -sodium-pair-spillrestore -fPIC
PREFIX=/home/hp/llvm-project/llvm/build/bin
CC=$(PREFIX)/clang
LD=$(PREFIX)/ld.lld

all : mkdir out

out : crt.o libc.o main.o shell_port.o shell.o shell_ext.o shell_cmd_list.o
	$(LD) -o build/out -T link.ld \
	build/crt.o build/vsnprintf.o build/string.o build/divsi.o build/divhi.o \
	build/main.o build/shell_port.o \
	build/shell.o build/shell_ext.o build/shell_cmd_list.o
	$(PREFIX)/llvm-objcopy build/out -O binary build/firmware.bin
	./coegen-x86_64 -b 16 -f xilinx build/firmware.bin > build/firmware.coe

crt.o : crt.S
	$(CC) $(CCOPT) -c crt.S -o build/crt.o

libc.o : vsnprintf.c string.c divsi.c divhi.c
	$(CC) $(CCOPT) -c vsnprintf.c -I ./ -o build/vsnprintf.o
	$(CC) $(CCOPT) -c string.c -I ./ -o build/string.o
	$(CC) $(CCOPT) -c divsi.c -I ./ -o build/divsi.o
	$(CC) $(CCOPT) -c divhi.c -I ./ -o build/divhi.o

main.o : main.c shell_port.h
	$(CC) $(CCOPT) -c main.c -I ./ -I ../../src -o build/main.o

shell_port.o : shell_port.c ../../src/shell.h
	$(CC) $(CCOPT) -c shell_port.c -I ./ -I ../../src -o build/shell_port.o

shell.o : ../../src/shell.c ../../src/shell.h shell_cfg.h
	$(CC) $(CCOPT) -c ../../src/shell.c -I ./ -I ../../src -o build/shell.o

shell_ext.o : ../../src/shell_ext.c ../../src/shell_ext.h ../../src/shell.h shell_cfg.h
	$(CC) $(CCOPT) -c ../../src/shell_ext.c -I ./ -I ../../src -o build/shell_ext.o

shell_cmd_list.o : ../../src/shell_cmd_list.c ../../src/shell.h shell_cfg.h
	$(CC) $(CCOPT) -c ../../src/shell_cmd_list.c -I ./ -I ../../src -o build/shell_cmd_list.o

.PHONY : all clean mkdir
clean :
	-rm -r build

mkdir :
	if [ ! -d "build" ]; then (mkdir build) fi
