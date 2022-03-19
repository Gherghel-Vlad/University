bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, printf, fread             
import exit msvcrt.dll      
import fopen msvcrt.dll      
import fclose msvcrt.dll      
import printf msvcrt.dll    
import fread msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        file_name db "file.txt", 0
        read_mode db "r", 0
        file_descriptor dd -1
        text db "The number of even digits in the file is: %d", 0
        even_digits_number dd 0
        digit resb 1

; our code starts here
segment code use32 class=code
    start:
        ; A text file is given. Read the content of the file, count the number of even digits and display the result on the screen. The name of text file is defined in the data segment.
        
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
            ; reading a digit from the file
            push dword [file_descriptor]
            push dword 1
            push dword 1
            push dword digit
            call [fread]
            add esp, 4 * 4
            
            ; checking if i am at the end of the file
            cmp eax, 0
            je close
            
            ; checking if the byte that was read is a digit or not
            cmp byte [digit], '0'
            jl loop_read
            
            cmp byte [digit], '9'
            jg loop_read
            
            ; cheking if it s an even digit
            mov al, [digit]
            clc
            rcr al, 1
            ; if it s not an even number, jump
            jae loop_read
            
            add dword [even_digits_number], 1
            
        
        
        
        jmp loop_read
        
        
        close:
        
        ;int printf(const char * format, variable_1, constant_2, ...);
        ; printing the result on the screen
        push dword [even_digits_number]
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
