qemu-system-i386 -cdrom pixix.iso -m 64M -cpu pentium2 \
    -netdev user,id=n1 -device e1000,netdev=n1