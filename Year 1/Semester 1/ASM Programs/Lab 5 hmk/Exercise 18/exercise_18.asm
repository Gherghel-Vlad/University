bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 2, 1, 3, -3
    l_a EQU $-a
    b db 4, 5, -5, 7 ; , 9, 13, 15, 16, 20, 21
    l_b EQU $-b
    r times (l_a+l_b) db -1

; our code starts here
segment code use32 class=code
    start:
        ; Two byte strings A and B are given. Obtain the string R that 
        ; contains only the odd positive elements of the two strings
        ; A: 2, 1, 3, -3
        ; B: 4, 5, -5, 7
        ; R: 1, 3, 5, 7
        
        
        mov ecx, l_a ; ECX = size of a
        mov esi, 0 ; index for a
        mov edx, 0 ; index for result location
        jecxz EndLoop1
        Repeat1:
            mov al, 0
            cmp [a+esi], al
            js IsNegative1 ; jumps if it s a negative number
            mov ax, 0
            mov al, [a+esi]
            mov bl, 2
            div bl ; AH = AX % BL, AL = AH/AL
            mov al, 1
            cmp ah, al
            jnz IsNotOdd1
            mov bl, [a+esi]
            mov [r+edx], bl ; saving the result if it s a positive odd number
            inc edx
            IsNotOdd1:
            IsNegative1:
            inc esi
        loop Repeat1
        EndLoop1:
        
        mov ecx, l_b ; ECX = size of b
        mov esi, 0 ; index for a
        jecxz EndLoop2
        Repeat2:
            mov al, 0
            cmp [b+esi], al
            js IsNegative2 ; jumps if it s a negative number
            mov ax, 0
            mov al, [b+esi]
            mov bl, 2
            div bl ; AH = AX % BL, AL = AH/AL
            mov al, 1
            cmp ah, al
            jnz IsNotOdd2
            mov bl, [b+esi]
            mov [r+edx], bl ; saving the result if it s a positive odd number
            inc edx
            IsNotOdd2:
            IsNegative2:
            inc esi
        loop Repeat2
        EndLoop2:
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
