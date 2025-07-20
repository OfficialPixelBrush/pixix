GNU_TOOLS="true"
TARGET_ARCH="i386"

# Create initramfs
echo "Making initramfs..."
rm -r initramfs
mkdir -p initramfs
mkdir -p initramfs/bin

# Build custom userland
echo "Building userland..."
cd user
./build.sh
cp ./shell.i386 ../initramfs/init
cp ./pitch.i386 ../initramfs/pitch
cp ./prep.i386 ../initramfs/prep
cp ./reboot.i386 ../initramfs/reboot
cp ./shutdown.i386 ../initramfs/shutdown
#cp ./ls.i386 ../initramfs/ls
cd ..

echo "ALL_GNU_TOOLS is set to: '$ALL_GNU_TOOLS'"
if [ "$GNU_TOOLS" = "true" ]; then
# Build bash
#echo "Building bash..."
#cd bash-5.3
#CFLAGS="-m32 -static" \
#LDFLAGS="-m32 -static" \
#./configure --prefix=/usr/local/bash-i386-static \
#            --without-bash-malloc \
#            --disable-nls \
#            --enable-static-link
#make clean
#make CFLAGS="-m32 -static" LDFLAGS="-m32 -static"
#cp bash ../initramfs/bash
#cd ..
#

# Build coreutils
echo "Building coreutils..."
cd coreutils-9.7
CFLAGS="-m32 -static" \
LDFLAGS="-m32 -static" \
./configure --prefix=/usr/local/bash-i386-static \
            --without-bash-malloc \
            --disable-nls \
            --enable-static-link
make clean
make CFLAGS="-m32 -static" LDFLAGS="-m32 -static"
#find ./src -type f -executable -exec cp {} ../initramfs/bin/ \;
cp ./src/ls  ../initramfs/bin
cp ./src/cat ../initramfs/bin
cd ..
fi

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
