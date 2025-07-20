TARGET_ARCH="i386"

mkdir initramfs

# Build custom userland
echo "Building userland..."
cd user
./build.sh
cp ./shell.i386 ../initramfs/init
cp ./pitch.i386 ../initramfs/pitch
cp ./prep.i386 ../initramfs/prep
#cp ./reboot.i386 ../initramfs/reboot
#cp ./shutdown.i386 ../initramfs/shutdown
#cp ./ls.i386 ../initramfs/ls
cd ..

# Make into init.cpio
echo "Making init..."
cd initramfs
find . | cpio -H newc -o > ../init.cpio
cd ..

# Build kernel and create ISO
echo "Building kernel and ISO..."
cd linux

# Configure and build the kernel
cp ../kernelconfig .config
make ARCH=i386 KCFLAGS="-march=$TARGET_ARCH" -j"$(nproc)"

# Prepare ISO image
cp ../isolinux.bin arch/x86/boot/
make isoimage ARCH=i386 -j"$(nproc)" KCFLAGS="-march=$TARGET_ARCH" FDARGS="initrd=/init.cpio" FDINITRD="../init.cpio"

# Move ISO to project root
mv arch/x86/boot/image.iso ../pixix.iso
cd ..

