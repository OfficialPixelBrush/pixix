.intel_syntax noprefix

.global _start

_start:
    mov eax, 88         
    mov ebx, 0xfee1dead 
    mov ecx, 672274793
    mov edx, 0x1234567 
    int 0x80
    
    mov eax, 1  
    xor ebx, ebx
    int 0x80
