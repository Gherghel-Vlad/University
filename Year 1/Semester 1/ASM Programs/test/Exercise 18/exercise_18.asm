bits 32 

extern _fopen
extern _fprintf

global _write_number_in_file

segment data public data use32
    filename db "min.txt", 0
    number dd 0
    fileDescriptor dd 0
    write_mode db "w", 0
    format_number db "%x", 0


segment code public code use32
    _write_number_in_file:
        
        ;creating stack frame
        push ebp
        mov ebp, esp
        
        ; void _write_number_in_file(number)
        ; it writes the number in the given file (creates it if it doesnt exist)
        
        ; ebp+8 the number
        
        mov eax, [ebp+8]
        mov [number], eax
        
        
        
        ;FILE *fopen(const char *filename, const char *mode)
        push dword write_mode
        push dword filename
        call _fopen
        add esp, 4*2
        
        ; saving the descriptor
        mov [fileDescriptor], eax
        
        ; int fprintf(FILE *stream, const char *format, ...)
        push dword [number]
        push dword format_number
        push dword [fileDescriptor]
        call _fprintf
        add esp, 4*3
        
        
        mov esp, ebp
        pop ebp
        
        ret 
    
    
    
    
    
    
       
    
        
        
        