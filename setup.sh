GET_NANO=false
GET_BUSYBOX=true
GET_GRUB=true

# Install Dependencies
echo "Installing Dependencies..."
if command -v apt >/dev/null 2>&1; then
    apt update
    apt install -y \
        isolinux \
        flex \
        bison \
        bc \
        genisoimage \
        libc6-dev-i386
elif command -v dnf >/dev/null 2>&1; then
    dnf install -y \
        syslinux \
        flex \
        bison \
        bc \
        genisoimage \
        glibc-devel.i686
else
    echo "Unsupported distribution"
    exit 1
fi

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

if [ "$GET_GRUB" = true ]; then
    echo "Cloning Grub..."
    git clone --depth=1 https://git.savannah.gnu.org/git/grub.git
    cd grub
    git pull
    ./bootstrap
    cd ..
fi
