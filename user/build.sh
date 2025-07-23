rm -rf bin
mkdir -p bin
cd src
ARGS_ASM="--32 -march=i386"
ARGS_GCC="-m32 -march=i386 -Wl,--omit-header -nostartfiles -ffreestanding -fno-asynchronous-unwind-tables -fomit-frame-pointer -fno-pic -fno-stack-protector -c"
ARGS_LD="-m elf_i386 -z max-page-size=0x1000 -nostdlib --gc-sections -z noexecstack -T ../script.ld -e _start"
ARGS_OBJCOPY="--strip-all --remove-section=.comment --remove-section=.note.gnu.property --remove-section=.note.gnu.build-id"

# Build Libaries
as $ARGS_ASM asm/crt.s -o asm/crt.lib
as $ARGS_ASM asm/sys.s -o asm/sys.lib
as $ARGS_ASM asm/net.s -o asm/net.lib
as $ARGS_ASM asm/mem.s -o asm/mem.lib

# Build C Programs
# No CRT (no args)
gcc $ARGS_GCC init.c
ld $ARGS_LD -o init.i386 init.o asm/sys.lib
objcopy $ARGS_OBJCOPY init.i386

gcc $ARGS_GCC shell.c
ld $ARGS_LD -o shell.i386 shell.o asm/sys.lib
objcopy $ARGS_OBJCOPY shell.i386

gcc $ARGS_GCC pitch.c
ld $ARGS_LD -o pitch.i386 pitch.o asm/sys.lib
objcopy $ARGS_OBJCOPY pitch.i386

# With CRT (args)
gcc $ARGS_GCC ping.c
ld $ARGS_LD -o ping.i386 ping.o asm/crt.lib asm/sys.lib asm/net.lib
objcopy $ARGS_OBJCOPY ping.i386

gcc $ARGS_GCC cat.c
ld $ARGS_LD -o cat.i386 cat.o asm/crt.lib asm/sys.lib
objcopy $ARGS_OBJCOPY cat.i386

gcc $ARGS_GCC mount.c
ld $ARGS_LD -o mount.i386 mount.o asm/crt.lib asm/sys.lib
objcopy $ARGS_OBJCOPY mount.i386

gcc $ARGS_GCC umount.c
ld $ARGS_LD -o umount.i386 umount.o asm/crt.lib asm/sys.lib
objcopy $ARGS_OBJCOPY umount.i386

gcc $ARGS_GCC ls.c
ld $ARGS_LD -o ls.i386 ls.o asm/crt.lib asm/sys.lib
objcopy $ARGS_OBJCOPY ls.i386

gcc $ARGS_GCC mkdir.c
ld $ARGS_LD -o mkdir.i386 mkdir.o asm/crt.lib asm/sys.lib
objcopy $ARGS_OBJCOPY mkdir.i386

gcc $ARGS_GCC ln.c
ld $ARGS_LD -o ln.i386 ln.o asm/crt.lib asm/sys.lib
objcopy $ARGS_OBJCOPY ln.i386

gcc $ARGS_GCC cd.c
ld $ARGS_LD -o cd.i386 cd.o asm/crt.lib asm/sys.lib
objcopy $ARGS_OBJCOPY cd.i386

gcc $ARGS_GCC insmod.c
ld $ARGS_LD -o insmod.i386 insmod.o asm/crt.lib asm/sys.lib asm/mem.lib
objcopy $ARGS_OBJCOPY insmod.i386

gcc $ARGS_GCC install.c
ld $ARGS_LD -o install.i386 install.o asm/crt.lib asm/sys.lib
objcopy $ARGS_OBJCOPY install.i386

mv *.i386 ../bin
cd ..