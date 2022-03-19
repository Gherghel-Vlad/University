bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    a db 20
    c db 25
    d db 30
    f dw 150
    

; our code starts here
segment code use32 class=code
    start:
        ; f+(c-2)*(3+a)/(d-4) = 150 + (23 * 23) / 26 = (3900 + 529) /26 = 4429 / 26 = 170 r 9
        
        ; here we do the (c-2) * (3 + a)
        mov AL, [c] ; al = c
        sub AL, 2; Al -=2
        mov BL, [a] ; bl = c
        add bl, 3 ; bl += 3
        mul BL ; AX = AL * BL
        
        ; here we make f*(d-4)/(d-4) so that we can add the higher part of the function
        ; ax will have the (c-2) * (3 + a) result
        mov bx, ax; bx = ax
        
        mov al, [d]; bl = d
        sub al, 4; bl -= 4
        mov ah, 0; ah = 0
        
        mul word [f]; DX:AX = f * AX
        
        ; here we add the ax =f*(d-4)/(d-4) to the bx =(c-2)*(3+a)/(d-4)
        add ax, bx; ax += bx
        
        ; here we divide the sum to d-4
        mov bl, [d]; bl =d
        sub bl, 4; bl-=4
        ; depend on the valors i cant make a signed division here...in my case i cant
        ; for signed values chenge the 2 muls from above as well in imuls
        div bl ; al = ax/bl ah = ax%bl
        
        
        
        
        
        
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
