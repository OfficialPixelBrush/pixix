ARGS_ASM="--32 -march=i486"
ARGS_GCC="-m32 -march=i486 -nostartfiles -ffreestanding -fno-asynchronous-unwind-tables -fomit-frame-pointer -fno-pic -fno-stack-protector -c"
ARGS_LD="-m elf_i386 -nostdlib --gc-sections -z noexecstack -T script.ld -e _start"
ARGS_OBJCOPY="--strip-all --remove-section=.comment --remove-section=.note.gnu.property --remove-section=.note.gnu.build-id"

# Build Libaries
as $ARGS_ASM asm/crt.s -o asm/crt.lib
as $ARGS_ASM asm/sys.s -o asm/sys.lib
as $ARGS_ASM asm/net.s -o asm/net.lib

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

# Build Assembly Programs
as $ARGS_ASM chroot.s -o chroot.o
ld $ARGS_LD -o chroot.i386 chroot.o
objcopy $ARGS_OBJCOPY chroot.i386
