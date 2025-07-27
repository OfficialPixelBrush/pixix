if [ ! -f pixix_disk.qcow2 ]; then
    qemu-img create -f qcow2 pixix_disk.qcow2 20G
fi
    #-cdrom pixix.iso \

qemu-system-i386 \
    -m 22M \
    -cpu 486 \
    -netdev user,id=n1 -device e1000,netdev=n1 \
    -drive file=pixix_disk.qcow2,format=qcow2,if=ide \
    -boot d