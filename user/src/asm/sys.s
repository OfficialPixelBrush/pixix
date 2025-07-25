.intel_syntax noprefix

.global sys_exit
.global sys_fork
.global sys_read
.global sys_write
.global sys_open
.global sys_close
.global sys_execve
.global sys_chdir
.global sys_mknod
.global sys_getpid
.global sys_mount
.global sys_umount
.global sys_mkdir
.global sys_ioctl
.global sys_setpgid
.global sys_setsid
.global sys_symlink
.global sys_fstat
.global sys_sysinfo
.global sys_uname
.global sys_init_module
.global sys_delete_module
.global sys_getdents
.global sys_waitid

sys_exit:
    mov ebx, [esp + 4]
    mov eax, 1
    int 0x80
    ret

sys_fork:
    mov eax, 2
    int 0x80
    ret

sys_read:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov eax, 3
    int 0x80
    ret

sys_write:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov eax, 4
    int 0x80
    ret

sys_open:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov eax, 5
    int 0x80
    ret

sys_close:
    mov ebx, [esp + 4]
    mov eax, 6
    int 0x80
    ret

sys_execve:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov eax, 11
    int 0x80
    ret

sys_chdir:
    mov ebx, [esp + 4]
    mov eax, 12
    int 0x80
    ret

sys_mknod:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov eax, 14
    int 0x80
    ret

sys_getpid:
    mov eax, 20
    int 0x80
    ret

sys_mount:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov esi, [esp + 16]
    mov edi, [esp + 20]
    mov eax, 21
    int 0x80
    ret

sys_umount:
    mov ebx, [esp + 4]
    mov eax, 22
    int 0x80
    ret

sys_mkdir:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov eax, 39
    int 0x80
    ret

sys_ioctl:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov eax, 54
    int 0x80
    ret

sys_setpgid:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov eax, 57
    int 0x80
    ret

sys_setsid:
    mov eax, 66
    int 0x80
    ret

sys_symlink:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov eax, 83
    int 0x80
    ret

sys_fstat: # technically sys_newfstat
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov eax, 108
    int 0x80
    ret

sys_sysinfo:
    mov ebx, [esp + 4]
    mov eax, 116
    int 0x80
    ret

sys_uname:
    mov ebx, [esp + 4]
    mov eax, 122
    int 0x80
    ret

sys_init_module:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov eax, 128
    int 0x80
    ret

sys_delete_module:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov eax, 129
    int 0x80
    ret

sys_getdents:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov eax, 141
    int 0x80
    ret

sys_waitid:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov esi, [esp + 16]
    mov eax, 284
    int 0x80
    ret
