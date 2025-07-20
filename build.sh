NO_GNU_TOOLS="true"
TARGET_ARCH="i486"

# Create initramfs
echo "Making initramfs..."
#rm -r initramfs
mkdir -p initramfs
mkdir -p initramfs/bin

# Build custom userland
echo "Building userland..."
cd user
./build.sh
cp ./shell ../initramfs/init
cp ./pitch ../initramfs/pitch
cp ./prep ../initramfs/prep
cp ./reboot ../initramfs/reboot
cp ./shutdown ../initramfs/shutdown
cp ./ls ../initramfs/ls
cd ..

echo "ALL_GNU_TOOLS is set to: '$ALL_GNU_TOOLS'"
if [ "$NO_GNU_TOOLS" = "false" ]; then
# Build bash
echo "Building bash..."
cd bash-5.3
CFLAGS="-m32 -static" \
LDFLAGS="-m32 -static" \
./configure --prefix=/usr/local/bash-i386-static \
            --without-bash-malloc \
            --disable-nls \
            --enable-static-link
make clean
make CFLAGS="-m32 -static" LDFLAGS="-m32 -static"
cp bash ../initramfs/bash
cd ..

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
find ./src -type f -executable -exec cp {} ../initramfs/bin/ \;
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
