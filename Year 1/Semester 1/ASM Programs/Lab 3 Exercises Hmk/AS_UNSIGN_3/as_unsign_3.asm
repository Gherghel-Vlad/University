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
        ; (c+d)-(a+d)+b = (70000 + 100000) - (130 + 100000) + 400 = 170000 - 100130 = 69870 +400 = 70270
        mov eax, [c] ; eax = c
        mov ebx, 0 ; unsigned convert c from dword to qword
        
        add eax, [d+0] 
        adc ebx, [d+4]
        ; EBX:EAX = c+d
        
        push ebx
        push eax
        ; saved c+d
        
        mov eax, 0
        mov al, [a]
        mov ebx, 0
        ; unsigned conversion a from byte to qword EBX:EAX = a
        
        add eax, [d+0]
        adc ebx, [d+4]
        ; ebx:eax = a+d
        
        pop ecx
        pop edx
        ; edx:ecx = c+d
        
        sub ecx, eax
        sbb edx, ebx
        ; edx:ecx = (c+d) - (a+d)
        
        mov eax, 0
        mov ax, [b]
        mov ebx, 0
        ; unsigned conversion of b from dword to qword EBX:EAX = b
        
        add ecx, eax
        adc edx, ebx
        ; EDX:ECX = (c+d)-(a+d)+b
        
        mov dword [result], ecx
        mov dword [result+4], edx
        
        
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
