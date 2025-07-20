TARGET_ARCH="i486"

mkdir initramfs

# Build custom userland
echo "Building userland..."
cd user
./build.sh
cp ./shell ../initramfs/init
cp ./pitch ../initramfs/pitch
#cp ./prep ../initramfs/prep
#cp ./reboot ../initramfs/reboot
#cp ./shutdown ../initramfs/shutdown
cp ./ls ../initramfs/ls
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

