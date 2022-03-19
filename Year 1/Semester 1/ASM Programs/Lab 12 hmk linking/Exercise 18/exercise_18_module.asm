bits 32 ; assembling for the 32 bits architecture
  

; declare external functions needed by our program
extern fscanf, printf               ; tell nasm that exit exists even if we won't be defining it
import fscanf msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll                         ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

                          
global read_number
global print_numbers
                          
; our code starts here
segment code use32 class=code
read_number:
        
        ; read_text(file_descriptor, file_content)
        
        mov ecx, [esp+12] ; ecx = file_format 
        mov edi, [esp+8] ; edi = file_content
        mov esi, [esp+4] ; esi - file_descriptor
        
        ; read_text(file_descriptor, file_format, file_content)
        
        ;int fscanf(FILE *stream, const char *format, ...)
        pushad
        
        push dword edi
        push dword ecx
        push dword [esi]
        call [fscanf]
        add esp, 4*3
        
        popad
        
        
        ; int fread(void * str, int size, int count, FILE * stream)
        ;push dword [esi]
        ;push dword 100
        ;push dword 1
        ;push dword edi
        ;call [fread]
        ;add esp, 4*4
        
        ret 4*2
        
        
print_numbers:
    ; print_numbers(message, print format, string of numbers, nr of nubmers)
    
    mov ecx, [esp+16] ; ecx = nr of numbers
    mov edi, [esp+12] ; edi = string of numbers
    mov ebx, [esp+8] ; ebx = print format
    mov esi, [esp+4] ; esi = message
    mov eax, 0 ; eax will show which number to print from the array
    ; printing the message
    pushad
    push dword esi
    call [printf]
    add esp, 4*1
    popad
    jecxz NoLoop
    
    repeat3:
        
        pushad
        
        push dword [edi + 4*eax]
        push dword ebx
        call [printf]
        add esp, 4*2
        
        
        popad
        
        inc eax ; going to the enxt number in the list
        
    loop repeat3
    
    NoLoop:
    
    
    ret 4*4

