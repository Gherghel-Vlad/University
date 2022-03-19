bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 0
    b dd 0
    r resd 1
    nr_1 resd 1
    format_d db "%d", 0
    format_x db "%x", 0
    message_a db "a = ", 0
    message_b db "b = ", 0
    message_nr_1 db "The value %d will have this number of 1's in the binary representation: %d", 0

; our code starts here
segment code use32 class=code
    start:
        ;Read a decimal number and a hexadecimal number from the keyboard. Display the number of 1's of the sum of the two numbers in decimal format.     Example:
        ; a = 32 = 0010 0000b
        ; b = 1Ah = 0001 1010b
        ; 32 + 1Ah = 0011 1010b
        ; The value printed on the screen will be 4
        
        ; imma print messages too
        push dword message_a
        call [printf]
        add esp, 4
        ;printing a =
        
        ;int scanf(const char * format, variable_address_1, ...);
        ; scanf(format_d, a)
        push dword a
        push dword format_d
        call [scanf]
        add esp, 4 * 2
        ; Read the value a from the keyboard
        
        push dword message_b
        call [printf]
        add esp, 4
        ;printing b =
        
        ; scanf(format_x, b)
        push dword b
        push dword format_x
        call [scanf]
        add esp, 4 * 2
        ; Read the value b from the keyboard
        
        mov eax, [a]
        add eax, [b] ; EAX = a + b
        
        mov ebx, eax ; i save it so i can print it later
        
        ; I will use shifting with carry to calculate the number of 1's from the result
        
        mov ecx, 32 ;  will loop 32 time cuz of 32 bits
        mov edx, 0 ; here i will calculate the number of 1's
        clc ; clearing the carry flag
        Repeta:
            shr eax, 1
            
            jae Not1 ; will jump if CF is 0
            add edx, 1
            
            Not1:
        loop Repeta
        
        ; int printf(const char * format, variable_1, constant_2, ...);
        ; printf(message_nr_1, ebx, edx)
        push edx
        push ebx
        push dword message_nr_1
        call [printf]
        add esp, 4 * 2
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
