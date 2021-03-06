bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 200
    b dw 300
    c dw 250
    d dw 400
    x dw 0

; our code starts here
segment code use32 class=code
    start:
        ; (b+b+d)-(c+a) = (300 + 300 + 400) - (250 + 200) = 1000 - 450 = 550
        mov AX, [b] ; AX = b
        add AX, [b] ; AX = AX + b
        add AX, [d] ; AX = AX + d
        
        mov BX, [c] ; BX = c
        add BX, [a] ; BX = BX + a
        
        sub AX, BX ; AX = AX - BX 
        mov [x], AX 
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
