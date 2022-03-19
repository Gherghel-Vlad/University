bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    A dw 100, 5, 1, 32767, 5339
    lenA equ $-A
    B dw 2, 100, 55, 10000
    lenB equ $-B
    C resw 20
    result_function dw 0
    
    print_format db "%u", 0
    
    
; our code starts here
segment code use32 class=code
    start:
        mov ebx, 0; iterator for the A array
        
        repeat1:
            cmp ebx, lenA
            ja done ;i am done when the iterator is bigger than the number of elements in A
            
            mov dx, [A + ebx] ; get the element from the A array
            pushad
            ; call the function
            
            ; i will assume that the result will be in eax and it s represented on a word
            mov ax, 4
            mov [result_function], ax
            popad
            
            mov cx, [result_function]
            shr dx, cl
            shl dx, cl ; making the X (in out case AX) lower bits 0
            
            mov [C + ebx], dx ; saving the number
            
            inc ebx 
            inc ebx ; incrementing the iterator
        
        jmp repeat1
        done:
        
        
        
        
        
        
        
    
    
    
    
    
    
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
