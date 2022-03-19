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
        ; (d-b)-a-(b-c) = (100000 - 500) - 100 - (500 - 70000) = 99500 - 100 + 69500 = 168,900
        
        mov ax, [b]
        cwde
        cdq
        ; signed conversion from ax -> eax -> edx:eax = b
        
        mov ebx, dword [d+0]
        mov ecx, dword [d+4]
        ; ECX:EBX = d
        
        sub ebx, eax
        sbb ecx, edx
        ; ECX:EBX = d-b
        
        mov al, [a]
        cbw
        cwde
        cdq
        ; EDX:EAX = a
        
        sub ebx, eax
        sbb ecx, edx
        ; ECX:EBX = (d-b)-a
        
        ;push ecx
        ;push ebx
        ; saved ECX:EBX in stack
        
        mov ax, [b]
        cwde
        ; EAX = b
        
        sub eax,  dword [c]
        ; EAX = b-c
        
        cdq
        ; EDX:EAX = b-c
        
        ;pop ebx
        ;pop ecx
        ; ECX:EBX = (d-b)-a
        
        sub ebx, eax
        sbb ecx, edx
        ; ECX:EBX = (d-b)-a-(b-c)
        
        mov [result+0], ebx
        mov [result+4], ecx
        
        
        
        
        
        
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
