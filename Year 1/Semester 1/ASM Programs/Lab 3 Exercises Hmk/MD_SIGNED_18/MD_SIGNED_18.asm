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
    a db -50
    b db -100
    c dw 2000
    e dd 100000
    x dq 2000000
    result RESQ 1
    

; our code starts here
segment code use32 class=code
    start:
        ; (a+b*c+2/c)/(2+a)+e+x = (-50 -100 * 2000 + 2/2000)/(2 - 50) + 100.000 + 2.000.000 =
        ; = (-50-200,000) / (-48) + 100.000 + 2.000.000 = 4167 R 34 + 2.100.000 = 2.104.167 r 34  
        
        
        mov al, [b]
        cbw
        ; unsigned conversion b (byte) in AX (word)
        
        imul word [c]
        ; DX:AX = b*c
        
        push dx
        push ax
        pop ebx
        ; EBX = b*c
        
        mov ax, 2
        mov dx, 0
        idiv word [c]
        ; AX = 2/c DX = 2%c
        
        ; I wont care about the remainder from now on
        
        mov ecx, 0
        mov cx, ax
        ; ECX = 2/c
        
        mov al, [a]
        cbw
        cwde
        ; signed conversion from a (byte) in EAX (dword)
        
        add ebx, eax
        add ebx, ecx
        ; EBX = a+b*c+2/c
        
        mov al, [a]
        add al, 2
        ; AX = 2+a
        
        cbw
        ; singed conversion of a (byte) to AX (word)
        
        push ax
        pop cx
        push ebx
        pop ax
        pop dx
        ; EAX = a+b*c+2/c
        ; CX = 2+a
        
        
        idiv cx
        ; AX = (a+b*c+2/c) / (2+a) DX = (a+b*c+2/c) % (2+a)
        
        mov ebx, 0
        mov bx, ax
        ; EBX = (a+b*c+2/c) / (2+a)
        
        mov eax, [e]
        ; EAX = e
        
        add eax, ebx
        ; EAX = (a+b*c+2/c) / (2+a) + e
        
        cdq
        ; signed conversion EDX:EAX = (a+b*c+2/c) / (2+a) + e
        
        add eax, dword [x+0]
        adc edx, dword [x+4]
        
        mov [result], eax
        mov [result+4], edx
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
