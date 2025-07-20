as --32 -march=i486 sys.s -o sys
as --32 -march=i486 crt.s -o crt

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c shell.c
ld -m elf_i386 -static -o shell crt sys shell.o --entry=_start -z noexecstack
strip shell

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c pitch.c
ld -m elf_i386 -static -o pitch crt sys pitch.o --entry=_start -z noexecstack
strip pitch

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c prep.c
ld -m elf_i386 -static -o prep crt sys prep.o --entry=_start -z noexecstack
strip prep

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c ls.c
ld -m elf_i386 -static -o ls crt sys ls.o --entry=_start -z noexecstack
strip ls

gcc -m32 -static -march=i486 --data-sections -fomit-frame-pointer -fno-pic -fno-stack-protector -nostdlib -c test.c
ld -m elf_i386 -static -o test crt sys test.o --entry=_start -z noexecstack
strip test

as --32 -march=i486 reboot.s -o reboot
strip reboot
as --32 -march=i486 shutdown.s -o shutdown
strip shutdown