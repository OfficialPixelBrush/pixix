TARGET_ARCH="i386"

rm -r initramfs
mkdir initramfs
mkdir initramfs/dev
mkdir initramfs/bin

# Build custom userland
echo "Building userland..."
cd user
./build.sh
cp ./shell.i386 ../initramfs/init
cp ./pitch.i386 ../initramfs/pitch
cp ./prep.i386 ../initramfs/prep
cp ./ping.i386 ../initramfs/ping
#cp ./dhcp.i386 ../initramfs/dhcp
#cp ./reboot.i386 ../initramfs/reboot
#cp ./shutdown.i386 ../initramfs/shutdown
#cp ./ls.i386 ../initramfs/ls
cd ..

echo "Building busybox..."
cd busybox
make CFLAGS="-march=$TARGET_ARCH -m32 -static" LDFLAGS="-march=$TARGET_ARCH -m32 -static"
strip busybox
cp busybox ../initramfs/bin/busybox
cd ..

echo "Setting up symlinks..."
cd initramfs
ln -s ./bin/busybox ./ifconfig
ln -s ./bin/busybox ./udhcpc
ln -s ./bin/busybox ./route
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
make isoimage ARCH=i386 -j"$(nproc)" KCFLAGS="-march=$TARGET_ARCH" FDARGS="initrd=/init.cpio root=/" FDINITRD="../init.cpio"

# Move ISO to project root
mv arch/x86/boot/image.iso ../pixix.iso
cd ..
