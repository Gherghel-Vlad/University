bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 20
    b db 30
    c db 40
    d dw 150

; our code starts here
segment code use32 class=code
    start:
        ; [-1+d-2*(b+1)]/a = [-1 + 150 - 2 * (30 + 1)] / 20 = (149 - 62) / 20 = 87/20 = 4 r 7 
        mov AL, [b]; AL = b
        add AL, 1; AL += 1
        mov BL, 2 ; BL = 2
        imul BL ; AX = BL  * AL
        
        mov BX, [d] ; bx = d
        add BX, -1 ; BX += -1
        sub BX, AX ; BX -= AX
        
        mov AX, BX; AX = BX
        idiv byte [a] ; AL = AX/a  AH=AH%a
    
    
    
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
