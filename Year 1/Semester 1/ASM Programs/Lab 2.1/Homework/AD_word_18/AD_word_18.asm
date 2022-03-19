bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 800
    b dw 300
    c dw 200
    d dw 100
    x dw 0

; our code starts here
segment code use32 class=code
    start:
        ; (a-b-c)+(a-c-d-d) = (800 - 300 - 200) + (800 - 200 - 100 - 100) = 300 + 400 = 700
        mov AX, [a]; ax = a 
        sub AX, [b]; ax -= b
        sub AX, [c]; ax -= c
        
        mov BX, [a]; bx = a 
        sub BX, [c]; bx -=c
        sub BX, [d]; bx -= d
        sub BX, [d]; bx -= d
        
        add AX, BX; AX += BX
        mov [x], ax
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
