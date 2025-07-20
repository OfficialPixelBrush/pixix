rm shell
gcc -m32 -static -march=i486 shell.c -o shell
rm fetch
gcc -m32 -static -march=i486 fetch.c -o fetch
rm setup
gcc -m32 -static -march=i486 setup.c -o setup
#gcc -c shell.c
#as sys.s
#ld -o shell shell.o a.out --entry main -z noexecstack
#mv shell init
#echo init | cpio -H newc -o > init.cpio