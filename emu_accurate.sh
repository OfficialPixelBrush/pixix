qemu-system-i386 \
    -m 64M \
    -cpu pentium2 \
    -netdev user,id=n1 -device e1000,netdev=n1 \
    -cdrom pixix.iso \
    -boot d
    #-drive file=pixix_disk.qcow2,format=qcow2,if=ide \