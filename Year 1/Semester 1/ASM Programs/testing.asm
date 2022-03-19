bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll                              ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
        a db 10, "bvcx "
        
        b db "asbfd sg ! fds  gdg", 0
        format db "%s",0
        c db " asbfdsg", 0
        
        message db "haha", 0
        
        nr resb 15

        print_1 db "  1", 0
        print_0 db "0", 0
; our code starts here
segment code use32 class=code
    start:
        
        push dword b
        push dword format
        call [printf]
        add esp, 4*2
        
    
        mov ecx, nr
        
        mov al, 0abh
        cwd
        
        mov bl, 10
        
        idiv bl
        
        mov byte [nr], "-"
        inc ecx
        
        mov bl, 16
        
        
        shl al, 4
        shr al, 4
        sub bl, al
        
        mov al, bl
        
        add al, '0'
        
        mov bl, 16
        
        shl ah, 4
        shr ah, 4
        sub bl, ah
        
        mov ah, bl
        
        add ah, '0'
        
        mov byte [ecx], al
        inc ecx
        
        mov byte [ecx], ah
        inc ecx
        
        
        
        
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
