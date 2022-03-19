bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fread, fwrite, fopen, fclose               
import exit msvcrt.dll                   
import fread msvcrt.dll                   
import fwrite msvcrt.dll                   
import fopen msvcrt.dll                   
import fclose msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
       fd1 dd 0
       file_name db "a.txt", 0
       rmode dd "r+", 0
       wmode db "w", 0
       data1 dd 0
       

; our code starts here
segment code use32 class=code
    start:
        
        ; FILE *fopen(const char *filename, const char *mode)
        push dword rmode
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je fin
        
        mov [fd1], eax
        
        loop1:
            
            ;size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
            push dword [fd1]
            push dword 100
            push dword 1
            push dword data1
            call [fread]
            add esp, 4 * 4
            
            cmp eax, 064h
            je fin_1
            
            mov ecx, eax
            
            loop2:
            
                add [data1 + ecx - 1], byte 1
            
            loop loop2
            
            mov ecx, eax
            
            mov ebx, data1
            
            loop3:
                
                
                add ebx, 1
                
                pushad
                
                
                ;size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
                push dword [fd1]
                push dword 1
                push dword 1
                push dword ebx
                call [fwrite]
                add esp, 4 * 4
                
                popad
                
            loop loop3
        
        jmp loop1
        
        
        
        fin_2:
        
        
        fin_1:
        
        ;int fclose(FILE *stream)
        push dword [fd1]
        call [fclose]
        add esp, 4 * 1
        
        
        fin:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
