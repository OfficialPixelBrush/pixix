qemu-system-i386 -cdrom pixix.iso -m 32M -cpu 486 \
    -netdev user,id=n1 -device e1000,netdev=n1