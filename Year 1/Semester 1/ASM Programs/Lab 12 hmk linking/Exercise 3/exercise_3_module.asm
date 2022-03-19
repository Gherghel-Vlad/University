bits 32 ; assembling for the 32 bits architecture


; our code starts here
segment code use32 class=code
global concatenate_digits


concatenate_digits:
    ; concatenate_digits(result, string1, string2)
    ; edi will represent the result location
    mov edi, [esp + 4]
    mov esi, [esp + 12] ; esi = string2
    
    ; taking and concatenating the decimal characters from the string2 to the result string
    repeta1:
        lodsb
        ; checking if it didnt reach the end of the string2
        cmp al, 0
        je done1
        
        ; checking if it s a digit
        cmp al, '0'
        jl NotADigit1
        cmp al, '9'
        jg NotADigit1
        
        ; if it went past those 2 checks, it means it s a digit and i can concatenate it to the result string
        stosb
        
        NotADigit1:
    
    jmp repeta1
    done1:
    
    ; taking and concatenating the decimal characters from the string1 to the result string
    mov esi, [esp+8]
    repeta2:
        lodsb
        ; checking if it didnt reach the end of the string1
        cmp al, 0
        je done2
        
        ; checking if it s a digit
        cmp al, '0'
        jl NotADigit2
        cmp al, '9'
        jg NotADigit2
        
        ; if it went past those 2 checks, it means it s a digit and i can concatenate it to the result string
        stosb
        
        NotADigit2:
    
    jmp repeta2
    done2:
    

    ret 3*4 ; clearing 3 doublwords because i sent 3 addresses (the result string adress and the strings adresses) 
    
    