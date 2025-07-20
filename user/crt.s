.intel_syntax noprefix
    .global _start
_start:
    mov  eax, [esp]      
    lea  ebx, [esp + 4]
    push 0                
    push ebx               
    push eax              
    call main
    ret
