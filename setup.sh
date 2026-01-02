GET_NANO=false
GET_VIM=true
GET_NCURSES=true
GET_BUSYBOX=true
GET_GRUB=false
GET_TCC=true
GET_MUSL=true

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

if [ "$GET_NCURSES" = true ]; then
    echo "Cloning ncurses..."
    wget https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.4.tar.gz
    tar xvf ncurses-6.4.tar.gz
    cd ncurses-6.4
    cd ..
fi

if [ "$GET_NANO" = true ]; then
    echo "Cloning nano..."
    git clone --depth=1 https://git.savannah.gnu.org/git/nano.git
    cd nano
    ./autogen
    git pull
    cd ..
fi

if [ "$GET_VIM" = true ]; then
    echo "Cloning vim..."
    git clone --depth=1 https://github.com/vim/vim.git
    cd vim
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

if [ "$GET_TCC" = true ]; then
    echo "Cloning Tiny C Compiler..."
    git clone --depth=1 https://repo.or.cz/tinycc.git
    cd tinycc
    git pull
    cd ..
fi

if [ "$GET_MUSL" = true ]; then
    echo "Cloning musl..."
    git clone https://github.com/richfelker/musl-cross-make.git
    cd musl-cross-make
    git pull
    # TODO: Add musl script
    cd ..
fi

