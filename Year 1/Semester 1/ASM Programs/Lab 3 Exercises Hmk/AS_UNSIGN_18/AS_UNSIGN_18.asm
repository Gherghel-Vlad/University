bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    ;a - byte, b - word, c - double word, d - qword - Unsigned representation
    a db 130
    b dw 400
    c dd 70000
    d dq 100000
    result resq 1
; our code starts here
segment code use32 class=code
    start:
        ; (d+d)-a-b-c = (100000 + 100000) - 130 - 400 - 70000 = 129,470
        mov eax, dword [d+0]
        mov ebx, dword [d+4]
        ; EBX:EAX = d
        
        mov ecx, dword [d+0]
        mov edx, dword [d+4]
        ; EDX:ECX = d
        
        add eax, ecx
        adc ebx, edx
        ; EBX:EAX = d+d
        
        mov ecx, 0
        mov cl, [a]
        mov edx, 0
        ; unsigned conversion of a from byte to qword EDX:ECX = a
        
        sub eax, ecx
        sbb ebx, edx
        ; EBX:EAX = (d+d)-a
        
        mov ecx, 0
        mov cx, [b]
        mov edx, 0
        ; unsigned conversion of b from byte to qword EDX:ECX = b
        
        sub eax, ecx
        sbb ebx, edx
        ; EBX:EAX = (d+d)-a-b
        
        mov ecx, [c]
        mov edx, 0
        ; unsigned conversion of c from byte to qword EDX:ECX = c
        
        sub eax, ecx
        sbb ebx, edx
        ; EBX:EAX = (d+d)-a-b-c
        
        mov dword [result], eax
        mov dword [result+4], ebx
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
