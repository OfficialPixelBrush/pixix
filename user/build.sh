rm shell
gcc -m32 -static shell.c -o shell
rm fetch
gcc -m32 -static fetch.c -o fetch
#gcc -c shell.c
#as sys.s
#ld -o shell shell.o a.out --entry main -z noexecstack
#mv shell init
#echo init | cpio -H newc -o > init.cpio