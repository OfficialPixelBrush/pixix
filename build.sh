TARGET_ARCH="i386"

rm -r initramfs
mkdir initramfs
mkdir initramfs/bin
mkdir initramfs/dev

rm -r diskfs
mkdir diskfs
mkdir diskfs/bin
echo "Welcome to the disk!" >> diskfs/text.txt

# Build custom userland
echo "Building userland..."
cd user
./build.sh
cp ./shell.i386 ../initramfs/init
cp ./pitch.i386 ../diskfs/pitch
cp ./ping.i386 ../diskfs/ping
cd ..

# Setting up busybox
echo "Building minimal busybox..."
cd busybox
cp ../minbusybox.config .config
make CFLAGS="-march=$TARGET_ARCH -m32 -static" LDFLAGS="-march=$TARGET_ARCH -m32 -static"
strip busybox
cp busybox ../initramfs/bin/minibb

echo "Building cd busybox..."
cp ../busybox.config .config
make CFLAGS="-march=$TARGET_ARCH -m32 -static" LDFLAGS="-march=$TARGET_ARCH -m32 -static"
strip busybox
cp busybox ../diskfs/bin/busybox
cd ..

# Grub setup
echo "Setting up grub..."
cd grub
cd build
../configure --target=i386 --prefix=/usr/local
make -j$(nproc)
cp grub-install ../../diskfs/
cp grub-mkconfig ../../diskfs/
cd ../..

# Symlinks to make using busybox easier
echo "Setting up symlinks..."
cd initramfs
ln -s ./bin/minibb ./ash
ln -s ./bin/minibb ./ls
ln -s ./bin/minibb ./cat
ln -s ./bin/minibb ./blkid
ln -s ./bin/minibb ./mount
ln -s ./bin/minibb ./umount
ln -s ./bin/minibb ./chroot
cd ../diskfs
ln -s ./bin/busybox ./ifconfig
ln -s ./bin/busybox ./udhcpc
ln -s ./bin/busybox ./route
ln -s ./bin/busybox ./find
ln -s ./bin/busybox ./cp
ln -s ./bin/busybox ./fdisk
ln -s ./bin/busybox ./chmod
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
cp ../isolinux.bin arch/x86/boot/
cp ../kernel.config .config
make ARCH=i386 KCFLAGS="-march=$TARGET_ARCH" -j"$(nproc)"

# Prepare ISO image
make isoimage ARCH=i386 -j"$(nproc)" KCFLAGS="-march=$TARGET_ARCH" FDARGS="initrd=/init.cpio" FDINITRD="../init.cpio"

mkdir iso_root
xorriso -osirrox on -indev arch/x86/boot/image.iso -extract / iso_root
cp -r ../diskfs/* iso_root/
xorriso -as mkisofs \
  -r -J -V "pixix" \
  -b isolinux.bin \
  -c boot.cat \
  -no-emul-boot -boot-load-size 4 -boot-info-table \
  -o ../pixix.iso \
  iso_root/
rm -rf iso_root
