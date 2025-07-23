if [ ! -f pixix_disk.qcow2 ]; then
    qemu-img create -f qcow2 pixix_disk.qcow2 20G
fi

qemu-system-i386 \
    -m 64M \
    -cpu pentium2 \
    -netdev user,id=n1 -device e1000,netdev=n1 \
    -cdrom pixix.iso \
    -drive file=pixix_disk.qcow2,format=qcow2,if=ide \
    -boot d