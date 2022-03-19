bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 1010_1001_1011_1011b
    b RESD 1 ; the result should be 0000 1001 0000 1111 1111000010010000 = 11110000100100001111000010010000
                                                                          ;11110000100100001111000010010000

; our code starts here
segment code use32 class=code
    start:
        ; Given the word A, compute the doubleword B as follows:
        ;    the bits 0-3 of B have the value 0;
        ;    the bits 4-7 of B are the same as the bits 8-11 of A
        ;    the bits 8-9 and 10-11 of B are the invert of the bits 0-1 of A (so 2 times) ;
        ;    the bits 12-15 of B have the value 1
        ;    the bits 16-31 of B are the same as the bits 0-15 of B.
        
        
        mov ebx, 0 ; EBX will be my result
        
        ;    the bits 0-3 of B have the value 0;
        
        and bl, 11110000b ; forced bits 0-3 to be 0
        
        ;    the bits 4-7 of B are the same as the bits 8-11 of A
        mov ax, [a]
        and ax, 0000_1111_0000_0000b ; we isolated the bits 8-11 of AX (a)
        mov cl, 4
        ror ax, cl ;  rotated to the right 4 positions
        or bx, ax ; we put the bits in the result
        
        ;    the bits 8-9 and 10-11 of B are the invert of the bits 0-1 of A (so 2 times) ;
        mov ax, [a]
        not ax ;  inverting the bits of AX (a)
        and ax, 0000000000000011b ; isolated bits 0-1 of AX (a)
        mov cl, 8
        rol ax, cl ; rotated the bits 0-1 to position 8-9
        or bx, ax ; put the bits in the result
        mov cl, 2
        rol ax, cl ; rotated the bits 2 positions (from 8-9 position to 10-11)
        or bx, ax ; put the bits in the result
        
        ;    the bits 12-15 of B have the value 1
        or bh, 11110000b ; forced the bits 12-15 to have value 1
        
        ;    the bits 16-31 of B are the same as the bits 0-15 of B.
        mov ax, bx ; saved the 0-15 bits of EBX to AX 
        mov cl, 16
        rol ebx, cl ; rotated so that i have the high part in the low part of EBX
        mov bx, ax ;  here i put the bits into BX
        rol ebx, cl ; rotated so that everything is back to normal
        
        mov [b], ebx
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
