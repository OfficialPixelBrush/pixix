.intel_syntax noprefix

no_path:
    .ascii "No path passed!\n\0"
no_path_end:

.global _start

_start:
    mov eax, [esp]         # argc
    cmp eax, 2             # Need at least 2 arguments (program + path)
    jl noarg               # if argc < 2, skip chroot call

    mov ebx, [esp + 8]     # argv[1] pointer = path for chroot syscall

    mov eax, 61            # syscall chroot
    int 0x80
    jmp end
    
    noarg:
    mov ebx, 1          # STDOUT
    mov ecx, no_path
    mov edx, no_path_end - no_path # string is 17 chars
    mov eax, 4
    int 0x80
    # Exit sys call
    # Return 0, all went good
    end:
    mov ebx, 0
    mov eax, 1
    int 0x80
