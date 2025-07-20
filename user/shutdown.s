.intel_syntax noprefix
.global _start

_start:
    mov eax, 88               # sys_reboot
    mov ebx, 0xfee1dead       # magic1
    mov ecx, 672274793        # magic2
    mov edx, 0x4321fed        # LINUX_REBOOT_CMD_POWER_OFF
    int 0x80

    # If reboot syscall fails, exit cleanly
    mov eax, 1                # sys_exit
    xor ebx, ebx
    int 0x80
