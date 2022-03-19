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
    a db 150
    b db 200
    d db 250
    c dd 4000000
    x dq 100000
    result RESQ 1

; our code starts here
segment code use32 class=code
    start:
        ; (8-a*b*100+c)/d+x = (8 - 150*200*100 + 4000000)/250 + 100000 = (8 - 3.000.000 +4.000.000)/250 +100000 =1.000.008/250 + 100.000=  
        ; =4000 r 8 + 100.000 = 104.000 r 8
       
        ; Because of 8-a*b*100 i will have to select specific numbers to be able to do unsigned representation : /
        ; I will assume c+8 > a*b*100 or else it wont be unsigned anymore
        
        mov al, [a]
        mul byte [b]
        ; AX = a*b
        
        mov bx, 100
        mul bx
        ; DX:AX = a*b*100
        
        push dx
        push ax
        pop ecx
        ; ECX = DX:AX
    
        mov ebx, 8
        add ebx, [c]
        ; EBX = 8+c
        
        sub ebx, ecx
        ; EBX = 8-a*b*100+c
        
        mov al, [d]
        mov ah, 0
        ; conversion of d (byte) in AX (word)
        
        mov cx, ax
        push ebx
        pop ax
        pop dx
        div cx
        ; AX = (8-a*b*100+c)/d DX = (8-a*b*100+c)%d
        
        ; I wont care about the remainder from now on
        
        mov cx, ax
        mov eax, 0
        mov ax, cx
        mov edx, 0
        ; unsigned conversion from AX (word) to EDX:EAX (qword)
        
        add eax, dword [x+0]
        adc edx, dword [x+4]
        ; EDX:EAX = (8-a*b*100+c)/d+x
        
        mov [result+0], eax
        mov [result+4], edx
        
        
    
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
