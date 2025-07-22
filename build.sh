TARGET_ARCH="i386"

rm -rf initramfs
mkdir -p initramfs/bin

rm -rf diskfs
mkdir diskfs
mkdir diskfs/bin
echo "Welcome to the disk!" >> diskfs/text.txt

# Build custom userland
echo "Building userland..."
cd user
chmod +x build.sh
./build.sh
cp ./init.i386 ../initramfs/init
cp ./shell.i386 ../initramfs/bin/shell
cp ./cat.i386 ../initramfs/cat
cp ./mount.i386 ../initramfs/mount
cp ./ls.i386 ../initramfs/ls
cp ./umount.i386 ../initramfs/umount
cp ./pitch.i386 ../diskfs/pitch
cp ./ping.i386 ../diskfs/ping
cd ..

echo "Building busybox..."
cd busybox
cp -n ../busybox.config .config
make busybox \
  CFLAGS="-march=$TARGET_ARCH -m32 -static" \
  LDFLAGS="-march=$TARGET_ARCH -m32 -static"
strip busybox
cp busybox ../diskfs/bin/busybox
cd ..

# Grub setup
echo "Setting up grub..."
cd grub
cd build
make -s -j$(nproc)
cp grub-install ../../diskfs/
cp grub-mkconfig ../../diskfs/
cd ../..

# Symlinks to make using busybox easier
echo "Setting up symlinks..."
cd diskfs
ln -s ./bin/busybox ./ifconfig
ln -s ./bin/busybox ./udhcpc
ln -s ./bin/busybox ./route
ln -s ./bin/busybox ./cp
ln -s ./bin/busybox ./fdisk
ln -s ./bin/busybox ./mkfs.ext2
ln -s ./bin/busybox ./wget
cd bin
ln -s ./bin/busybox ./sh
cd ../..

# Make into init.cpio
echo "Making init..."
cd initramfs
find . | cpio -H newc -o > ../init.cpio
cd ..

# Build kernel and create ISO
echo "Building kernel and ISO..."
cd linux

# Configure and build the kernel
cp -u ../isolinux.bin arch/x86/boot/
cp -u ../kernel.config .config
make ARCH=i386 KCFLAGS="-march=$TARGET_ARCH" -j"$(nproc)"

# Prepare ISO image
make isoimage ARCH=i386 -j"$(nproc)" \
  KCFLAGS="-march=$TARGET_ARCH" \
  FDARGS="initrd=/init.cpio init=/init" \
  FDINITRD="../init.cpio"

mkdir iso_root
xorriso -osirrox on -indev arch/x86/boot/image.iso -extract / iso_root
cp -r ../diskfs/* iso_root/
xorriso -as mkisofs \
  -r -R -V "pixix" \
  -b isolinux.bin \
  -c boot.cat \
  -no-emul-boot -boot-load-size 4 -boot-info-table \
  -o ../pixix.iso \
  iso_root/
rm -rf iso_root
