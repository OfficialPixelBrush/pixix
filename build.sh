ALL_GNU_TOOLS="false"
TARGET_ARCH="i486"

# Create initramfs
echo "Making initramfs..."
rm -r initramfs
mkdir -p initramfs
mkdir -p initramfs/bin

# Build custom userland
echo "Building userland..."
cd user
gcc -m32 -no-pie -fno-pic -static -march=$TARGET_ARCH -mno-sse -mno-mmx -fno-stack-protector -fno-asynchronous-unwind-tables -fno-ident shell.c -o shell
gcc -m32 -no-pie -fno-pic -static -march=$TARGET_ARCH -mno-sse -mno-mmx -fno-stack-protector -fno-asynchronous-unwind-tables -fno-ident fetch.c -o fetch
gcc -m32 -no-pie -fno-pic -static -march=$TARGET_ARCH -mno-sse -mno-mmx -fno-stack-protector -fno-asynchronous-unwind-tables -fno-ident setup.c -o setup
cp shell ../initramfs/init
cp fetch ../initramfs/fetch
cp setup ../initramfs/setup
cd ..

echo "ALL_GNU_TOOLS is set to: '$ALL_GNU_TOOLS'"
if [ "$ALL_GNU_TOOLS" = "true" ]; then
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
else
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
make CFLAGS="-m32 -static" LDFLAGS="-m32 -static" src/ls src/mkdir
cp ./src/ls ../initramfs/bin/
cp ./src/mkdir ../initramfs/bin/
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
make ARCH=$TARGET_ARCH KCFLAGS="-march=$TARGET_ARCH" -j"$(nproc)"

# Prepare ISO image
cp ../isolinux.bin arch/x86/boot/
make isoimage ARCH=$TARGET_ARCH -j"$(nproc)" KCFLAGS="-march=$TARGET_ARCH" FDARGS="initrd=/init.cpio" FDINITRD="../init.cpio"

# Move ISO to project root
mv arch/x86/boot/image.iso ../pixix.iso
cd ..
