bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll 
import printf msvcrt.dll    

extern concatenate_digits



; our data is declared here (the variables needed by our program)
segment data use32 class=data
        string_1 db "as34df56gh70", 0
        string_2 db "ghf11hgf546", 0
        result_1 resb 100
        result_2 resb 100
        format_1_string db "First result: %s",13, 10, 0
        format_2_string db "Second result: %s", 0
        

; our code starts here
segment code use32 class=code
    start:
       
       ; concatenate_digits(result, string1, string2)
       
       push dword string_2
       push dword string_1
       push dword result_1
       call concatenate_digits
       
       push dword string_1
       push dword string_2
       push dword result_2
       call concatenate_digits
       
       push dword result_1
       push dword format_1_string
       call [printf]
       add esp, 4*2
        
       
       push dword result_2
       push dword format_2_string
       call [printf]
       add esp, 4*2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
