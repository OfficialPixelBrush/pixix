# Create initramfs
echo "Making initramfs..."
rm -r initramfs
mkdir -p initramfs

# Build kernel
echo "Building kernel..."
cd linux
make -j"$(nproc)"
cd ..

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

# Build custom userland
echo "Building userland..."
cd user
rm shell
gcc -m32 -static shell.c -o shell
rm fetch
gcc -m32 -static fetch.c -o fetch
cp shell ../initramfs/init
cp fetch ../initramfs/fetch
cd ..

# Make into init.cpio
echo "Making init..."
cd initramfs
find . | cpio -H newc -o > ../init.cpio
cd ..

# Make ISO
echo "Making iso..."
cp isolinux.bin linux/arch/x86/boot/
cd linux
make -j"$(nproc)" isoimage ARCH=i386 FDARGS="initrd=/init.cpio" FDINITRD="../init.cpio"
cd ..
mv linux/arch/x86/boot/image.iso pixix.iso