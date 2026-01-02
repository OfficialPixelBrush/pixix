cd ncurses-6.4
CC="i386-linux-musl-gcc" \
    CFLAGS="-m32 -static -O2" \
    LDFLAGS="-m32 -static" \
    ./configure \
        --prefix=$HOME/musl-i386-ncurses \
        --with-shared=no \
        --with-static=yes \
        --enable-widec \
        --without-debug \
        --without-ada

make -j$(nproc)
make install
cd ..