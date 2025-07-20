# Install Dependencies
echo "Installing Dependencies..."
apt install isolinux

# Download necessary code
echo "Cloning latest kernel..."
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
echo "Cloning bash..."
wget https://ftp.gnu.org/gnu/bash/bash-5.3.tar.gz
tar -xf bash-5.3.tar.gz
echo "Cloning coreutils..."
wget https://ftp.gnu.org/gnu/coreutils/coreutils-9.7.tar.gz
tar -xf coreutils-9.7.tar.gz

# Copy config to kernel
echo "Copying kernel config..."
cp kernelconfig linux/.config
