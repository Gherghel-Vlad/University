bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fread, printf, fscanf, scanf            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fscanf msvcrt.dll
import scanf msvcrt.dll
import fclose msvcrt.dll 

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "cuvinte.txt", 0
    read_access db "r", 0
    file_descriptor dd -1
    
    text db "L = ", 0
    
    text_for_empty_case db "No words with the length an odd number and smaller than L exist in that file.", 0
    check_digit_for_empty_case dd 0 ; 0 - False, it didnt found any words, 1 - True, it found words
    
    maximum_length dd -1 ; this is L
    current_word resb 50
    read_format_string db "%s", 0
    read_format_number db "%d", 0
    write_format db "%s ", 0
    
    

; our code starts here
segment code use32 class=code
    start:
        ; opening the file
        push dword read_access
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax
        
        ; checking if the file was opened succesfully
        cmp eax, 0
        jz final
        
        ; printing the message before reading L
        push dword text
        call [printf]
        add esp, 4
        
        ; reading the L (maximum length of a word)
        ;int scanf(const char *format, ...)
        push dword maximum_length
        push dword read_format_number
        call [scanf]
        add esp, 4*2
        
        repeat1:
            
            ; reading a word
            ; int fscanf(FILE *stream, const char *format, ...)
            push dword current_word
            push dword read_format_string
            push dword [file_descriptor]
            call [fscanf]
            add esp, 4*3
            
            cmp eax, -1 ; checking if i reached the end of the file
            je done
            
            ; calculating the length of the word
            mov ebx, 0 ; ebx will show the length of the current word
            
            cld ; clearing the direction flag
            mov esi, current_word
            
            repeat2:
                lodsb
                
                cmp al, 0 ; if it reached the end of the word
                je DoneCountingTheLength
                
                inc ebx 
            
            jmp repeat2
            
            ; adding the 0 at the end of the word
            mov byte [current_word + ebx], 0
            
            DoneCountingTheLength:
            ; ebx will have my current word's length
            
            ; checking if it s an odd number
            mov ax, bx ; preparing the DX:AX value to be printed
            mov dx, 0 
            mov cx, 2
            div cx
            
            cmp dx, 1 
            jne NotAGoodWord
            
            ; if it reached here it means the length of the word is an odd number
            ; checking if it s smaler than L
            cmp ebx, dword [maximum_length]
            jnl NotAGoodWord
            
            ; if it reached here it means that the word is correct and needs to be printed on the screen
            push dword current_word
            push dword write_format
            call [printf]
            add esp, 4*2
            
            ; making the check digit True 
            mov ecx, 1
            mov [check_digit_for_empty_case], ecx
            
            NotAGoodWord:
            
        
        jmp repeat1
        
        done:
        
        mov ebx, 0
        cmp dword [check_digit_for_empty_case], ebx
        jne closefile
        
        push dword text_for_empty_case
        call [printf]
        add esp, 4
        
        
        closefile:
        
        ; closing the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        
        
        final:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
