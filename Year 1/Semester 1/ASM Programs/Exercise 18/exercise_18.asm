bits 32 
; testing one
extern _fopen
extern _fprintf

global _determine_minimum_from_array

global _write_number_in_file

segment data public data use32
    minimumNumber dw 0

    filename db "min.txt", 0
    number dd 0
    fileDescriptor dd 0
    write_mode db "w", 0
    format_number db "%x", 0


segment code public code use32

    _determine_minimum_from_array:
        ; this function determines the minimum from an array of integers and returns it
        ; int _determine_minimum_from_array(int array[],int length)
        
        ; creating the stackframe
        push ebp
        mov ebp, esp
        mov eax, 0
        
        ; [ebp] will have the caller's ebp
        ; [ebp+4] will have the return address
        ; ebp+8 will have the address of my array
        ; ebp + 12 the length of my arrray
        
        ; ECX = how long the array will be
        mov ecx, [ebp+12]
        
        ; ebx = the address of my first element from the array
        mov ebx, [ebp+8]
        
        ; ! integers have the size of 2 bytes
        ; cheking if i have elements
        jecxz Done
        
        ; saving the first element of the array in minimumNumber
        mov eax, 0
        mov ax, [ebx]
        mov [minimumNumber], ax
        
        sub ecx, 1
        
        jecxz DoneMinimum
        
        repeat1:
            ; going to the next element in the array
            add ebx, 4
            mov ax, [ebx]
            
            ; cheking if it s a new minimum
            cmp ax, word [minimumNumber]
            jge NoNewMinimumNumber
            
            mov [minimumNumber], ax
            
            NoNewMinimumNumber:
        
        loop repeat1
        
        
        DoneMinimum:
        mov eax, 0
        mov ax, [minimumNumber]
        
        
        Done:
        mov esp, ebp
        pop ebp
        
        ret


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
    
    
    
    
    
    
       
    
        
        
        