<img style="min-width: 100px; image-rendering: pixelated" src="images/pixix.png">

# Pixix
A hyper-minimal Linux Distro for i386 and above.

<img style="min-width: 100px; image-rendering: pixelated" src="images/pixix.png">

A good chunk of this was copied/inspired by [Making Smallest Possible Linux Distro (x64) by Nir Lichtman](https://www.youtube.com/watch?v=u2Juz5sQyYQ),
except that my target was an i386 system with 32MB of RAM.

### Minimum requirements
- CD-ROM Drive
- 22 Megabytes of RAM
- i386 (for pixix applications)
- i686 (e.g. Pentium Pro or later, for busybox applications)

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

## Applications
### Available in the initramfs
```
init shell cat mount umount ls*
```
*\* these are handled by busybox*

### Available on the disk
```
ping pitch cp* fdisk* ifconfig* mkfs.ext2* route* udhcpc* wget*
```
*\* these are handled by busybox*

# Resources
- [Linux `man 2` pages](https://linux.die.net/man/2/)
- [Making Smallest Possible Linux Distro (x64) by Nir Lichtman](https://youtu.be/u2Juz5sQyYQ)
- [i386 Linux 2.2+ Syscalls by h-peter recktenwald](https://www.lxhp.in-berlin.de/lhpsysc1.html)
- [Linux man pages online by Michael Kerrisk](https://www.man7.org/linux/man-pages)
- [Linux System Call Table for x86_64](https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)
- [System Call Table](https://web.archive.org/web/20160213015253/http://docs.cs.up.ac.za/programming/asm/derick_tut/syscalls.html)