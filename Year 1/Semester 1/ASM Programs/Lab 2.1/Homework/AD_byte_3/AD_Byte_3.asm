bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 5
    b db 10
    c db 7
    d db 15
    x db 0

; our code starts here
segment code use32 class=code
    start:
        ; (c+d)-(a+d)+b = (7+15) - (5 + 15) + 10 =22 - 20 + 10 = 12 = C (16)
        mov AL, [c] ; al = c
        add AL, [d] ; AL = AL + d
        mov AH, [a] ; AH =a
        add AH, [d] ; AH = AH + d
        sub AL, AH  ; AL = AL - AH
        add AL, [b]   ; AL = AL + b
        mov [x], AL
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
