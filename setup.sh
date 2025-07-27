GET_NANO=false
GET_BUSYBOX=true
GET_LIMINE=true

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
cp kernel.config linux/.config

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

if [ "$GET_LIMINE" = true ]; then
    echo "Cloning Limine..."
    git clone --depth=1 https://github.com/limine-bootloader/limine.git
    cd limine
    git pull
    ./bootstrap
    cd ..
fi
