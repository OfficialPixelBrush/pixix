TARGET_ARCH="i386"
DATE=$(date +%d-%b-%Y)

rm -rf initramfs diskfs

sleep 1

mkdir initramfs
mkdir initramfs/bin

mkdir diskfs
mkdir diskfs/bin
mkdir diskfs/mod
mkdir diskfs/grubmod
echo "Welcome to the disk!" >> diskfs/text.txt

# Build custom userland
echo "Building userland..."
cd user
chmod +x build.sh
./build.sh
# Copying
cp bin/init.i386    ../initramfs/bin/init
cp bin/shell.i386   ../initramfs/bin/shell
cp bin/cat.i386     ../initramfs/bin/cat
cp bin/mount.i386   ../initramfs/bin/mount
cp bin/ls.i386      ../initramfs/bin/ls

cp bin/umount.i386  ../diskfs/bin/umount
cp bin/cd.i386      ../diskfs/bin/cd
cp bin/pitch.i386   ../diskfs/bin/pitch
cp bin/ping.i386    ../diskfs/bin/ping
cp bin/insmod.i386  ../diskfs/bin/insmod
cp bin/mkdir.i386   ../diskfs/bin/mkdir
cp bin/ln.i386      ../diskfs/bin/ln
cp bin/cp.i386      ../diskfs/bin/cp
cp bin/irc.i386      ../diskfs/bin/irc
cp bin/install.i386 ../diskfs/install

# Symlinking
cd ../initramfs/
ln -s bin/init init
ln -s bin/cat cat
ln -s bin/mount mount
ln -s bin/ls ls
cd ..

echo "Building busybox..."
cd busybox
cp --update=none ../busybox.config .config
make busybox \
  CFLAGS="-march=$TARGET_ARCH -m32 -static" \
  LDFLAGS="-march=$TARGET_ARCH -m32 -static"
strip busybox
cp busybox ../diskfs/bin/busybox
cd ..

# Grub setup
echo "Setting up grub..."
cd grub
mkdir build
cd build
CFLAGS="-m32 -static" CXXFLAGS="-m32 -static" ../configure \
  --target=i386 \
  --with-platform=pc \
  --disable-werror \
  --disable-efiemu \
  --disable-nls \
  --disable-grub-mkfont \
  --disable-device-mapper \
  --disable-gtk \
  --disable-uboot \
  --disable-libzfs \
  --enable-grub-mkrescue=no
make -s -j$(nproc)
#./grub-mkimage -O i386-pc -o core.img -p /boot/grub -d ./grub-core/ part_msdos ext2 normal multiboot linux 
cp grub-install ../../diskfs
cp grub-mkconfig ../../diskfs
grub-mkimage -O i386-pc -o core.img -p /boot/grub/i386-pc part_msdos ext2 normal multiboot linux configfile
cp core.img ../../diskfs
find grub-core/ -maxdepth 1 -type f -exec cp {} ../../diskfs/grubmod/ \;
#cp grub-core/modinfo.sh ../../diskfs/grubmod/
#cp grub-core/moddep.lst ../../diskfs/grubmod/
#find . -name "*.mod" -exec cp {} ../../diskfs/grubmod/ \;
cd ../..

# Symlinks to make using busybox easier
echo "Setting up symlinks..."
cd diskfs
ln -s bin/busybox ./ifconfig
ln -s bin/busybox ./udhcpc
ln -s bin/busybox ./route
ln -s bin/busybox ./fdisk
ln -s bin/busybox ./mkfs.ext2
ln -s bin/busybox ./mkdosfs
ln -s bin/busybox ./mkswap
ln -s bin/busybox ./wget
#ln -s bin/busybox ./cp
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
cp -u ../isolinux.bin arch/x86/boot/
cp -u ../kernel.config .config
# Dunno why this doesn't work :p
export LOCALVERSION="-pixix_$DATE"
make ARCH=i386 KCFLAGS="-march=$TARGET_ARCH" -j"$(nproc)"

find . -name "*.ko" -exec cp --parents {} ../diskfs/mod/ \;

# Prepare ISO image
make isoimage ARCH=i386 -j"$(nproc)" \
  KCFLAGS="-march=$TARGET_ARCH" \
  FDARGS="initrd=/init.cpio init=/init" \
  FDINITRD="../init.cpio"

mkdir iso_root
xorriso -osirrox on -indev arch/x86/boot/image.iso -extract / iso_root
cp -r ../diskfs/* iso_root/
xorriso -as mkisofs \
  -r -R -V "pixix_$DATE" \
  -b isolinux.bin \
  -c boot.cat \
  -no-emul-boot -boot-load-size 4 -boot-info-table \
  -o ../pixix.iso \
  iso_root/
rm -rf iso_root
