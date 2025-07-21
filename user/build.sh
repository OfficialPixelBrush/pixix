as --32 -march=i486 lib/crt.s -o lib/crt.lib
as --32 -march=i486 lib/sys.s -o lib/sys.lib
as --32 -march=i486 lib/net.s -o lib/net.lib

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c shell.c
ld -m elf_i386 -static -o shell.i386 lib/crt.lib lib/sys.lib shell.o --entry=_start -z noexecstack
strip shell.i386

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c pitch.c
ld -m elf_i386 -static -o pitch.i386 lib/crt.lib lib/sys.lib pitch.o --entry=_start -z noexecstack
strip pitch.i386

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c prep.c
ld -m elf_i386 -static -o prep.i386 lib/crt.lib lib/sys.lib prep.o --entry=_start -z noexecstack
strip prep.i386

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c ping.c
ld -m elf_i386 -static -o ping.i386 lib/crt.lib lib/sys.lib lib/net.lib ping.o --entry=_start -z noexecstack
strip ping.i386

#gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c ping.c
#ld -m elf_i386 -static -o ping.i386 lib/crt.lib lib/sys.lib lib/net.lib ping.o --entry=_start -z noexecstack
#strip ping.i386

#gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c ls.c
#ld -m elf_i386 -static -o ls.i386 lib/crt.lib lib/sys.lib ls.o --entry=_start -z noexecstack
#strip ls.i386

#gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c test.c
#ld -m elf_i386 -static -o test.i386 lib/crt.lib lib/sys.lib test.o --entry=_start -z noexecstack
#strip test.i386

as --32 -march=i486 reboot.s -o reboot.i386
strip reboot.i386
as --32 -march=i486 shutdown.s -o shutdown.i386
strip shutdown.i386