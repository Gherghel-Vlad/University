bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fread, printf, scanf            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fclose msvcrt.dll



segment data use32 class=data
    file_name times 50 db 0 
    access_mode  db "r", 0
    
    file_descriptor dd -1
    length_text dd -1
    character_format db "%c", 0
    read_format db "%s", 0
    word_number dd 0
    four dw 4
    input_text times 101 dd 0 
    output_text times 101 dd 0
    

; our code starts here
segment code use32 class=code
    start:
        ; reading the name of the file
        push dword file_name
        push dword read_format
        call [scanf]
        add esp, 4*2
        
        ; opening the file
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax
        
        ; checking if the file was opened succesfully
        cmp eax, 0
        jz final
        
        ;int fread(void * str, int size, int count, FILE * stream)
        
        push dword [file_descriptor]
        push dword 100
        push dword 1
        push dword input_text
        call [fread]
        add esp, 4*4
        
        mov ecx, eax ; saving the length of the text read
        mov ebx, 0 ; my variable that counts the words
        jecxz final ; cheking if i read sth or not
        
        mov edi, output_text
        mov esi, input_text
        
        repeat1:
            mov eax, ebx
            div word [four]
            cmp dx, 0
            jne NotAMultiplePos
            
            ; case in which the word is on a 4 multiple position
            lodsb
            
            cmp al, " "
            je DoneSavingTheWord
            
            stosb 
            
            jmp repeat1
            
            DoneSavingTheWord:
            mov al, " "
            stosb ; adding a space between words
            add ebx, 1
            
            
            NotAMultiplePos:
            
            lodsb
            
            ; here i check if i am beginning to read a new word
            cmp al," "
            jne GoNext
            
            cmp byte [esi], "A"
            jl GoNext
            cmp byte [esi], "Z"
            jl FoundNewWord
            cmp byte [esi], "a"
            jl GoNext
            cmp byte [esi], "z"
            jg GoNext
            
            
            FoundNewWord:
            add ebx, 1
            
            GoNext:
            sub ecx, 1
            jecxz Done
        
        jmp repeat1
        
        Done:
        
        ; printing the answer
        push dword output_text
        call [printf]
        add esp, 4*1
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4*1
        
        
        
        final:
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
