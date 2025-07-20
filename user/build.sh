as --32 -march=i486 sys.s -o sys.lib
as --32 -march=i486 crt.s -o crt.lib

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c shell.c
ld -m elf_i386 -static -o shell.i386 crt.lib sys.lib shell.o --entry=_start -z noexecstack
strip shell.i386

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c pitch.c
ld -m elf_i386 -static -o pitch.i386 crt.lib sys.lib pitch.o --entry=_start -z noexecstack
strip pitch.i386

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c prep.c
ld -m elf_i386 -static -o prep.i386 crt.lib sys.lib prep.o --entry=_start -z noexecstack
strip prep.i386

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c ls.c
ld -m elf_i386 -static -o ls.i386 crt.lib sys.lib ls.o --entry=_start -z noexecstack
strip ls.i386

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c test.c
ld -m elf_i386 -static -o test.i386 crt.lib sys.lib test.o --entry=_start -z noexecstack
strip test.i386

as --32 -march=i486 reboot.s -o reboot.i386
strip reboot.i386
as --32 -march=i486 shutdown.s -o shutdown.i386
strip shutdown.i386