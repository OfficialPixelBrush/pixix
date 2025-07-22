.intel_syntax noprefix

.global sys_mmap
.global sys_munmap

sys_mmap: # Technically sys_old_mmap
    mov ebx, [esp + 4]
    mov eax, 90
    int 0x80
    ret

sys_munmap:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov eax, 91
    int 0x80
    ret
