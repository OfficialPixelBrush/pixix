.intel_syntax noprefix
    .global _start
_start:
    mov  eax, [esp]     # Get value of argument count
    lea  ebx, [esp + 4] # Get pointer to argv
    push 0      # Don't care about envp
    push ebx    # Pointer to argv[0]            
    push eax    # Argument count
    call main
    mov ebx,eax # Get the exit code
    mov eax, 1  # sys_exit
    int 0x80
