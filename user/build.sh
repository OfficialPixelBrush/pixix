as --32 -march=i486 asm/crt.s -o asm/crt.lib
as --32 -march=i486 asm/sys.s -o asm/sys.lib
as --32 -march=i486 asm/net.s -o asm/net.lib

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c shell.c
ld -m elf_i386 -static -o shell.i386 asm/crt.lib asm/sys.lib shell.o --entry=_start -z noexecstack
strip shell.i386

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c pitch.c
ld -m elf_i386 -static -o pitch.i386 asm/crt.lib asm/sys.lib pitch.o --entry=_start -z noexecstack
strip pitch.i386

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c ping.c
ld -m elf_i386 -static -o ping.i386 asm/crt.lib asm/sys.lib asm/net.lib ping.o --entry=_start -z noexecstack
strip ping.i386