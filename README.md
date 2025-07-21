# Pixix
A hyper-minimal Linux Distro 

A good chunk of this was copied/inspired by [Making Smallest Possible Linux Distro (x64) by Nir Lichtman](https://www.youtube.com/watch?v=u2Juz5sQyYQ),
except that my target was an i386 system with 32MB of RAM.

### How to run
Just execute all.sh. This'll clone the necessary files into the repo.
Then it'll automatically build the final ISO for you.
```bash
chmod +x all.sh
./all.sh
```

If you'd like to run the commands separately, just execute the following in whatever order you need.

- `./setup.sh` is responsible for downloading all the necessary things (kernel + bash)

- `./build.sh` is for compiling everything into a usable .iso file

All of this was tested on Linux Mint 22.1, so modify `setup.sh` for whatever distro you may be running.

### Getting online
```bash
ifconfig eth0 up
udhcpc -i eth0
ifconfig eth0 10.0.2.15 netmask 255.255.255.0 up
prep
route add default gw 10.0.2.2
```