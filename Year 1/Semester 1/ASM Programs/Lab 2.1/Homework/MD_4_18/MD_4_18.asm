bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 10
    b db 20
    c db 25
    d dw 255

; our code starts here
segment code use32 class=code
    start:
        ; question: if d/a has a rest how do we delete it? or should we substract just like in real life...getting every variable /a first 
        ; 200-[3*(c+b-d/a)-300] = 200 - [3*((455-255)/10) - 300] = 200 - (585/10 - 300) = 200 - (-2415/10) = 4415/10 = 441 r 5
        
        mov AL, [b] ; AL = b
        add AL, [c] ; AL += c
        imul byte [a] ; AX = AL * a
        sub AX, [d]; al = al-d
        
        mov BX, 3
        imul BX; DX:AX = AX * BX
        
        sub AX, 3000 ; ax -= 3000
        mov BX, 2000
        sub BX, AX ; BX = bx - ax 
        mov ax, bx
        
        ;overflow if we divide by a byte that s small
        mov BL, [a]
        mov BH, 0
        idiv BX ; AX = ax/a DX = ax%a
        
    
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
