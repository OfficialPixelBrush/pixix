GET_NANO=false
GET_BUSYBOX=true
GET_PARTED=true
GET_GRUB=true

# Install Dependencies
echo "Installing Dependencies..."
apt install isolinux flex bison bc genisoimage libc6-dev-i386

# Download necessary code
echo "Cloning latest kernel..."
git clone --depth=1 https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
cd linux
git pull
cd ..

# Copy config to kernel
echo "Copying kernel config..."
cp kernelconfig linux/.config

if [ "$GET_NANO" = true ]; then
    echo "Cloning nano..."
    git clone --depth=1 https://git.savannah.gnu.org/git/nano.git
    cd nano
    git pull
    cd ..
fi

if [ "$GET_BUSYBOX" = true ]; then
    echo "Cloning Busybox..."
    git clone --depth=1 https://github.com/mirror/busybox
    cd busybox
    git pull
    cd ..
fi

if [ "$GET_GRUB" = true ]; then
    echo "Cloning Grub..."
    git clone --depth=1 git://git.savannah.gnu.org/grub.git
    cd grub
    rm -r buikd
    mkdir build
    git pull
    cd ..
fi
