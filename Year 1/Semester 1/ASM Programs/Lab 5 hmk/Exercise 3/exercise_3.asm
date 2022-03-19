bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        s1 db 1, 2, 3, 4
        l_s1 EQU $-s1
        s2 db 5, 6, 7 ; , 8, 9
        l_s2 EQU $-s2
        d times (l_s1+l_s2) db -1

; our code starts here
segment code use32 class=code
    start:
        ; Two byte strings S1 and S2 are given. Obtain the string D by concatenating 
        ; the elements of S1 from the left hand side to the right hand side  
        ; and the elements of S2 from the right hand side to the left hand side.
        ; S1: 1, 2, 3, 4
        ; S2: 5, 6, 7
        ; D: 1, 2, 3, 4, 7, 6, 5
        
        mov ecx, l_s1 ; ECX = size of s1
        mov esi, 0 ; my index for going trough d 
        jecxz endLoop1
        Repeat1:
            mov bl, [s1+esi] ; moved in bl the string value from the position s1_esi
            mov [d+esi], bl ; saved in the destination location
            inc esi ; gotta go up to the next position for s1 and d
        loop Repeat1
        endLoop1:
        
        mov ecx, l_s2 ; ECX = size of s2
        jecxz endLoop2
        Repeat2:
            mov ebx, ecx ; i need the position s2 + ECX - 1
            dec ebx
            mov bl, [s2+ebx] ; saved in BL the element to be saved in the destiantion location
            mov [d+esi], bl ; saving that element where it needs to be
            inc esi ; going to the enxt location of d
        loop Repeat2
        endLoop2:
        
    
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
