GET_GNU_TOOLS=false
GET_NANO=false
GET_BUSYBOX=true

ARCHIVE_BASH=bash-5.3.tar.gz
ARCHIVE_COREUTILS=coreutils-9.7.tar.gz
ARCHIVE_BUSYBOX=busybox-1.36.1.tar.bz2

# Install Dependencies
echo "Installing Dependencies..."
apt install isolinux flex bison bc genisoimage libc6-dev-i386

# Download necessary code
echo "Cloning latest kernel..."
git clone --depth=1 https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git

# Copy config to kernel
echo "Copying kernel config..."
cp kernelconfig linux/.config

if [ "$GET_NANO" = true ]; then
    echo "Cloning nano..."
    git clone --depth=1 https://git.savannah.gnu.org/git/nano.git
fi

if [ "$GET_GNU_TOOLS" = true ]; then
    if [ ! -e "$ARCHIVE_BASH"] ; then
        echo "Cloning bash..."
        wget https://ftp.gnu.org/gnu/bash/$ARCHIVE_BASH
        tar -xf $ARCHIVE_BASH
    fi
    if [ ! -e "$ARCHIVE_COREUTILS" ]; then
        echo "Cloning coreutils..."
        wget https://ftp.gnu.org/gnu/coreutils/$ARCHIVE_COREUTILS
        tar -xf $ARCHIVE_COREUTILS
    fi
fi

if [ "$GET_BUSYBOX" = true ]; then
    echo "Cloning Busybox..."
    git clone --depth=1 https://github.com/mirror/busybox
    #if [ ! -e "$ARCHIVE_BUSYBOX" ]; then
    #    echo "Cloning Busybox..."
    #    wget https://busybox.net/downloads/$ARCHIVE_BUSYBOX
    #    tar -xf $ARCHIVE_BUSYBOX
    #fi
    echo "Copying busybox config..."
    cp busyboxconfig busybox/.config
fi
