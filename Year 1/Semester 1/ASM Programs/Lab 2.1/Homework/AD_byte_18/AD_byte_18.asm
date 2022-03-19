bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    a db 3
    b db 10
    c db 8
    d db 30
    x db 0
    

; our code starts here
segment code use32 class=code
    start:
        ; d-(a+b)+c
        mov AL, [a] ; AL = a
        add AL, [b] ; AL = AL + b
        ; This works too
        sub [d], AL ; d= d - AL
        mov AL, [d]
        add AL, [c]; d = d + c
        mov [x], AL
        
        ; This works
        ;mov BL, AL ; BL = AL
        ;mov AL, [d] ; AL = d
        ;sub AL, BL; AL = AL - BL
        ;add AL, [c] ; AL = AL + c
        ;mov [x], AL
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
