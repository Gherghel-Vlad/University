bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a,b,d-byte; c-doubleword; x-qword
    a db 50
    b db 80
    d db 110
    c dd 2000
    x dq 100000
    result RESQ 1

; our code starts here
segment code use32 class=code
    start:
        ; (8-a*b*100+c)/d+x = (8 - 50*80*100 +2000)/110 + 100.000 = (8 - 400.000 + 2000)/110 + 100.000 = -397,992/110 +100.000 =
        ; = -3618 r 12 + 100.000 = 96,382 r 12
        
        mov al, [a]
        imul byte [b]
        ; AX = a*b
        
        mov bx, 100
        imul bx
        ; DX:AX = a*b*100
        
        push dx
        push ax
        pop ecx
        ; ECX = DX:AX
    
        mov ebx, 8
        sub ebx, ecx
        ; EBX = 8-a*b*100
        
        add ebx, [c]
        ; EBX = 8-a*b*100+c
        
        mov al, [d]
        cbw
        ; signed conversion of d (byte) in AX (word)
        
        mov cx, ax
        push ebx
        pop ax
        pop dx
        idiv cx
        ; AX = (8-a*b*100+c)/d DX = (8-a*b*100+c)%d
        
        ; I wont care about the remainder from now on
        
        cwde
        cdq
        ; signed conversion from AX (word) to EDX:EAX (qword)
        
        add eax, dword [x+0]
        adc edx, dword [x+4]
        ; EDX:EAX = (8-a*b*100+c)/d+x
        
        mov [result+0], eax
        mov [result+4], edx
        
        
    
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
