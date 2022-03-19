bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen,                ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fopen msvcrt.dll   

extern read_number
extern print_numbers


; our data is declared here (the variables needed by our program)
segment data use32 class=data
        file_name db "numbers.txt", 0
        file_read_mode db "r", 0
        file_descriptor dd 1
        file_format db "%d", 0
        print_format db "%d ", 0
        file_content resb 100
        positive resd 100
        negative resd 100
        message_positive db "The positive numbers array is: ", 0
        message_negative db 10, 13, "The negative numbers array is: ", 0
        
        

; our code starts here
segment code use32 class=code
    start:
        
        push dword file_read_mode
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax
        
        mov ebx, 0 ; will show me where in the positive number should i put the new number
        mov edx, 0 ; will show me where in the negative number should i put the new number
        
        repeta2:
            mov [file_content], dword 0
            ; read_text(file_descriptor, file_content)
            push dword file_format
            push dword file_content
            push dword file_descriptor
            call read_number
            
            mov eax, [file_content]
            
            cmp eax, 0
            je done
            
            cmp eax,0
            jl nr_neg
            
            lea edi, [positive + ebx * 4]
            mov [edi], dword eax
            inc ebx
            jmp continue
            
            
            nr_neg:
            lea edi, [negative + edx * 4]
            mov [edi], dword eax
            inc edx
            
            continue:
            
        jmp repeta2
        done:
        
        
        
    ; print_numbers(message, print format, string of numbers, nr of nubmers)
        pushad
        
        push dword ebx
        push dword positive
        push dword print_format
        push dword message_positive
        call print_numbers
        
        popad
        
        pushad
        
        push dword edx
        push dword negative
        push dword print_format
        push dword message_negative
        call print_numbers
        
        popad
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
