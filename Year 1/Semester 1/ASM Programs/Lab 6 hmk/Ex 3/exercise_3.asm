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
    sir dd 0702090Ah, 0B0C0304h, 05060108h
    len EQU ($-sir)/2
    result RESB 6

; our code starts here
segment code use32 class=code
    start:
        ; An array of doublewords, where each doubleword contains 2 values on a word (unpacked, so each nibble is preceded by a 0) is given. Write an asm program to create a new array of bytes which contain those values (packed on a single byte), arranged in an ascending manner in memory, these being considered signed numbers.

        mov edx, 0 ; i will use it to increment trough the result string
        mov esi, sir
        mov ecx, len
       
        jecxz NoDWords
        Repeta1:
            LODSW
            mov bl, al ; saving the low part
            ; I am gonna shift to the right by 4 bits so that the number from the high part will be on the second byte of the low part
            shr ax, 4 ; the shifting
            add al, bl ; now in AL i should have the 2 values packed
            mov [result + edx], al ; saving the byte in my result string
            inc edx ; going to the enxt position in my result string
        
        loop Repeta1
        
        NoDWords:
        
        ; now i will order the string in an ascending order

        
        mov ebx, 0 ; this will show us which byte we will take for comparision with all the other ones
        mov esi, result
        mov edx, 1 ; i will use this one to go trough the result string ( will show the element with whom i will compare the esi one)
        
        NotFinished:
        
        mov edx, ebx
        add edx, 1
        
        ContinueComparing:
        mov edi, result
        add edi, ebx ; EDI will have the adress of the element with whom i compare all the others from the array with
        
        mov esi, result
        add esi, ebx
        LODSB ; loads in AL the byte for which we are going to look for it s position in the string array
        
        cmp al, [result + edx]
        jl DontInterchange ; wont interchange if the first value is greater than the next ones
            mov esi, result
            add esi, edx ; esi will now have the address of the value that s lesser than AL
            
            mov ah, al ; AH will be my auxialiary that i will use in interchanging
            
            LODSB ; AL = the value lesser than what is in AH
            
            STOSB ; EDI will take the value from AL
            
            ror ax, 8 ; AL will now have the greater one
            
            mov edi, esi
            dec edi ; lodsb increments with 1 esi, and i dont want that
            STOSB ; EDI will take the value from AL
            
        DontInterchange:
        inc edx
        
        mov ecx, len
        dec ecx
        cmp edx, ecx 
        jle ContinueComparing ; As long as there are variables to comapre with
        inc ebx
        
        mov ecx, len
        dec ecx
        cmp ebx, ecx
        jl NotFinished ; If there are still positions left that arent checked 
        
        
        ; Thanks God it works!
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
