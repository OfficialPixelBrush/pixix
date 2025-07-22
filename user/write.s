.intel_syntax noprefix
.section .text
.global _start

_start:
    mov   ebx, 1              # fd = STDOUT
    lea   ecx, [message]
    mov   edx, message_end - message
    mov   eax, 4              # sys_write
    int   0x80

    mov   ebx, 0              # status = 0
    mov   eax, 1              # sys_exit
    int   0x80

.section .rodata
message:
    .ascii "Test!\n"
message_end:
