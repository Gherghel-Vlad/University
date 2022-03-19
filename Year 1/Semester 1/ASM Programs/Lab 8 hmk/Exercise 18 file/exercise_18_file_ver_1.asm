bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, printf, fread                   ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll 
import fopen msvcrt.dll 
import fclose msvcrt.dll 
import printf msvcrt.dll 
import fread msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        ; johnny cash again : )
        file_name db "file.txt", 0
        read_mode db "r", 0
        file_descriptor dd -1
        number_of_words dd 0, 0
        text db "The number of words in the file is: %d", 0
        byte_read db 0,  0
        last_byte_read db -1, 0
        
        

; our code starts here
segment code use32 class=code
    start:
        ; A text file is given. The text contains letters, spaces and points. Read the content of the file, determine the number of words and display the result on the screen. (A word is a sequence of characters separated by space or point)
        ; mov [last_byte_read], byte -1
        ; mov [number_of_words], dword 0
        ; BIG QUESTION!!!: WHY DO I GET AN ACCESS VIOLATION TO THE MEMORY VARIABLES THAT ARE UP IF I DONT DO WHAT I DID 
        ; I get memory access violation to an add and push for both of those variables. And if i dont do that weird mov at the beginning
        ; i cant run in debug mode. I can build it and run it. UPDATE: But now it works...if i deleted that
        
        ; opening the file
        ; FILE * fopen(const char* file_name, const char * access_mode)
        push dword read_mode
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        
        mov [file_descriptor], eax
        
        ; check if it opened correctly
        cmp eax, 0
        je final
        
        loop_read:
            
            ;int fread(void * str, int size, int count, FILE * stream)
            ; reading a character from the file
            push dword [file_descriptor]
            push dword 1
            push dword 1
            push dword byte_read
            call [fread]
            add esp, 4 * 4
            
            ; byte_read will have the character read from the file
            
            cmp eax, 0
            je LastWordCase
            
            ; i will check if it s a letter or not
            
            cmp byte [byte_read], 'A'
            jl NotCharacter
            cmp byte [byte_read], 'Z'
            jle done
            cmp byte [byte_read], 'a'
            jl NotCharacter
            cmp byte [byte_read], 'z'
            jg NotCharacter
            ; if it s a letter then i will go read the next one
            jmp done
            
            NotCharacter:
            
            ; if it s not a character, but the last character read is, that means it s a word
            ; jump to the next read of a byte if it s the first reading 
            cmp byte [last_byte_read], -1
            je done
            
            ; check if the last byte read is a character
            
            cmp byte [last_byte_read], 'A'
            jl done
            cmp byte [last_byte_read], 'Z'
            jle ItsANewWord
            cmp byte [last_byte_read], 'a'
            jl done
            cmp byte [last_byte_read], 'z'
            jg done
            
            ItsANewWord:
            ; this means that it s new word read
            add dword [number_of_words], 1
            
            
            done:
            
            mov ah, [byte_read]
            mov [last_byte_read], ah
        
        jmp loop_read
        
        LastWordCase:
        
        ; if the last byte read was a letter, it wasnt comparred to anything, so i have to check it as well
        cmp byte [last_byte_read], 'A'
        jl close
        cmp byte [last_byte_read], 'Z'
        jle Continue
        cmp byte [last_byte_read], 'a'
        jl close
        cmp byte [last_byte_read], 'z'
        jg close
        
        Continue:
        add dword [number_of_words], 1
        
        
        
        close:
        
        
        ;int printf(const char * format, variable_1, constant_2, ...);
        ; printing the result on the screen
        push dword [number_of_words]
        push dword text
        call [printf]
        add esp, 4 * 2
        
        
        ;int fclose(FILE * descriptor)
        ; closing the opened file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4 * 1
        
        
        
        final:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
