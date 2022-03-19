bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte, b - word, c - double word, d - qword - Signed representation
    a db 100
    b dw 500
    c dd 70000
    d dq 100000
    result RESQ 1
    
    
; our code starts here
segment code use32 class=code
    start:
        ; (b+b+d)-(c+a) = (500 + 500 + 100000) - (70000 + 100) = 101000 - 70100 = 30900
        
        mov ax, [b]
        add ax, [b]
        ; AX = b+b
        
        CWDE
        CDQ
        ; signed transformation of b+b (byte) in qword EDX:EAX = b+b
        add eax, dword [d+0]
        adc edx, dword [d+4]
        ; EDX:EAX = b+b+d
        
        mov ebx, eax
        mov ecx, edx
        ; ECX:EBX = EDX:EAX = b+b+d
        
        mov al, [a]
        CBW
        CWDE
        ; signed transformation of a (byte) into dword
        
        add eax, [c]
        ; EAX = a+c
        CDQ
        ; EDX:EAX = a+c (sign conversion dword -> qword)
        
        sub ebx, eax
        sbb ecx, edx
        ; ECX:EBX = (b+b+d)-(c+a)
        
        mov dword [result+0], ebx
        mov dword [result+4], ecx
        
        
        
        
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
