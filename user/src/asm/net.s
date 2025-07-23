.intel_syntax noprefix

.global sys_socket
.global sys_bind
.global sys_connect
.global sys_setsockopt
.global sys_sendto
.global sys_recvfrom

sys_socket:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov eax, 359
    int 0x80
    ret

sys_bind:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov eax, 361
    int 0x80
    ret

sys_connect:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov eax, 362
    int 0x80
    ret

sys_setsockopt:
    mov     ebx, [esp + 4]
    mov     ecx, [esp + 8]
    mov     edx, [esp + 12]
    mov     esi, [esp + 16]
    mov     edi, [esp + 20]
    mov eax, 366
    int 0x80
    ret

sys_sendto:
    mov     ebx, [esp + 4]
    mov     ecx, [esp + 8]
    mov     edx, [esp + 12]
    mov     esi, [esp + 16]
    mov     edi, [esp + 20]
    mov     ebp, [esp + 24]
    mov eax, 369
    int 0x80
    ret

sys_recvfrom:
    mov     ebx, [esp + 4]
    mov     ecx, [esp + 8]
    mov     edx, [esp + 12]
    mov     esi, [esp + 16]
    mov     edi, [esp + 20]
    mov     ebp, [esp + 24]
    mov eax, 371
    int 0x80
    ret
