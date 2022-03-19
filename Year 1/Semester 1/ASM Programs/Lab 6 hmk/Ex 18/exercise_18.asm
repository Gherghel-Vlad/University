bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir DD 12AB5678h, 1256ABCDh, 12344344h
    len EQU ($-sir)/4 ; i want the number of words
    four dd 4

; our code starts here
segment code use32 class=code
    start:
        ; I am doing this on Johnny Cash songs :)
        ; A string of doublewords is given. Order in increasing order the string of the high words (most significant) from these doublewords. The low words (least significant) remain unchanged.
        
        mov ebx, 0 ; this will show on which position i am on in the array (to which i compare to the whole string)
        mov edx, 1 ; this will show me to whom i will compare that one element on the position
        
        ; Johnny Cash - Hurt really good song
        
        NotYetFinished:
        
        mov eax, ebx
        mul DWORD [four]
        add eax, sir
        mov esi, eax ; ESI will show to whom i will compare everything
        
        LODSD ; EAX = the value to whom i will compare everything 
        
        mov edx, ebx
        inc edx ; starting from the next element after the position EBX will show me
        
        mov ecx, eax ; ECX = EAX
        
        
        ContinueComparingBoye:
        ror ecx, 16
        
        push edx ; saving the index so that it s not erased in the multiplication
        
        mov eax, edx
        mul DWORD [four]
        add eax, sir
        mov esi, eax ; ESi will show to whom i compare to the element from ECX
        
        pop edx ; getting the index back 
        
        LODSD ; EAX got the  the one to i compare with the element on the fixed position
        
        ror eax, 16
        ; i only care about the high part from both of them ... 
        ; Johnny Cash The Man Comes Around really good song as well
        
        cmp ax, cx
        jg DontInterchange
            
            push WORD ax
            push WORD cx
            
            pop WORD ax
            pop WORD cx ; interchanged AX and CX without changing the high parts...i hope
            
            ror eax, 16
            ror ecx, 16
            
            push edx
            push eax
            
            mov eax, edx
            mul DWORD [four]
            add eax, sir
            mov edi, eax ; EDI will show me where to save the one that s less
            
            pop eax
            pop edx
            
            STOSD 
            
            push edx
            push eax
            
            mov eax, ebx
            mul DWORD [four]
            add eax, sir
            mov edi, eax ; EDI will show me where to save the one that s greater
            
            pop eax
            pop edx
            
            mov eax, ecx
            STOSD 
        
        
        DontInterchange:
        
        
        inc edx
        
        cmp edx, len
        jl ContinueComparingBoye
        
        inc ebx
        mov ecx, len
        dec ecx ; this will show me the actual number on which EBX must arrive
        cmp ebx, ecx
        jl NotYetFinished
        
        
        
        
        
        
        
        
        
        
        
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
