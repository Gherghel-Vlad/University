bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 324
    l_a EQU $-a
    r RESW 1

; our code starts here
segment code use32 class=code
    start:
        
        mov ecx, l_a
        mov edx, 0 ; my result
        mov ax, [a]
        jecxz EndLoop
        Repeta:
            mov cl, 10
            div cl ; AL = AX/10 AH= AX%10
            add edx, ah
            mov ah, 0
        
        loop Repeta
        
        
        EndLoop:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
