bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fread, fprintf, fscanf            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll



segment data use32 class=data
    input_file_name db "input.txt", 0
    input_file_name_descriptor dd -1
    read_access db "r", 0
    
    output_file_name db "output.txt", 0
    output_file_name_descriptor dd -1
    write_access db "w", 0
    
    read_format db "%c", 0
    character_read db 0, 0
    write_format db "%s", 0
    sentence_number dd 0
    

; our code starts here
segment code use32 class=code
    start:
        ; opening the input file
        push dword read_access
        push dword input_file_name
        call [fopen]
        add esp, 4*2
        
        mov [input_file_name_descriptor], eax
        ; checking if it was opened correctly
        cmp eax, 0
        jz final
        
        ; opening the output file
        push dword write_access
        push dword output_file_name
        call [fopen]
        add esp, 4*2
        
        mov [output_file_name_descriptor], eax
        ; checking if it was opened correctly
        cmp eax, 0
        jz final
        
        mov ebx, 0 ; ebx will be my sentence counter
        
        repeat1:
            
            ; reading a character from the input file
            ;int fscanf(FILE *stream, const char *format, ...)
            push dword character_read
            push dword read_format
            push dword [input_file_name_descriptor]
            call [fscanf]
            add esp, 4*3
            
            ; checking if it s end of file
            cmp eax, -1
            je done
            
            ; checking if a new sentence is coming
            cmp byte [character_read], '!'
            jne continue
            
            add ebx, 1
            jmp repeat1
            
            continue:
            ; checking if the character is inside the sentence that i need to print
            mov ax, bx
            cwd
            mov cx, 2
            div cx
            
            cmp dx, 1
            jne NoNeedToPrint
            
            ; printing the character in the file
            ;int fprintf(FILE *stream, const char *format, ...)
            push dword character_read
            push dword write_format
            push dword [output_file_name_descriptor]
            call [fprintf]
            add esp, 4*3
            
        
            
            NoNeedToPrint:
        
        jmp repeat1
        
        done:
        ; closing the files
        push dword [input_file_name_descriptor]
        call [fclose]
        add esp, 4
        
        push dword [output_file_name_descriptor]
        call [fclose]
        add esp, 4
        
        
        final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
