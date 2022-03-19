bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dw 1100110110101010b
    b dw 1110110011011011b
    c RESD 1 ;  c should be the inverse of 100 011011 0110101 1100110110101010 = 11001101101010100110101011011100
                                                                                ;11001101101010100110101011011100
    
    
    
    
; our code starts here
segment code use32 class=code
    start:
        ; Given the words A and B, compute the doubleword C as follows:
        ;    the bits 0-2 of C are the same as the bits 12-14 of A
        ;    the bits 3-8 of C are the same as the bits 0-5 of B
        ;    the bits 9-15 of C are the same as the bits 3-9 of A
        ;    the bits 16-31 of C are the same as the bits of A
        
        mov ebx, 0 ; in EBX will be my result
        
        ;    the bits 0-2 of C are the same as the bits 12-14 of A
        mov eax, 0
        mov ax, [a]
        and ax, 0111000000000000b ;  isolated the 12-14 bits of A
        mov cl, 12
        ror ax, cl ; we rotate 12 positions to the right
        or ebx, eax ;  we put the bits in the result
        
        ;    the bits 3-8 of C are the same as the bits 0-5 of B
        mov eax, 0
        mov ax, [b]
        and ax, 0000000000111111b ;  we isolate bits 0-5 of B
        mov cl, 3
        rol ax, 3 ;  we rotate 3 positions to the left
        or ebx, eax ; we put the bits in the result
        
        
        ;    the bits 9-15 of C are the same as the bits 3-9 of A
        mov eax, 0
        mov ax, [a]
        and ax, 0000001111111000b ;  isolated the 3-9 bits of A
        mov cl, 6
        rol ax, cl ; we rotate 6 positions to the left
        or ebx, eax ;  we put the bits in the result
        
        ;    the bits 16-31 of C are the same as the bits of A
        mov cl, 16
        rol ebx, cl ; we rotate so that we have the high part ( 16-31 bits) in the BX
        mov ax, [a]
        or bx, ax
        rol ebx, 16
        
        mov [c], ebx
        
        
        
        
        
        
        
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
