bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a,b-byte; c-word; e-doubleword; x-qword
    a db 150
    b db 200
    c dw 2000
    e dd 100000
    x dq 2000000
    result RESQ 1
    

; our code starts here
segment code use32 class=code
    start:
        ; (a+b*c+2/c)/(2+a)+e+x = (150 + 200*2000 +2/2000)/(2+150) + 100.000 + 2.000.000 = (150 + 400,000)/152 + 100.000 =
        ; = 400.150 / 152 + 100.000 + 2.000.000 = 2632 r 86 + 100.000 + 2.000.000= 102.632 r 86 + 2.000.000 = 2.102.632 r 82 
        
        mov al, [b]
        mov ah, 0
        ; unsigned conversion b (byte) in AX (word)
        
        mul word [c]
        ; DX:AX = b*c
        
        push dx
        push ax
        pop ebx
        ; EBX = b*c
        
        mov ax, 2
        mov dx, 0
        div word [c]
        ; AX = 2/c DX = 2%c
        
        ; I wont care about the remainder from now on
        
        mov ecx, 0
        mov cx, ax
        ; ECX = 2/c
        
        mov eax, 0
        mov al, [a]
        ; unsigned conversion from a (byte) in EAX (dword)
        
        add ebx, eax
        add ebx, ecx
        ; EBX = a+b*c+2/c
        
        mov ax, 0
        mov al, [a]
        add al, 2
        ; AX = 2+a
        
        push ax
        pop cx
        push ebx
        pop ax
        pop dx
        ; EAX = a+b*c+2/c
        ; CX = 2+a
        
        
        div cx
        ; AX = (a+b*c+2/c) / (2+a) DX = (a+b*c+2/c) % (2+a)
        
        mov ebx, 0
        mov bx, ax
        ; EBX = (a+b*c+2/c) / (2+a)
        
        mov eax, [e]
        ; EAX = e
        
        add eax, ebx
        ; EAX = (a+b*c+2/c) / (2+a) + e
        
        mov edx, 0
        ; unsigned conversion EDX:EAX = (a+b*c+2/c) / (2+a) + e
        
        add eax, dword [x+0]
        adc edx, dword [x+4]
        
        mov [result], eax
        mov [result+4], edx
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
