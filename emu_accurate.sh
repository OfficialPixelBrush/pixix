qemu-system-i386 -m 64M -cpu pentium2 \
    -netdev user,id=n1 -device e1000,netdev=n1 \
    -cdrom pixix.iso \
    -device ide-cd,bus=ide.1 \
    -boot d