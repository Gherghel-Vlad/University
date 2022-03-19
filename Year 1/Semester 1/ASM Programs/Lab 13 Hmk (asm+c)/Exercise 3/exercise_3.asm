bits 32 

global _concatDecimals


segment data public data use32
    resultStringAddress dd 0
    firstStringAddress dd 0
    secondStringAddress dd 0


segment code public code use32
    ; function will concatinate the decimals from one string to the decimal of the other string
    ; concatDecimals(char result_string, char first_string, char second_string)
    _concatDecimals:
        ; creating the new stack frame
        push ebp
        mov ebp, esp
        ; saving the registers (i might change quite a lot and C compiler might not like it)
        ; pushad
        ; on dword [ebp] I have the ebp value of the caller
        ; on dword [ebp+4] i have the return value
        ; that means on ebp+8 i have second_string, ebp+12 first_string, ebp+16 result_string
        ; i will save the addresses in variables so it s easier for me to work with them
        mov eax, [ebp+8]
        mov [resultStringAddress], eax
        mov eax, [ebp+12]
        mov [firstStringAddress], eax
        mov eax, [ebp+16]
        mov [secondStringAddress], eax
        
        ; going trough the first string and concatinating the decimal values to the result string
        cld
        mov edi, [resultStringAddress]
        mov esi, [firstStringAddress]
        repeat1:
            lodsb
            cmp al, 0
            je Done1
            
            cmp al, '0'
            jl NotDigit1
            cmp al, '9'
            jg NotDigit1
                
            ;if it came here, that means it s a digit
            stosb
            
        
            NotDigit1:
            
            
            
        jmp repeat1
        Done1:
        cld
        ; doing the same for the second string
        mov esi, [secondStringAddress]
        repeat2:
            lodsb
            cmp al, 0
            je Done2
            
            cmp al, '0'
            jl NotDigit2
            cmp al, '9'
            jg NotDigit2
            
            ;if it came here, that means it s a digit
            stosb
            
            
        
            NotDigit2:
            
            
        jmp repeat2
        
        Done2:
        ; restoring the registers
        ; popad
        ; restoring the stack frame
        mov esp, ebp
        pop ebp
        
        ret
        
